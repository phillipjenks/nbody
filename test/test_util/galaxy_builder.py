import random, os, sys, math
sys.path.append(os.path.join(os.getcwd(), '..', '..'))

from problem_builder import Body

random.seed()

class GalaxyBuilder:

	def __init__(self, pos, vel, radius):

		self.pos = pos
		self.vel = vel
		self.radius = radius

		self.mass = 1e8

	# Assumes rotating about the origin
	def _calculate_vel(self, pos):

		# GM / r^2 = v^2 / r => v = sqrt(GM / r)
		r = math.sqrt(pos[0] * pos[0] + pos[1] * pos[1])
		v_mag = math.sqrt(self.mass / r)

		return [-v_mag * pos[1] / r, v_mag * pos[0] / r, 0]

	def _build_star(self):

		x = 0
		while x == 0:
			x = random.randint(-self.radius, self.radius)

		y = 0
		while y == 0:
			y = random.randint(-self.radius, self.radius)

		star_pos = [x, y, 0]
		star_vel = self._calculate_vel(star_pos)

		for i in xrange(len(star_pos)):
			star_pos[i] += self.pos[i]

		for i in xrange(len(star_vel)):
			star_vel[i] += self.vel[i]

		return Body(1, star_pos, star_vel)


	def build_galaxy(self, num_stars):

		bodies = [Body(self.mass, self.pos, self.vel)]

		for i in xrange(num_stars):
			bodies.append(self._build_star())

		return bodies

