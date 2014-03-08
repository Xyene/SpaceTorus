from time import clock
import os.path

from space_torus.gl.texture import load_texture
from space_torus.gl.graphics import *

__FACE_TRIANGLES = 0
__FACE_QUADS = 1
__DISPLAY_CACHE = {}
__CACHE = {}


def model_list(model, sx=1.0, sy=1.0, sz=1.0, rotation=(0, 0, 0), nocache=False):
    """
        Compiles a model into a display list.
        Here be dragons.
    """
    global __DISPLAY_CACHE
    if not nocache and model in __DISPLAY_CACHE:
        return __DISPLAY_CACHE[model]

    # The list our object will be contained in
    display = glGenLists(1)
    __DISPLAY_CACHE[model] = display
    print "Regen!"
    for m, text in model.materials.iteritems():
        if text.texture:
            # Ensure all textures are loaded
            load_texture(os.path.join(model.root, text.texture))

    glNewList(display, GL_COMPILE)
    with glMatrix(), glRestore(GL_CURRENT_BIT):
        with glRestore(GL_TRANSFORM_BIT):
            # Apply transformations
            pitch, yaw, roll = rotation
            glRotatef(pitch, 1, 0, 0)
            glRotatef(yaw, 0, 1, 0)
            glRotatef(roll, 0, 0, 1)

        vertices = model.vertices
        textures = model.textures
        normals = model.normals

        for g in model.groups:
            material = g.material

            tex_id = load_texture(os.path.join(model.root, material.texture)) if (material and material.texture) else 0

            if tex_id:
                glEnable(GL_TEXTURE_2D)
                glBindTexture(GL_TEXTURE_2D, tex_id)
            else:
                glBindTexture(GL_TEXTURE_2D, 0)
                glDisable(GL_TEXTURE_2D)

            if material:
                # Apply ambient, diffuse and specular lighting properties.
                if material.Ka:
                    kx, ky, kz = material.Ka
                    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, fv_4(kx, ky, kz, 1))
                if material.Kd:
                    kx, ky, kz = material.Kd
                    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, fv_4(kx, ky, kz, 1))
                if material.Ks:
                    kx, ky, kz = material.Ks
                    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, fv_4(kx, ky, kz, 1))
                glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material.shininess)

            type = -1

            def point(f, vertices, normals, textures, n):
                if f.norms:
                    glNormal3f(*normals[f.norms[n]])
                if tex_id:
                    coords = textures[f.texs[n]]
                    if len(coords) == 2:
                        glTexCoord2f(*coords)
                    else:
                        glTexCoord3f(*coords)

                x, y, z = vertices[f.verts[n]]
                glVertex3f(x * sx, y * sy, z * sz)

            for f in g.faces:
                if type != f.type:
                    if type != -1:
                        glEnd()
                    glBegin(GL_TRIANGLES)
                type = f.type

                point(f, vertices, normals, textures, 0)
                point(f, vertices, normals, textures, 1)
                point(f, vertices, normals, textures, 2)

                if type == __FACE_QUADS:
                    # We might as well triangulate the model for a bit of a rendering gain on some cards
                    point(f, vertices, normals, textures, 2)
                    point(f, vertices, normals, textures, 3)
                    point(f, vertices, normals, textures, 0)
        glEnd()

    glEndList()
    return display


