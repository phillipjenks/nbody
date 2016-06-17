from body import Body

class BodyBuilder:

	def __init__(self):

		self.bodies = []

	def build_bodies(self):

		# As a default, just build four bodies in a square
		for x in [-1, 1]:
			for y in [-1, 1]:
				self.bodies.append(Body(1, [x, y, 0], [0, 0, 0]))

		return self.bodies