from datetime import datetime, timedelta
from space_torus.camera import Camera
from space_torus.entity import *

import game
from space_torus.game import *
from space_torus.overlay import *
from os import listdir
from os.path import isfile, join
import os.path
import random

class AppletScreenStarfield(object):
    def __init__(self, applet, star_count):
        self.applet = applet
        self.max_stars = star_count
        self.active = True
        self.starfield = []
        self.z = 0

    def update(self, dt):
        starfield = self.starfield
        _z = self.z
        for x, y, z in starfield:
            if z < _z:
                # Star is behind camera, we can remove
                starfield.remove((x, y, z))
        # Some stars were removed; generate some new ones
        # We can't generate too far back or they will be clipped
        for n in xrange(self.max_stars - len(starfield) + 1):
            starfield.append((random.randint(-500, 500),
                                   random.randint(-500, 500),
                                   random.randint(_z + 100, _z + 1000)))
        self.z += 5 # Move

    def on_draw(self):
        glTranslatef(0, 0, -self.z) # Scroll through starfield
        glDisable(GL_LIGHTING)
        glDisable(GL_TEXTURE_2D)
        glPointSize(1.5)
        with glSection(GL_POINTS), glRestore(GL_CURRENT_BIT):
            starfield = self.starfield
            for idx, star in enumerate(starfield):
                if idx & 1: # Every other star
                    # Change the alpha channel to make the stars appear to flicker
                    glColor4f(1, 1, 1, random.randint(75, 255) / 255.0)
                glVertex3f(*star)