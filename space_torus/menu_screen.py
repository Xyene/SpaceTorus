from space_torus import soundbank
from space_torus.game import *
from space_torus.overlay import *
from space_torus.starfield_screen import AppletScreenStarfield
from space_torus.ship_screen import AppletScreenShipSelect
from time import time
import pyglet


class AppletScreenMainMenu(AppletScreenStarfield):
    def __init__(self, applet):
        super(AppletScreenMainMenu, self).__init__(applet, 2000)
        self.applet = applet
        self.active = True
        self.dirty = True
        self.flash_id = 0
        self.banner_id = 0
        # soundbank.THEME.play()

    def update(self, dt):
        super(AppletScreenMainMenu, self).update(dt)

    def on_mouse_press(self, x, y, button, modifiers):
        self.applet.overlay = AppletScreenShipSelect(self.applet)

    def on_resize(self, width, height):
        self.dirty = True

    def __do_compile(self):
        width, height = self.applet.get_size()
        if self.flash_id:
            glDeleteLists(self.flash_id, 1)
        if self.banner_id:
            glDeleteLists(self.banner_id, 1)
        self.flash_id = glCompile(glString, width / 2, height / 2, "Click anywhere to start!", anchor_x="center",
                                  anchor_y="center", size=42, color=(0, 0, 255, 255))
        self.banner_id = glCompile(glString, width / 2, height - 100, "Space Torus", anchor_x="center", size=64,
                                   color=(0, 255,) * 2)

    def on_draw(self):
        glPushMatrix()
        glRotatef(180, 0, 1, 0)
        super(AppletScreenMainMenu, self).on_draw()

        width, height = self.applet.get_size()

        glOrthoProjection(width, height)
        with glRestore(GL_ENABLE_BIT):
            glDisable(GL_LIGHTING)
            glEnable(GL_TEXTURE_2D)
            glEnable(GL_BLEND)
            if self.dirty:
                self.__do_compile()
                self.dirty = False

            if int(time() * 2) & 1:
                glCallList(self.flash_id)
            glCallList(self.banner_id)

        glFrustrumProjection()
        glPopMatrix()