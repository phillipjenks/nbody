# N-Body Simulator

This simulator is an N-Body gravity simulator written in C++. Included in the project is the source and a set of utilities written in Python for building initial conditions
and visualization. THIS IS STILL IN THE VERY EARLY STAGES OF DEVELOPMENT. This means that config params might change and that the sim shouldn't be expected to be entirely stable.

## Dependencies
- Python 2.7
- The visualization scripts use [matplotlib](http://matplotlib.org/) to create individual frames. Depending on the state of your python installation, matplotlib recomends 
installing some standalone Python environments that support the full [SciPy stack](http://www.scipy.org/install.html). I found the easiest way is just to use pip
```python
pip install matplotlib
```
- The visualization scripts also use [FFmpeg](https://ffmpeg.org/) to create an mp4. ffmpeg needs to be in your PATH for this to work. 

## Usage
The problem initial condition is specified in a text file that lists the individual bodies on separate lines with mass, position components, and velocity components separated by spaces.
```
mass_1 pos_x pos_y pos_z vel_x vel_y vel_z
.
.
.
mass_n ...
```

Usage the `-c` argument you can provide an optional configuration file as input to set up the sim parameters. These parameters are
- TotalTime: Total simulation time. Defaults to 1.
- TimeStep: The simulation time step. Defaults to 0.01.
- OutputFrequency: Amount of time in between data dumps (this name will likely change). Defaults to 0.01.
- GravityStrength: Constant parameter that defines the strength of gravity. Defaults to 0.001.
- SofteningParam: Constant that is added to r^2 in the denominator of the gravity equation to avoid numerical errors from dividing by small numbers. Defaults to 0.0025.
- Solver: ('rk4' or 'newtonian') Sets the integration scheme. Defaults to 'rk4'.
- DebugOutput: (0, 1, T, True, F, or False) Controls detail of output. False is recommended unless you're debugging your sim parameters. Defaults to true.

## Test Problems

Included in this repo are several test problems. To run an individual test problem

- build the nbody executable
- cd into the `test` directory
- run `python run_test.py <problem_name>`

This will build the body and config files for the test problem, run the simulation, and create the output movie `nbody_out.mp4`. The file `profile_data` will also be created. It shows some time profiling stats for the test problem. 

To create your own test problem, you will need to provide a `problem.py` file in your test problem directory. `problem.py` should define a class `Problem` that inherits from the `BodyBuilder` utility class in the `problem_builder` module. You need to override the `build_bodies` method, which returns a list of body objects. These bodies will be used to create your problem's initial condition. You can also provide a `config.py` file, which defines the class `Config` (inherits from `ConfigFileBuilder`) in order to provide custom params. Providing your own `config.txt` file that you build yourself is also sufficient. See the included test problems for examples.