import os.path

try:
    import json
except ImportError:
    try:
        import simplejson as json
    except:
        print "No compatible JSON decoder found."
        import sys

        sys.exit()

from space_torus.gl.graphics import *
from entity import *
from space_torus.gl.texture import *
import random


AU = 20 * 100


def load_world(file):
    file = os.path.join(os.path.dirname(__file__), file)
    world_dir = os.path.dirname(file)
    with open(file) as f:
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

            planet_id = glCompile(glSphere, radius, int(radius / 2), int(radius / 2), load_texture(os.path.join(world_dir, texture)),
                                  lighting=lighting)
            atmosphere_id = 0
            cloudmap_id = 0
            if 'atmosphere' in info:
                atmosphere_data = info['atmosphere']
                size = e(get('diffuse_size', atmosphere_data))
                atm_texture = os.path.join(world_dir, get('diffuse_texture', atmosphere_data))
                cloud_texture = os.path.join(world_dir, get('cloud_texture', atmosphere_data))
                cloudmap_id = glCompile(glSphere, radius + 2, int(radius / 2), int(radius / 2),
                                        load_texture(cloud_texture), lighting=False)
                atmosphere_id = glCompile(glDisk, radius + 2, radius + size + 2, 30,
                                          load_texture(atm_texture, safe=True))

            world.tracker.append(
                Planet(planet_id, (x, y, z), bounding_radius=radius, rotation=(pitch, yaw, roll), delta=delta,
                       atmosphere=atmosphere_id, cloudmap=cloudmap_id))
            if 'ring' in info:
                ring_data = info['ring']
                texture = os.path.join(world_dir, get('texture', ring_data))
                distance = e(get('distance', ring_data))
                size = e(get('size', ring_data))
                pitch = e(get('pitch', ring_data, pitch))
                yaw = e(get('yaw', ring_data, yaw))
                roll = e(get('roll', ring_data, roll))

                world.tracker.append(
                    Planet(glCompile(glDisk, distance, distance + size, 30, load_texture(texture, safe=True)),
                           (x, y, z),
                           rotation=(pitch, yaw, roll)))
        return world


class World(object):
    def __init__(self):
        self.waypoints = []
        self.tracker = []
        self.tori = []
        self._x = None
        self._y = None
        self._z = None

    def generate_tori(self, dist):
        for w0, w1 in zip(self.waypoints[:-1], self.waypoints[1:]):
            x0, y0, z0 = w0
            x1, y1, z1 = w1
            dx, dy, dz = x1 - x0, y1 - y0, z1 - z0
            tori = dz / dist
            ix = float(dx) / tori
            iy = float(dy) / tori
            x, y, z = w0

            for i in xrange(tori):
                dx = 2 + z / 15000
                dy = min(dx, z / 8000)
                self.tori.append((random.gauss(x, dx), random.gauss(y, dy), z))
                x += ix
                y += iy
                z += dist