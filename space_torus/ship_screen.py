from datetime import datetime, timedelta
from space_torus import soundbank
from space_torus.camera import Camera
from space_torus.entity import *
from space_torus.starfield_screen import AppletScreenStarfield
from world import *

try:
    import json
except ImportError:
    try:
        import simplejson as json
    except:
        print "No compatible JSON decoder found."
        import sys

        sys.exit()

try:
    from space_torus.gl.cmodel import *
except ImportError:
    from space_torus.gl.model import *

import game
from space_torus.game import *
from space_torus.overlay import *
from os import listdir
from os.path import isfile, join
import os.path
from space_torus.gl.graphics import *

SPACECRAFT_BASE_DIR = "assets\spacecraft"


class ShipDef(object):
    def __init__(self, name, description, speed, sensitivity, model):
        self.name = name
        self.description = description
        self.speed = speed
        self.sensitivity = sensitivity
        self.model = model


class AppletScreenShipSelect(AppletScreenStarfield):
    def __init__(self, applet):
        super(AppletScreenShipSelect, self).__init__(applet, 2000)
        self.applet = applet
        self.active = True
        self.ships = []
        self.rot = 0
        self.selected = -1
        self.text_list = 0

        # Enable two light sources
        glEnable(GL_LIGHTING)
        glEnable(GL_LIGHT0)
        glEnable(GL_LIGHT1)

        # Essentially one behind all planets and one in front, so that everything is well lit
        glLightfv(GL_LIGHT0, GL_POSITION, fv_4(.5, .5, 1, 0))
        glLightfv(GL_LIGHT0, GL_SPECULAR, fv_4(.5, .5, 1, 1))
        glLightfv(GL_LIGHT0, GL_DIFFUSE, fv_4(1, 1, 1, 1))
        glLightfv(GL_LIGHT1, GL_POSITION, fv_4(1, 0, .5, 0))
        glLightfv(GL_LIGHT1, GL_DIFFUSE, fv_4(.5, .5, .5, 1))
        glLightfv(GL_LIGHT1, GL_SPECULAR, fv_4(1, 1, 1, 1))

        # Begin loading all ships (.json files in /assets/spacecraft
        path = os.path.join(os.path.dirname(__file__), SPACECRAFT_BASE_DIR)
        for sf in [os.path.join(path, f) for f in listdir(path) if isfile(join(path, f)) and f.endswith(".json")]:
            # Load and read attributes
            root = json.load(open(sf, 'r'))
            name = root['name']
            description = root['description']
            model = os.path.join(path, root['model'])
            speed = int(root['speed'])
            sensitivity = float(root['sensitivity'])
            scale = float(root['scale'])
            pitch = float(root['pitch'])
            yaw = float(root['yaw'])
            roll = float(root['roll'])

            print "Loading spacecraft '%s' (%s: %s) %sx [%s, %s, %s]" % (
                name, description, model, scale, pitch, yaw, roll)

            # Create a ship and compile a display list for it
            self.ships.append(
                ShipDef(name, description, speed, sensitivity,
                        model_list(load_model(model), scale, scale, scale, (pitch, yaw, roll))))

    def update(self, dt):
        # Allow the starfield to update
        super(AppletScreenShipSelect, self).update(dt)

    def on_mouse_press(self, x, y, button, modifiers):
        if self.selected != -1:
            # A ship has been selected; we can start the game
            # Here we pass control to an AppletScreenWorld overlay
            import space_torus.world_screen
            self.applet.overlay = space_torus.world_screen.AppletScreenWorld(self.applet, load_world(r"assets\worlds\solar_system.json"),
                                                    self.ships[self.selected])
            # The game is controlled via mouse so it makes sense to grab focus
            self.applet.set_exclusive_mouse(True)

    def on_mouse_motion(self, mx, my, dx, dy):
        # Check if the user's mouse is above a ship
        # This is performed in O(n) time but can be modified to O(1) time
        selection = -1
        # The rectangle of the selection line loop
        w = 450
        h = 55
        x = 5
        height = self.applet.get_size()[1]

        for idx in xrange(len(self.ships)):
            y = height - 45 - idx * 55 - h

            if x <= mx <= x + w and y <= my <= y + h:
                selection = idx
                break
        if selection != self.selected:
            # Something new has been selected
            self.selected = selection
            # soundbank.CLIP_BLIP.play()

    def on_resize(self, width, height):
        glDeleteLists(self.text_list, 1)
        self.text_list = 0

    def on_draw(self):
        applet = self.applet

        glRotatef(180, 0, 1, 0)

        glDisable(GL_LIGHTING)
        glEnable(GL_BLEND)
        glColor4f(1, 1, 1, 1)
        glEnable(GL_TEXTURE_2D)

        width, height = applet.get_size()

        glOrthoProjection(width, height)

        if not self.text_list:
            self.text_list = glGenLists(1)
            glNewList(self.text_list, GL_COMPILE)
            glString(width / 2, height - 10, "Choose a vessel...", size=16, color=(0, 255,) * 2, anchor_x="center")

            for idx in xrange(len(self.ships)):
                ship = self.ships[idx]
                glString(10, height - 40 - idx * 55, ship.name, size=12, color=(0, 255,) * 2, bold=True)
                glString(20, height - 55 - idx * 55, ship.description, color=(255,) * 4, bold=False)
                glString(20, height - 70 - idx * 55,
                         "Maximum speed %skm/s, %.0f%% maneuverability" % (ship.speed, (1 - ship.sensitivity) * 100))
            glEndList()
        glCallList(self.text_list)

        if self.selected != -1:
            glDisable(GL_TEXTURE_2D)
            with glSection(GL_LINE_LOOP):
                w = 425
                h = 55
                x = 5
                y = height - 45 - self.selected * 55 - h
                glColor3f(0, 1, 0)
                glVertex2f(x, y)
                glVertex2f(x + w, y)
                glVertex2f(x + w, y + h)
                glVertex2f(x, y + h)
            glFrustrumProjection()
            glEnable(GL_LIGHTING)
            glEnable(GL_TEXTURE_2D)
            glEnable(GL_BLEND)

            with glMatrix(), glRestore(GL_CURRENT_BIT):
                ship = self.ships[self.selected]
                glTranslatef(-1, 0, 10)
                glRotatef(-self.rot, 0, 1, 0)
                self.rot += 3
                glCallList(ship.model)
        else:
            glFrustrumProjection()
        super(AppletScreenShipSelect, self).on_draw()
