import os, sys, math
sys.path.append(os.path.join(os.getcwd(), 'test_util'))

from problem_builder import BodyBuilder
from galaxy_builder import GalaxyBuilder

class Problem(BodyBuilder):

	def __init__(self):
		BodyBuilder.__init__(self)

	def build_bodies(self):

		builder = GalaxyBuilder([0, 0, 0], [0, 0, 0], 50)

		return builder.build_galaxy(300)