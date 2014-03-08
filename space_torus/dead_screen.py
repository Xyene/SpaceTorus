from space_torus import soundbank
from space_torus.game import *
from space_torus.overlay import *
from time import time
from space_torus.ship_screen import AppletScreenShipSelect
import pyglet

class AppletScreenDead(object):
    def __init__(self, game_screen, message):
        self.game_screen = game_screen
        self.active = True
        self.flash_id = 0
        self.banner_id = 0
        self.message = message
        self.dirty = True

    def update(self, dt):
        # Do not forward update events; effectively locks game
        pass

    def on_mouse_press(self, x, y, button, modifiers):
        # Switch to ship selection
        self.game_screen.applet.overlay = AppletScreenShipSelect(self.game_screen.applet)

    def on_resize(self, width, height):
        # Force display list recompilation.
        self.dirty = True

    def __do_compile(self):
        """
            Ensures display lists are compiled.
        """
        width, height = self.game_screen.applet.get_size()
        # Clean up old display lists
        if self.flash_id:
            glDeleteLists(self.flash_id, 1)
        if self.banner_id:
            glDeleteLists(self.banner_id, 1)
        # Generate ones for the new screen resolution
        self.flash_id = glCompile(glString, width / 2, height / 2, "Click to restart!", anchor_x="center", anchor_y="center", size=42, color=(0, 0, 255, 255))
        self.banner_id = glCompile(glString, width / 2, height - 100, self.message, anchor_x="center", size=64, color=(0, 255,)*2)

    def on_draw(self):
        with glMatrix():
            self.game_screen.on_draw()
            width, height = self.game_screen.applet.get_size()

            glOrthoProjection(width, height)

            with glRestore(GL_ENABLE_BIT):
                glDisable(GL_LIGHTING)
                glEnable(GL_TEXTURE_2D)
                glEnable(GL_BLEND)

                # If our display resolution changed, recompile text lists.
                if self.dirty:
                    self.__do_compile()
                    self.dirty = False

                if int(time() * 2) & 1:  # Flash
                    glCallList(self.flash_id)
                glCallList(self.banner_id)

            glFrustrumProjection()