import sys, os
sys.path.append(os.path.join(os.getcwd(), '..'))
sys.path.append(os.path.join(os.getcwd(), '..', 'visualization'))

from subprocess import Popen

from problem_builder import ProblemBuilder
import visualize as vis

def main(problem):

	print '\nBuilding Problem: ' + problem
	builder = ProblemBuilder(problem)
	builder.build_problem()

	args = ['nbody.exe', os.path.join(problem, 'bodies.txt')]
	if not os.path.exists(os.path.join(os.getcwd(), problem, 'bodies.txt')):
		print 'Unable to find initial condition for problem. Problem was not built correctly.'
		return

	if os.path.exists(os.path.join(os.getcwd(), problem, 'config.txt')):
		args.extend(['-c', os.path.join(problem, 'config.txt')])

	print '\nRunning problem simulation'
	pipe = Popen(args, shell=True)
	pipe.wait()

	print '\nRunning problem visualization'
	vis.build_imgs(**builder.visualization_config)

if __name__ == "__main__":

	if len(sys.argv) < 2:
		print 'Usage: python run_test.py <problem>'
	else:
		main(sys.argv[1])