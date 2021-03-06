import os, shutil, webbrowser
from subprocess import Popen
import matplotlib.pyplot as plt

DATA_DIRECTORY = os.path.join(os.getcwd(), 'output')
IMAGE_OUTPUT = os.path.join(os.getcwd(), 'imgs')
MOVIE_OUTPUT = os.path.join(os.getcwd(), 'nbody_out.mp4')
SCRIPT_DIR = os.path.dirname(os.path.realpath(__file__))

def extract_data_point_from_file(file_name):

	data_point = {'time': 0, 'pts': []}

	with open(os.path.join(DATA_DIRECTORY, file_name), 'rt') as in_file:
		file_lines = [x.strip('\n') for x in in_file.readlines()]

		for dat in file_lines:
			line_data = dat.split(',');
			if line_data[0] == 'time':
				data_point['time'] = float(line_data[1])
			else:
				data_point['pts'].append([float(line_data[1]), float(line_data[2]), float(line_data[3])])

	return data_point

def build_imgs(**kwargs):

	custom_lim = None
	if kwargs is not None:
		if 'custom_lim' in kwargs.keys():
			custom_lim = kwargs['custom_lim']

	if os.path.exists(IMAGE_OUTPUT):
		shutil.rmtree(IMAGE_OUTPUT)

	if os.path.exists(MOVIE_OUTPUT):
		os.remove(MOVIE_OUTPUT)

	os.makedirs(IMAGE_OUTPUT)

	data_list = os.listdir(DATA_DIRECTORY)
	total_points = len(data_list)

	data_points = []
	data_number = 0

	print ''

	for data_file in data_list:
		print '{0}\r'.format('Extracting Data: ' + str(int(100 * float(data_number) / total_points)) + '%'),
		data_number += 1
		data_points.append(extract_data_point_from_file(data_file))

	print '{0}\r'.format('Extracting Data: 100%')
	# extract min and max
	maxx = 0
	maxy = 0

	formatted_data = []
	data_number = 0
	
	for pt in data_points:

		print '{0}\r'.format('Formatting Data: ' + str(int(100 * float(data_number) / total_points)) + '%'),

		formatted_point = {'data_number': data_number, 'time': pt['time'], 'x': [], 'y': []}
		data_number += 1

		for body_pt in pt['pts']:
			formatted_point['x'].append(body_pt[0])
			formatted_point['y'].append(body_pt[1])

			maxx = max(maxx, abs(body_pt[0]))
			maxy = max(maxy, abs(body_pt[1]))

		formatted_data.append(formatted_point)

	print '{0}\r'.format('Formatting Data: 100%')

	if maxx == 0:
		maxx = 1
	if maxy == 0:
		maxy = 1

	maxxy = max(maxx, maxy)

	if custom_lim:
		maxxy = custom_lim
	else:
		maxxy *= 2

	# let's build our plots
	for pt in formatted_data:

		print '{0}\r'.format('Plotting Data: ' + str(int(100 * float(pt['data_number']) / total_points)) + '%'),

		plt.clf()
		plt.scatter(pt['x'], pt['y'], marker='*')
		plt.title('time = ' + str(pt['time']))
		plt.grid(True)
		plt.xlim(-maxxy, maxxy)
		plt.ylim(-maxxy, maxxy)

		plt.savefig(os.path.join(IMAGE_OUTPUT, 'img_' + str(pt['data_number']).zfill(4)))

	print '{0}\r'.format('Plotting Data: 100%')

	print 'Creating Movie With FFMPEG'

	pipe = Popen(['ffmpeg.exe', '-framerate', '25', '-i', os.path.join(IMAGE_OUTPUT, 'img_%04d.png'), '-c:v', 'libx264', '-r', '25', '-pix_fmt', 'yuv420p', MOVIE_OUTPUT])
	pipe.wait()

	webbrowser.open(MOVIE_OUTPUT)


if __name__ == "__main__":
	build_imgs()