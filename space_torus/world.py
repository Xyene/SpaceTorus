from bisect import bisect_left
from operator import itemgetter
import hashlib
import os.path

import json

from glgeom import *
from entity import *
from texture import *


TORUS_DISTANCE = 20
AU = TORUS_DISTANCE * 100


def load_world(file):
    with open(os.path.join(os.path.dirname(__file__), file)) as f:
        world = World()
        root = json.load(f)

        e = lambda x: eval(str(x), {'__builtins__': None}, {'AU': AU})

        world.waypoints = []

        for waypoint in root['waypoints']:
            x, y, z = waypoint
            world.waypoints.append((e(x), e(y), e(z)))

        def get(var, set, default=None):
            if var in set:
                return set[var]
            return default

        for planet in root['planets']:
            print "Loading %s." % planet
            info = root['planets'][planet]

            texture = get('texture', info)
            lighting = get('lighting', info, True)
            x = e(get('x', info, 0))
            y = e(get('y', info, 0))
            z = e(get('z', info, 0))
            pitch = e(get('pitch', info, 0))
            yaw = e(get('yaw', info, 0))
            roll = e(get('roll', info, 0))
            delta = e(get('delta', info, 5))
            radius = e(get('radius', info))

            id = compile(sphere, radius, int(radius / 2), int(radius / 2), load_texture(texture), lighting=lighting)

            atmosphere = 0
            if 'atmosphere' in info:
                atmosphere_data = info['atmosphere']
                size = e(get('size', atmosphere_data))
                atm_texture = get('texture', atmosphere_data)
                atmosphere = compile(disk, radius, radius + size, 30, load_texture(atm_texture, safe=True))

            world.tracker.append(Planet(id, (x, y, z), (pitch, yaw, roll), delta=delta, atmosphere=atmosphere))
            if 'ring' in info:
                ring_data = info['ring']
                texture = get('texture', ring_data)
                distance = e(get('distance', ring_data))
                size = e(get('size', ring_data))
                pitch = e(get('pitch', ring_data, pitch))
                yaw = e(get('yaw', ring_data, yaw))
                roll = e(get('roll', ring_data, roll))

                world.tracker.append(
                    Planet(compile(disk, distance, distance + size, 30, load_texture(texture, safe=True)), (x, y, z),
                           (pitch, yaw, roll)))
        return world


class World(object):
    def __init__(self):
        self.waypoints = []
        self.tracker = []

    def torus_at(self, n):
        distance = TORUS_DISTANCE + .0

        zs = map(itemgetter(2), self.waypoints)
        index = bisect_left(zs, n * distance)
        if index < 1 or index > len(zs) - 2:
            return None
        w0, w1 = self.waypoints[index - 1:index + 1]

        x0, y0, z0 = w0
        x1, y1, z1 = w1

        dx, dy, dz = x1 - x0, y1 - y0, z1 - z0

        s = abs(dz / distance)
        dn = n - z0 / distance

        nx = x0 + (dx / s * dn)
        ny = y0 + (dy / s * dn)
        nz = z0 + (dz / s * dn)

        def r(n):
            # This makes me cry at how horribly beautiful it is
            return int(hashlib.md5(str(nz * n)).hexdigest()[-8:], 16) % 5

        nx += r(nx)
        ny += r(ny)

        return nx, ny, nz