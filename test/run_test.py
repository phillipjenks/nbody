from subprocess import Popen
import os

pipe = Popen(['nbody.exe', '-c', 'nbody_config.txt', 'nbody_test_bodies.txt'], shell=True)
pipe.wait()

pipe = Popen(['python', os.path.join(os.getcwd(), '..', 'visualization', 'visualize.py')], shell=True)
pipe.wait()

