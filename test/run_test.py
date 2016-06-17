import sys, os
sys.path.append(os.path.join(os.getcwd(), '..'))

from subprocess import Popen

from problem_builder import ProblemBuilder

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
	pipe = Popen(['python', os.path.join(os.getcwd(), '..', 'visualization', 'visualize.py')], shell=True)
	pipe.wait()

if __name__ == "__main__":

	if len(sys.argv) < 2:
		print 'Usage: python run_test.py <problem>'
	else:
		main(sys.argv[1])