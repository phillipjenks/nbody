import importlib, os, sys, inspect
from body_file_builder import BodyFileBuilder

class ProblemBuilder:

	def __init__(self, problem):

		self.problem = problem
		self.BuilderModule = None
		self.ConfigModule = None

		self.visualization_config = {}

		sys.path.append(os.path.join(os.getcwd(), problem))

		try:
			self.BuilderModule = importlib.import_module('problem')
		except ImportError, err:
			print 'ERROR: Unable to import problem builder for problem ' + problem
			print err
			return

		if 'Problem' not in [x[0] for x in inspect.getmembers(self.BuilderModule)]:
			self.BuilderModule = None
			print "ERROR: Expected class name 'Problem' in " + os.path.join(problem, 'problem.py')
			return

		# Now check for optional config builder
		try:
			self.ConfigModule = importlib.import_module('config')
		except ImportError, err:
			print err
			print "No config detected. Using default or already existing 'config.txt'"

		if self.ConfigModule and 'Config' not in [x[0] for x in inspect.getmembers(self.ConfigModule)]:
			self.ConfigModule = None
			print "WARN: Found config builder module but expected class name 'Config' in " + os.path.join(problem, 'config.py')
			print "WARN: Using default or already existing 'config.txt'"

	def build_problem(self):

		if not self.BuilderModule:
			return

		body_builder = self.BuilderModule.Problem()
		file_builder = BodyFileBuilder(self.problem)

		file_builder.build_file(body_builder.build_bodies())

		if self.ConfigModule:
			config_builder = self.ConfigModule.Config(self.problem)
			config_builder.build_file()
			self.visualization_config = config_builder.visualization_config

