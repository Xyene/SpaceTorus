from space_torus.gl.graphics import *


def overlay_start(overlay):
    def _start(err):
        overlay.cam.lock = True
        n = min(int(round(err / 40.0, 1)), 3)
        if n > 0:
            w, h = overlay.applet.get_size()
            glString(w / 2, h / 2, str(n), size=64, anchor_x='center', anchor_y='baseline')
        if n <= 0:
            overlay.cam.lock = False
        return (err - 1 if n > 0 else 0) if overlay.applet.exclusive else err
    return _start

def overlay_message(overlay, color):
    def _hit((err, message)):
        with glRestore(GL_CURRENT_BIT | GL_ENABLE_BIT):
            w, h = overlay.applet.get_size()
            glEnable(GL_BLEND)
            glColor4f(color[0], color[1], color[2], err / 100.0)
            with glSection(GL_QUADS):
                glVertex2f(0, 0)
                glVertex2f(0, h)
                glVertex2f(w, h)
                glVertex2f(w, 0)
        glString(10, h - (180 - err), message)
        err -= 1
        if err > 0:
            return err, message
        return None
    return _hit