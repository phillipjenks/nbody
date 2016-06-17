import os, sys
sys.path.append(os.path.join(os.getcwd(), '..', '..'))

from problem_builder import ConfigFileBuilder

class Config(ConfigFileBuilder):

	def __init__(self, problem):
		ConfigFileBuilder.__init__(self, problem)

		self.config['TimeStep'] = 0.0001
		self.config['OutputFrequency'] = 0.001
		self.config['TotalTime'] = 10
		self.config['SofteningParam'] = 0.0002
		self.config['GravityStrength'] = Config.calculate_G()
		self.config['DebugOutput'] = 0

	@staticmethod
	def calculate_G():

		# with mass in solar masses, distance in AU, and time in seconds
		g0 = 6.67e-11 # m^3 / kg / s^2

		# conversions
		kgToSolar = 2e30 # kg / m_solar
		mToAu = 1.5e11 # m / AU
		sToYr = 3.154e7 # s / year

		return g0 / (mToAu * mToAu * mToAu) * kgToSolar * sToYr * sToYr # AU^3 / solar_mass / year^2