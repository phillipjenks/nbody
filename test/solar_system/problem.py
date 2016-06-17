import math

from problem_builder import BodyBuilder
from problem_builder import Body

from config import Config

class Problem(BodyBuilder):

	def __init__(self):
		BodyBuilder.__init__(self)

		self.g = Config.calculate_G()

	def _get_vel(self, dist):
		# GM / r^2 = v^2 / r
		# => v = sqrt(GM / r), M = 1
		return math.sqrt(self.g / float(dist))

	def _build_body(self, mass, dist):
		return Body(mass, [dist, 0, 0], [0, self._get_vel(dist), 0])

	def build_bodies(self):

		# The sun, M = 1
		self.bodies.append(Body(1, [0, 0, 0], [0, 0, 0]))

		planets = []
		# Mercury, M = 1.652e-7, r = 0.39
		planets.append((1.652e-7, .39))
		
		# venus, M = 2.447e-6, r = .723
		planets.append((2.447e-6, .723))

		# Earth, M = 3.003e-6, r = 1
		planets.append((3.003e-6, 1))

		# Mars, M = 3.213e-7, r = 1.524
		planets.append((3.213e-7, 1.524))

		# Jupiter, M = 9.543e-4, r = 5.203
		planets.append((9.543e-4, 5.203))

		# Saturn, M = 2.857e-4, r = 9.539
		planets.append((2.857e-4, 9.539))

		# Uranus, M = 4.365e-5, r = 19.18
		planets.append((4.365e-5, 19.18))

		# Neptune, M = 5.149e-5, r = 30.06
		planets.append((5.149e-5, 30.06))

		for planet in planets:
			self.bodies.append(self._build_body(planet[0], planet[1]))

		return self.bodies		