def load_model(path, nocache=False):
    """
        Generates a model object from the given model file.
    """
    global __CACHE
    if not nocache and path in __CACHE:
        return __CACHE[path]
    # The location we shall search for materials.
    root = os.path.dirname(path)

    vertices = []
    normals = []
    textures = []
    groups = []
    materials = {}

    # Allez au diable, Python
    current_group = [None]
    current_material = [None]

    def dispatch(p, commands):
        with open(p, 'r') as file:
            for line in file:
                line = line.strip()
                if not line or line[0] == '#':
                    continue # Empty or comment
                words = line.split()
                type = words[0]
                if type in commands:
                    commands[type](words)

    def newmtl(words):
        """
            Material definition.
        """
        material = Material(words[1])
        materials[words[1]] = material
        current_material[0] = material

    def Ka(words):
        """
            Ambient light colour.
        """
        current_material[0].Ka = (float(words[1]), float(words[2]), float(words[3]))

    def Kd(words):
        """
            Diffuse light colour.
        """
        current_material[0].Kd = (float(words[1]), float(words[2]), float(words[3]))

    def Ks(words):
        """
            Specular light colour.
        """
        current_material[0].Ks = (float(words[1]), float(words[2]), float(words[3]))

    def Ns(words):
        """
            Shiny.
        """
        current_material[0].shininess = min(float(words[1]), 125) # Seems to sometimes be > 125. TODO: find out why

    def map_Kd(words):
        """
            Diffuse texture.
        """
        current_material[0].texture = words[-1]

    def v(words):
        """
            A vertex.
        """
        vertices.append((float(words[1]), float(words[2]), float(words[3])))

    def vn(words):
        """
            A normal.
        """
        normals.append((float(words[1]), float(words[2]), float(words[3])))

    def vt(words):
        """
            A texture coordinate.
        """
        l = len(words)
        x, y, z = 0, 0, 0
        if l >= 2:
            x = float(words[1])
        if l >= 3:
            # OBJ origin is at upper left, OpenGL origin is at lower left
            y = 1 - float(words[2])
        if l >= 4:
            z = float(words[3])
        textures.append((x, y, z))

    def f(words):
        """
            A face; links multiple vertices together.
        """
        l = len(words)
        type = -1
        face_vertices = []
        face_normals = []
        face_textures = []

        vertex_count = l - 1
        if vertex_count == 3:
            type = __FACE_TRIANGLES
        elif vertex_count == 4:
            type = __FACE_QUADS
        else:
            raise Exception("only tri and quad faces supported, got face with %s vertices" % vertex_count)

        raw_faces = []
        current_value = -1
        vindices = []
        nindices = []
        tindices = []

        for i in xrange(1, vertex_count + 1):
            raw_faces = words[i].split('/')
            l = len(raw_faces)

            current_value = int(raw_faces[0])

            vindices.append(current_value - 1)
            face_vertices.append(vertices[current_value - 1])

            if l == 1:
                continue

            if l >= 2 and raw_faces[1]:
                current_value = int(raw_faces[1])
                if current_value <= len(textures):
                    tindices.append(current_value - 1)
                    face_textures.append(textures[current_value - 1])
            if l >= 3 and raw_faces[2]:
                current_value = int(raw_faces[2])
                nindices.append(current_value - 1)
                face_normals.append(normals[current_value - 1])

        if not groups:
            group = Group()
            groups.append(group)
        else:
            group = groups[-1]
        group.vertices += face_vertices
        group.normals += face_normals
        group.textures += face_textures

        idx_count = group.idx_count
        group.indices += (idx_count + 1, idx_count + 2, idx_count + 3)
        group.idx_count += 3

        group.faces.append(Face(type, vindices, nindices, tindices, face_vertices, face_normals, face_textures))

    # Loads a material file
    mtllib = lambda words: dispatch(os.path.join(root, words[1]), obj)

    def usemtl(words):
        """
            Begin using a material.
            Only material groups are supported (one material per group).
        """
        mat = ' '.join(words[1:])
        if mat in materials:
            groups[-1].material = materials[mat]
        else:
            print "Warning: material %s undefined." % mat

    # Create new group
    g = lambda words: groups.append(Group(words[1]))

    # Lookup for all directives
    obj = {
        'v': v,
        'vn': vn,
        'vt': vt,
        'f': f,
        'mtllib': mtllib,
        'usemtl': usemtl,
        'g': g,
        'o': g, # TODO: o is not really g
        'newmtl': newmtl,
        'Ka': Ka,
        'Kd': Kd,
        'Ks': Ks,
        'Ns': Ns,
        'map_Kd': map_Kd
    }

    dispatch(path, obj)

    object = WavefrontObject(root, vertices, normals, textures, groups, materials)
    __CACHE[path] = object
    return object


"""
    Containers for objects.
"""

class WavefrontObject(object):
    def __init__(self, root, vertices=None, normals=None, textures=None, groups=None, materials=None):
        self.root = root
        self.vertices = vertices or []
        self.normals = normals or []
        self.textures = textures or []
        self.groups = groups or []
        self.materials = materials or []


class Group(object):
    def __init__(self, name=None):
        if not name:
            name = clock()
        self.name = name
        self.material = None
        self.faces = []
        self.indices = []
        self.vertices = []
        self.normals = []
        self.textures = []
        self.idx_count = 0


class Face(object):
    def __init__(self, type, verts, norms, texs, vertices, normals, textures):
        self.type = type
        self.verts = verts
        self.norms = norms
        self.texs = texs
        self.vertices = vertices
        self.normals = normals
        self.textures = textures


class Material(object):
    def __init__(self, name, texture=None, Ka=0, Kd=0, Ks=0, shininess=0.0):
        self.name = name
        self.texture = texture
        self.Ka = Ka
        self.Kd = Kd
        self.Ks = Ks
        self.shininess = shininess