from datetime import datetime, timedelta
from space_torus.camera import Camera

from pyglet.window import key, mouse
from pyglet.gl import *
from space_torus.dead_screen import AppletScreenDead

from space_torus.game import *
from space_torus.overlay import *


TORUS_DETAIL = 7        # 2 ** detail edges/torus
TORUS_RADIUS = 4
TORUS_DISTANCE = 20     # How far each torus should be
INITIAL_SPEED = 2       # The initial speed of the player
DELTA = 0.00314159265   # How much to increment speed / second
VIEW_DISTANCE = 3       # How many tori to show in front
MOUSE_SENSITIVITY = 0.3 # Mouse sensitivity, 0..1, none...hyperspeed

class AppletScreenWorld(object):
    def __init__(self, applet, world, ship):
        self.applet = applet
        self.world = world
        self.speed = ship.speed / 100.0
        self.missed = 0
        self.score = 0
        self.overlays = {}
        self.active = True
        self.invincible = False
        self.info = True
        self.time = 0
        self.zoom = 10.0
        self.cam = Camera()

        def update_time(dt):
            if self.applet.exclusive and not self.cam.lock:
                self.time += 1
                self.speed += DELTA

        pyglet.clock.schedule_interval(update_time, 1)
        self.torus_id = glCompile(glTorus, TORUS_RADIUS, 0.25, TORUS_DETAIL ** 2, TORUS_DETAIL ** 2,  fv_4(.07, .37, 1, 2))
        self.cl_torus_id = glCompile(glTorus, TORUS_RADIUS, 0.25, TORUS_DETAIL ** 2, TORUS_DETAIL ** 2, fv_4(0, 1, 0, 1))
        self.ship = ship

        self.world.generate_tori(TORUS_DISTANCE)
        c = self.cam
        # Position camera at first torus...
        c.x, c.y, c.z = self.world.tori[0]
        c.z -= TORUS_DISTANCE # ... well, a bit away...
        self.cam.yaw = 180 # ... and face the torus.

        self.overlays[overlay_start(self)] = 160

    def update(self, dt):
        cam = self.cam
        if self.applet.exclusive and not self.cam.lock:
            x0, y0, z0 = cam.x, cam.y, cam.z
            cam.move(0, 0, -self.speed * 128 * 0.003)
            x1, y1, z1 = cam.x, cam.y, cam.z
            if cam.z >= self.world.tori[-1][2]:
                self.applet.set_exclusive_mouse(False)
                self.info = False
                self.applet.overlay = AppletScreenDead(self, "Exited the solar system.\nScored %s points." % self.score)
                return
            tz0, tz1 = int(z0), int(z1)
            # If the two torus steps are different, it means we've entered
            # a different torus sector.
            if tz0 / TORUS_DISTANCE != tz1 / TORUS_DISTANCE:
                dx, dy, dz = x1 - x0, y1 - y0, z1 - z0
                for torus_step in xrange(tz1 - tz0):
                    # Passed a torus boundary
                    torus = tz0 / TORUS_DISTANCE + torus_step + 1
                    if torus >= len(self.world.tori):
                        break
                    tx, ty, tz = self.world.tori[torus]
                    factor = (tz - z0) / dz
                    ax, ay = factor * dx + x0, factor * dy + y0
                    distance = hypot(ax - tx, ay - ty)
                    if distance - 1.5 > TORUS_RADIUS:
                        if not self.invincible:
                                self.missed += 1
                                hp = min((25 - self.missed) * 4, 100)
                                if hp >= 0:
                                    self.overlays.clear()
                                    self.overlays[overlay_message(self, (1, 0, 0))] = (70, ("Hull integrity at %s%%." + (" Watch it!" if not hp else "")) % hp)
                                else:
                                    self.applet.set_exclusive_mouse(False)
                                    self.info = False
                                    # It is easier to use an overlay that blocks input than to have locking flags
                                    self.applet.overlay = AppletScreenDead(self, "Your ship explodes.\nScored %s points." % self.score)
                    else:
                        self.score += 1

        if self.applet.exclusive:
            # Check if a planet collision has occured
            for entity in self.world.tracker:
                entity.update()
                x, y, z = entity.location
                distance = sqrt((cam.x - x) ** 2 + (cam.z - z) ** 2 + (cam.y - y) ** 2)
                if entity.bounding_radius and distance + 3 >= entity.bounding_radius and distance - 3 <= entity.bounding_radius:
                    self.applet.set_exclusive_mouse(False)
                    self.info = False
                    self.applet.overlay = AppletScreenDead(self, "Your ship is flattened.\nScored %s points." % self.score)

    def on_mouse_press(self, x, y, button, modifiers):
        if not self.applet.exclusive:
            # Grab mouse
            self.applet.set_exclusive_mouse(True)

    def on_mouse_motion(self, x, y, dx, dy):
        if not self.cam.lock and self.applet.exclusive: # Only handle camera movement if mouse is grabbed
            self.cam.mouse_move(dx * self.ship.sensitivity, dy * self.ship.sensitivity)

    def on_mouse_scroll(self, x, y, scroll_x, scroll_y):
        # As a zoom occurs we can't just go further behind: we also need to go up a bit to keep the perspective
        self.zoom = min(60.0, self.zoom + 2.5) if scroll_y < 0 else max(10.0, self.zoom - 2.5)

    def on_key_press(self, symbol, modifiers):
        if symbol == key.NUM_ADD:
            self.speed += 1
        elif symbol == key.NUM_SUBTRACT:
            self.speed -= 1
        elif symbol == key.NUM_MULTIPLY:
            self.speed += 10
        elif symbol == key.NUM_DIVIDE:
            self.speed -= 10
        elif symbol == key.I:
            self.active = not self.active
        elif symbol == key.G:
            self.invincible = not self.invincible
            self.missed = 0
            self.overlays.clear()
            self.overlays[overlay_message(self, (0, 0, 1))] = (50, ("Invincibility %s." % ("on" if self.invincible else "off")))


    def on_draw(self):
        applet = self.applet

        cam = self.cam
        glRotatef(180, 0, 1, 0)
        # Uncomment this line for a much harder game
        # glRotatef(-(c.yaw / 10), 0, 0, 1)
        glTranslatef(-cam.x, -(cam.y + self.zoom / 4), -(cam.z - self.zoom))

        glEnable(GL_LIGHTING)
        glEnable(GL_BLEND)

        glColor3f(1, 1, 1)

        z = int(cam.z / TORUS_DISTANCE)
        for torus in xrange(z, min(z + VIEW_DISTANCE, len(self.world.tori) - 1)):
            with glMatrix(), glRestore(GL_CURRENT_BIT):
                glTranslatef(*self.world.tori[torus])
                glCallList(self.torus_id if torus != z + 1 else self.cl_torus_id)

        with glMatrix(), glRestore(GL_CURRENT_BIT):
            glTranslatef(cam.x, cam.y, cam.z)
            glRotatef(cam.pitch, 1, 0, 0)
            glRotatef(-cam.yaw, 0, 1, 0)
            glRotatef(cam.roll, 0, 0, 1)
            glCallList(self.ship.model)

        for entity in self.world.tracker:
            x, y, z = entity.location
            pitch, yaw, roll = entity.rotation

            with glMatrix():
                glTranslatef(x, y, z)
                glRotatef(pitch, 1, 0, 0)
                glRotatef(yaw, 0, 1, 0)
                glRotatef(roll, 0, 0, 1)
                glCallList(entity.id)

            if hasattr(entity, "atmosphere") and entity.atmosphere:
                with glMatrix():
                    glTranslatef(*entity.location)

                    matrix = fv_16()
                    glGetFloatv(GL_MODELVIEW_MATRIX, matrix)
                    matrix[0: 3] = [1, 0, 0]
                    matrix[4: 7] = [0, 1, 0]
                    matrix[8:11] = [0, 0, 1]
                    glLoadMatrixf(matrix)

                    glCallList(entity.atmosphere)

            if hasattr(entity, "cloudmap") and entity.cloudmap:
                with glMatrix(), glRestore(GL_ENABLE_BIT):
                    glEnable(GL_ALPHA_TEST)
                    glTranslatef(*entity.location)
                    pitch, yaw, roll = entity.rotation
                    glRotatef(pitch, 1, 0, 0)
                    glRotatef(yaw, 0, 1, 0)
                    glRotatef(roll, 0, 0, 1)
                    glCallList(entity.cloudmap)

        glDisable(GL_TEXTURE_2D)

        width, height = applet.get_size()

        glOrthoProjection(width, height)

        if not self.cam.lock and self.info:
            d = datetime(1, 1, 1) + timedelta(seconds=self.time)

            glString(10, height, '''%.1f FPS\n%s points\ntime (%d:%d:%d)\nspeed %dkm/s''' % (
                pyglet.clock.get_fps(), self.score, d.hour, d.minute, d.second, self.speed * 100), size=10)

            # Draws progress bar
            x, y = 5, 5
            width, height = 10, 2
            progress = min((25 - self.missed) * 4, 100)
            with glRestore(GL_CURRENT_BIT):
                # Draw border
                with glSection(GL_LINE_LOOP):
                    glColor3f(1, 0, 0)
                    glVertex2f(x, y)
                    glVertex2f(x + width, y)
                    glColor3f(0, 1, 0)
                    glVertex2f(x + width, y + height * 100)
                    glVertex2f(x, y + height * 100)
                # And the fill
                with glSection(GL_QUADS):
                    glColor3f(1, 0, 0)
                    glVertex2f(x, y)
                    glVertex2f(x + width, y)
                    glColor3f(0, 1, 0)
                    glVertex2f(x + width, y + height * progress)
                    glVertex2f(x, y + height * progress)

        # Update overlays
        for pointer, err in dict(self.overlays).iteritems():
            err = pointer(err)
            if not err:
                self.overlays.pop(pointer, None)
            else:
                self.overlays[pointer] = err

        glFrustrumProjection()