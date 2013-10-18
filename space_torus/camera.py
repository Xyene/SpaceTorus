from math import *


class Camera:
    def __init__(self, x=0, y=0, z=0, pitch=0, yaw=0, roll=0):
        self.x = x
        self.y = y
        self.z = z
        self.pitch = pitch
        self.yaw = yaw
        self.roll = roll

    def move(self, dx, dy, dz):
        self.z += dx * cos(radians(self.yaw - 90)) + dz * cos(radians(self.yaw))
        self.x -= dx * sin(radians(self.yaw - 90)) + dz * sin(radians(self.yaw))
        self.y += dy * sin(radians(self.pitch - 90)) + dz * sin(radians(self.pitch))

    def mouse_move(self, dx, dy):
        MAX_LOOK_UP = 90
        MAX_LOOK_DOWN = -90

        if self.yaw + dx >= 360:
            self.yaw = self.yaw + dx - 360
        elif self.yaw + dx < 0:
            self.yaw = 360 - self.yaw + dx
        else:
            self.yaw += dx

        if MAX_LOOK_DOWN <= dy - self.pitch - dy <= MAX_LOOK_UP:
            self.pitch += -dy
        elif self.pitch - dy < MAX_LOOK_DOWN:
            self.pitch = MAX_LOOK_DOWN
        elif self.pitch - dy > MAX_LOOK_UP:
            self.pitch = MAX_LOOK_UP

    def direction(self):
        m = cos(radians(self.pitch))

        dy = -sin(radians(self.pitch))
        dx = cos(radians(self.yaw - 90)) * m
        dz = sin(radians(self.yaw - 90)) * m
        return dx, dy, dz