import os, sys, math
sys.path.append(os.path.join(os.getcwd(), '..', '..'))

from problem_builder import BodyBuilder
from problem_builder import Body

class Problem(BodyBuilder):

	def __init__(self):
		BodyBuilder.__init__(self)

	def build_bodies(self):

		self.bodies.append(Body(1, [0, 0, 0], [0, 0, 0]))

		r = 1

		# GM / r^2 = v^2 / r
		# => v = sqrt(GM / r)

		self.bodies.append(Body(0.00001, [r, 0, 0], [0, math.sqrt(1 / float(r)), 0]))

		return self.bodies		