
from problem_builder import ConfigFileBuilder

class Config(ConfigFileBuilder):

	def __init__(self, problem):
		ConfigFileBuilder.__init__(self, problem)

		self.config['TimeStep'] = 0.001
		self.config['OutputFrequency'] = 0.1
		self.config['TotalTime'] = 10
		self.config['SofteningParam'] = 0.0002
		self.config['GravityStrength'] = 1
		self.config['DebugOutput'] = 0