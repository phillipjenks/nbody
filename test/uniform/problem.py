
from problem_builder import BodyBuilder
from problem_builder import Body

class Problem(BodyBuilder):

	def __init__(self):
		BodyBuilder.__init__(self)

	def build_bodies(self):

		for x in xrange(-10, 11):
			for y in xrange(-10, 11):
				self.bodies.append(Body(1, [x, y, 0], [0, 0, 0]))

		return self.bodies