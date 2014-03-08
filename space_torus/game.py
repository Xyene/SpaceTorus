from space_torus.menu_screen import AppletScreenMainMenu
from space_torus.ship_screen import AppletScreenShipSelect
from space_torus.world_screen import AppletScreenWorld

from world import *

try:
    from pyglet.gl import *
    from pyglet.gl.glu import *
    from pyglet.window import key, mouse
    import pyglet
except ImportError:
    print "Pyglet not installed correctly, or at all."
    sys.exit()

try:
    from space_torus.gl.cmodel import *
except ImportError:
    from space_torus.gl.model import *

from space_torus.overlay import *

import sys

TICKS_PER_SECOND = 40   # How many times to update game per second

class Applet(pyglet.window.Window):
    def __init__(self, *args, **kwargs):
        super(Applet, self).__init__(*args, **kwargs)

        self.exclusive = False

        pyglet.clock.schedule_interval(self.update, 1.0 / TICKS_PER_SECOND)

        glClearColor(0, 0, 0, 1)
        glClearDepth(1.0)

        glEnable(GL_BLEND)
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)

        # This is for atmosphere textures that are slightly opaque
        glAlphaFunc(GL_GEQUAL, 0.5)
        # Enable depth testing
        glDepthFunc(GL_LEQUAL)
        glEnable(GL_DEPTH_TEST)
        # Though flat shading might work well for some ships,
        # For most planets smooth shading is ideal. We can let the model
        # loader handle shading in the event a ship requires it.
        glShadeModel(GL_SMOOTH)

        glMatrixMode(GL_MODELVIEW)

        self.overlay = AppletScreenMainMenu(self)

    def update(self, dt):
        self.overlay.update(dt)

    def set_exclusive_mouse(self, exclusive):
        if self.overlay.active:
            super(Applet, self).set_exclusive_mouse(exclusive) # Pass to parent
            self.exclusive = exclusive # Toggle flag

    def on_mouse_press(self, x, y, button, modifiers):
        if hasattr(self.overlay, "on_mouse_press"): self.overlay.on_mouse_press(x, y, button, modifiers)

    def on_mouse_motion(self, x, y, dx, dy):
        if hasattr(self.overlay, "on_mouse_motion"): self.overlay.on_mouse_motion(x, y, dx, dy)

    def on_mouse_scroll(self, x, y, scroll_x, scroll_y):
        if hasattr(self.overlay, "on_mouse_scroll"): self.overlay.on_mouse_scroll(x, y, scroll_x, scroll_y)

    def on_key_press(self, symbol, modifiers):
        if symbol == key.ESCAPE: sys.exit() # Quit game
        elif symbol == key.F: self.set_fullscreen(not self.fullscreen)
        if self.exclusive: # Only handle keyboard input if mouse is grabbed
            if symbol == key.E:
                self.set_exclusive_mouse(False) # Escape mouse
            elif hasattr(self.overlay, "on_key_press"):
                self.overlay.on_key_press(symbol, modifiers)

    def on_resize(self, width, height):
        glViewport(0, 0, width, height)
        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()
        # A field of view of 45
        gluPerspective(45.0, width / float(height), 0.5, 5000000.0)
        glMatrixMode(GL_MODELVIEW)
        if hasattr(self.overlay, "on_resize"): self.overlay.on_resize(width, height)

    def on_draw(self):
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glLoadIdentity()
        self.overlay.on_draw()