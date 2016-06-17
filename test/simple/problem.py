import os, sys
sys.path.append(os.path.join(os.getcwd(), '..', '..'))

from problem_builder import BodyBuilder

class Problem(BodyBuilder):

	def __init__(self):
		BodyBuilder.__init__(self)

	def build_bodies(self):

		return BodyBuilder.build_bodies(self)