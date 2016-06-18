import os, sys, math
sys.path.append(os.path.join(os.getcwd(), 'test_util'))

from problem_builder import BodyBuilder
from galaxy_builder import GalaxyBuilder

class Problem(BodyBuilder):

	def __init__(self):
		BodyBuilder.__init__(self)

	def build_bodies(self):

		builder = GalaxyBuilder()

		self.bodies.extend(builder.build_galaxy(pos = [100, 100, 0], vel = [-100, -300, 0], radius = 50, inner_radius = 5, num_stars = 300))
		self.bodies.extend(builder.build_galaxy(pos = [-100, -100, 0], vel = [300, 100, 0], radius = 50, inner_radius = 5, num_stars = 300))

		return self.bodies