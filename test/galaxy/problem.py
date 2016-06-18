import os, sys, math
sys.path.append(os.path.join(os.getcwd(), 'test_util'))

from problem_builder import BodyBuilder
from galaxy_builder import GalaxyBuilder

class Problem(BodyBuilder):

	def __init__(self):
		BodyBuilder.__init__(self)

	def build_bodies(self):

		builder = GalaxyBuilder()

		return builder.build_galaxy(pos = [10, 10, 0], vel = [-100, -100, 0], radius = 50, inner_radius = 5, num_stars = 300)