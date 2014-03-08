from PIL import Image
from pyglet import image
from pyglet.gl import *
from ctypes import c_int, byref, c_ulong

# Texture cache: why load something twice?
__CACHE = {}

# Max texture size on current card, always at least 1024
__max_texture = 0


def load_texture(file, safe=False, nocache=False):
    global __CACHE, __max_texture
    if not nocache and file in __CACHE:
        return __CACHE[file]
        # print "Loading image %s..." % file

    if not __max_texture:
        buf = c_int()
        glGetIntegerv(GL_MAX_TEXTURE_SIZE, byref(buf))
        __max_texture = buf.value

    # Flip from BGR to RGB
    # I hate you too, Pyglet...
    # REGULAR EXPRESSIONS ARE NOT MEANT TO PARSE BINARY DATA!!!

    im = Image.open(file)

    width, height = im.size

    # Resize to be valid
    if width > __max_texture or height > __max_texture:
        ratio = min(float(__max_texture) / width, float(__max_texture) / height)
        width = int(width * ratio)
        height = int(height * ratio)
        # Resize with no filter; looks bad by itself but we perform bilinear filtering later
        im = im.resize((width, height), Image.NONE)

    # Convert.
    mode = GL_RGBA
    try:
        texture = im.tostring("raw", "RGBA", 0, -1)
    except SystemError:
        try:
            texture = im.tostring("raw", "RGBX", 0, -1)
        except SystemError:
            mode = GL_RGB
            texture = im.tostring("raw", "RGB", 0, -1)


    buffer = c_ulong()
    glGenTextures(1, byref(buffer))
    id = buffer.value

    glBindTexture(GL_TEXTURE_2D, id)
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1)

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)

    # Set image data
    glTexImage2D(GL_TEXTURE_2D, 0, mode, width, height, 0, mode, GL_UNSIGNED_BYTE, texture)

    __CACHE[file] = id
    return id