class Body:

	def __init__(self, mass, pos, vel):

		self.mass = mass;
		self.pos = pos;
		self.vel = vel;

	def get_string(self):

		my_dat = [str(self.mass)]
		my_dat.extend([str(x) for x in self.pos])
		my_dat.extend([str(x) for x in self.vel])

		return ' '.join(my_dat)