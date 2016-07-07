import os

class ConfigFileBuilder:

	def __init__(self, problem):

		self.problem = problem

		self.config = {
			'TimeStep': 0.01,
			'OutputFrequency': 0.01,
			'TotalTime': 1,
			'SofteningParam': 0.0025,
			'GravityStrength': 0.001,
			'DebugOutput': 1,
			'Solver': 'rk4'
		}

		self.visualization_config = {}

	def build_file(self):

		file_path = os.path.join(os.getcwd(), self.problem, 'config.txt')

		file_out = open(file_path, 'wt')

		config_text = []
		for key in self.config.keys():
			config_text.append(key + ' ' + str(self.config[key]))

		file_out.write('\n'.join(config_text))

		file_out.close()