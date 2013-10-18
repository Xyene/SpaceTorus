from pyglet import image
from pyglet.gl import *

id = 0
cache = {}


def load_texture(file, safe=False):
    global id, cache
    if file in cache:
        return cache[file]
    id += 1
    print "Loading image %s..." % file

    import os.path

    raw = image.load(os.path.join(os.path.dirname(__file__), "assets", "textures", file))

    width, height = raw.width, raw.height

    mode = GL_RGBA if 'A' in raw.format else GL_RGB
    # Flip from BGR to RGB
    # I hate you too, Pyglet...
    # REGULAR EXPRESSIONS ARE NOT MEANT TO PARSE BINARY DATA!!!
    texture = raw.get_data('RGBA', width * 4) if safe else raw.data[::-1] if 'BGR' in raw.format else raw.data

    buffer = [id] # Buffer to hold the returned texture id
    glGenTextures(1, (GLuint * len(buffer))(*buffer))

    glBindTexture(GL_TEXTURE_2D, buffer[0])

    #Load textures with no filtering. Filtering generally makes the texture blur.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST)
    glTexImage2D(GL_TEXTURE_2D, 0, mode, width, height, 0, mode, GL_UNSIGNED_BYTE, texture)

    cache[file] = buffer[0]

    return buffer[0]