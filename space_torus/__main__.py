#!/usr/bin/python

INITIAL_WIN_HEIGHT = 540
INITIAL_WIN_WIDTH = 700
WIN_TITLE = "Space Torus"
MUSIC = False
OPTIMIZED = True


def main():
    import sys

    if OPTIMIZED and not sys.flags.optimize:
        print "Optimizing session..."
        import subprocess

        subprocess.call([sys.executable, '-O'] + sys.argv)
        return
    print "Welcome to Space Torus. The game will begin shortly."

    import pyglet
    from pyglet.media import Player

    from space_torus.game import Applet

    if MUSIC:
        player = Player()
        player.queue(pyglet.resource.media("assets/music/default.mp3"))
        player.eos_action = player.EOS_LOOP
        player.play()

    window = Applet(width=INITIAL_WIN_WIDTH, height=INITIAL_WIN_HEIGHT, caption=WIN_TITLE, resizable=True, vsync=0)
    pyglet.app.run()


if __name__ == '__main__':
    main()