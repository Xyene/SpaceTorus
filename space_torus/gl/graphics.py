from math import *
from pyglet.gl import *
import pyglet

"""
    OpenGL utilities to make OpenGL more Python-like.
"""

# Shorthands for ctype float vectors
fv_4 = (GLfloat * 4)
fv_8 = (GLfloat * 8)
fv_16 = (GLfloat * 16)

'''
    Shorthands for OpenGL state boilerplate, e.g.

    with glSection(GL_QUADS):
        # Vertices

    instead of the more verbose

    glBegin(GL_QUADS)
    # Vertices
    glEnd()
'''
class glSection(object):
    def __init__(self, mode):
        self.mode = mode

    def __enter__(self):
        glBegin(self.mode)

    def __exit__(self, *excinfo):
        glEnd()

class glRestore(object):
    def __init__(self, mode):
        self.mode = mode

    def __enter__(self):
        glPushAttrib(self.mode)

    def __exit__(self, *excinfo):
        glPopAttrib()

class glMatrix(object):
    def __init__(self):
        pass

    def __enter__(self):
        glPushMatrix()

    def __exit__(self, *excinfo):
        glPopMatrix()


__TWOPI = pi * 2

# Cache for glString, mangled
__label = pyglet.text.Label('', font_name='Consolas', font_size=12, x=0, y=0, color=(255,) * 4)

def glString(x, y, text, font='Consolas', size=__label.font_size, anchor_x=__label.anchor_x, anchor_y=__label.anchor_y, color=__label.color, bold=False, italic=False):
    global __label
    # Update style
    __label.x = x
    __label.y = y
    __label.font_size = size
    __label.font = font
    __label.color = color
    __label.bold = bold
    __label.italic = italic

    __label.anchor_x = anchor_x
    __label.anchor_y = anchor_y
    # Draw each line
    for line in text.split('\n'):
        __label.y -= 20
        __label.text = line
        __label.draw()
        __label.y -= size


def glCompile(pointer, *args, **kwargs):
    """
        Executes pointer in a list.
    """
    display = glGenLists(1)
    glNewList(display, GL_COMPILE)
    pointer(*args, **kwargs)
    glEndList()
    return display


def glOrthoProjection(width, height):
    """
        Specifies an orthographic (2D) projection.
    """
    glDisable(GL_LIGHTING)
    glDisable(GL_DEPTH_TEST)
    glMatrixMode(GL_PROJECTION)
    glPushMatrix()
    glLoadIdentity()
    glOrtho(0, width, 0, height, -1, 1)
    glMatrixMode(GL_MODELVIEW)
    glPushMatrix()
    glLoadIdentity()


def glFrustrumProjection():
    """
        Specifies a frustrum (3D) projection.
    """
    glMatrixMode(GL_PROJECTION)
    glPopMatrix()
    glMatrixMode(GL_MODELVIEW)
    glPopMatrix()
    glEnable(GL_LIGHTING)
    glEnable(GL_DEPTH_TEST)

def glDisk(rinner, router, segs, tex):
    """
        Draws a disk in 2D world space.
    """
    glEnable(GL_TEXTURE_2D)
    glDisable(GL_LIGHTING)
    glBindTexture(GL_TEXTURE_2D, tex)
    res = segs * 5

    glBegin(GL_TRIANGLE_STRIP)
    texture = 0
    for n in xrange(res + 1):
        theta = __TWOPI * n / res
        x = cos(theta)
        y = sin(theta)
        glTexCoord2f(0, texture)
        glVertex2f(rinner * x, rinner * y)
        glTexCoord2f(1, texture)
        glVertex2f(router * x, router * y)
        texture ^= 1
    glEnd()
    glEnable(GL_LIGHTING)
    glDisable(GL_TEXTURE_2D)


def glSphere(r, lats, longs, tex, lighting=True):
    """
        Sphere function from the OpenGL red book.
    """
    sphere = gluNewQuadric()
    gluQuadricDrawStyle(sphere, GLU_FILL)
    gluQuadricTexture(sphere, True)
    if lighting:
        gluQuadricNormals(sphere, GLU_SMOOTH)

    glEnable(GL_TEXTURE_2D)
    if lighting:
        glDisable(GL_BLEND)
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (GLfloat * 4)(1, 1, 1, 0))
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat * 4)(1, 1, 1, 0))
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 125)
    else:
        glDisable(GL_LIGHTING)
    glBindTexture(GL_TEXTURE_2D, tex)

    gluSphere(sphere, r, lats, longs)

    glBindTexture(GL_TEXTURE_2D, 0)
    glDisable(GL_TEXTURE_2D)
    glEnable(GL_LIGHTING)
    glEnable(GL_BLEND)
    gluDeleteQuadric(sphere)


def glTorus(major_radius, minor_radius, n_major, n_minor, material, shininess=125):
    """
        Torus function from the OpenGL red book.
    """
    glPushAttrib(GL_CURRENT_BIT)
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, material)
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, fv_4(1, 1, 1, 1))
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess)

    major_s = __TWOPI / n_major
    minor_s = __TWOPI / n_minor

    def n(x, y, z):
        m = 1.0 / sqrt(x * x + y * y + z * z)
        return [x * m, y * m, z * m]

    fv_3 = (GLfloat * 3)
    for i in xrange(n_major):
        a0 = i * major_s
        a1 = a0 + major_s
        x0 = cos(a0)
        y0 = sin(a0)
        x1 = cos(a1)
        y1 = sin(a1)

        glBegin(GL_TRIANGLE_STRIP)

        for j in xrange(n_minor + 1):
            b = j * minor_s
            c = cos(b)
            r = minor_radius * c + major_radius
            z = minor_radius * sin(b)

            glNormal3fv(fv_3(*n(x0 * c, y0 * c, z / minor_radius)))
            glVertex3f(x0 * r, y0 * r, z)

            glNormal3fv(fv_3(*n(x1 * c, y1 * c, z / minor_radius)))
            glVertex3f(x1 * r, y1 * r, z)

        glEnd()
    glPopAttrib()