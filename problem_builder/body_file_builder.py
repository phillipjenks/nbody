import os

class BodyFileBuilder:

	def __init__(self, problem):

		self.problem = problem

	def build_file(self, bodies):

		file_path = os.path.join(os.getcwd(), self.problem, 'bodies.txt')

		file_out = open(file_path, 'wt')

		file_out.write('\n'.join([body.get_string() for body in bodies]))

		file_out.close()