#!/usr/bin/python

def main():
    print "Welcome to Space Torus. The game will begin shortly."

    import os

    os.environ['PYGLET_SHADOW_WINDOW'] = "0"

    import pyglet

    pyglet.options['shadow_window'] = False
    # Omit relatively expensive error checking
    pyglet.options['debug_gl'] = False
    pyglet.options['debug_trace_flush'] = False

    from space_torus.game import Applet

    d = pyglet.window.get_platform().get_default_display().get_default_screen()
    w = d.width - 100
    h = d.height - 100
    a = Applet(width=w, height=h, caption="Space Torus", resizable=True, vsync=0)
    # Center on screen
    a.set_location(d.width / 2 - w / 2,  d.height / 2 - h / 2)
    # Because a crosshair looks a bit neater
    a.set_mouse_cursor(a.get_system_mouse_cursor('crosshair'))

    pyglet.app.run()


if __name__ == '__main__':
    main()