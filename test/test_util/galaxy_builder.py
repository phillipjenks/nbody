import random, os, sys, math
sys.path.append(os.path.join(os.getcwd(), '..', '..'))

from problem_builder import Body

random.seed()

class GalaxyBuilder:

	def __init__(self):

		self.mass = 1e8

	# Assumes rotating about the origin
	def _calculate_vel(self, pos):

		# GM / r^2 = v^2 / r => v = sqrt(GM / r)
		r = math.sqrt(pos[0] * pos[0] + pos[1] * pos[1])
		v_mag = math.sqrt(self.mass / r)

		return [-v_mag * pos[1] / r, v_mag * pos[0] / r, 0]

	def _build_star(self, pos, vel, radius, inner_radius):

		r = 0
		while r == 0:
			r = random.random() * (radius - inner_radius) + inner_radius

		th = random.random() * 360

		x = r * math.cos(math.radians(th))
		y = r * math.sin(math.radians(th))

		star_pos = [x, y, 0]
		star_vel = self._calculate_vel(star_pos)

		for i in xrange(len(star_pos)):
			star_pos[i] += pos[i]

		for i in xrange(len(star_vel)):
			star_vel[i] += vel[i]

		return Body(1, star_pos, star_vel)


	def build_galaxy(self, pos = [0, 0, 0], vel = [0, 0, 0], radius = 50, inner_radius = 1, num_stars = 100):

		bodies = [Body(self.mass, pos, vel)]

		for i in xrange(num_stars):
			bodies.append(self._build_star(pos, vel, radius, inner_radius))

		return bodies

