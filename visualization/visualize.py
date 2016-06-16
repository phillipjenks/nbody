import os
import matplotlib.pyplot as plt

DATA_DIRECTORY = os.path.join(os.getcwd(), 'output')
IMAGE_OUTPUT = os.path.join(os.getcwd(), 'imgs')

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

def build_imgs():

	data_list = os.listdir(DATA_DIRECTORY)

	data_points = []

	for data_file in data_list:
		data_points.append(extract_data_point_from_file(data_file))

	# extract min and max
	maxx = 0
	maxy = 0

	formatted_data = []
	data_number = 0
	for pt in data_points:

		formatted_point = {'data_number': data_number, 'time': pt['time'], 'x': [], 'y': []}
		data_number += 1

		for body_pt in pt['pts']:
			formatted_point['x'].append(body_pt[0])
			formatted_point['y'].append(body_pt[1])

			maxx = max(maxx, abs(body_pt[0]))
			maxy = max(maxy, abs(body_pt[1]))

		formatted_data.append(formatted_point)

	# let's build our plots
	for pt in formatted_data:

		plt.scatter(pt['x'], pt['y'], marker='*')
		plt.title('time = ' + str(pt['time']))
		plt.grid(True)
		plt.xlim(-maxx, maxx)
		plt.ylim(-maxy, maxy)

		plt.savefig(os.path.join(IMAGE_OUTPUT, 'img_' + str(pt['data_number'])))


if __name__ == "__main__":
	if not os.path.exists(IMAGE_OUTPUT):
		os.makedirs(IMAGE_OUTPUT)
	build_imgs()