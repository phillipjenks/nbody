# N-Body Simulator

This simulator is an RK4 based N-Body gravity simulator written in C++. Included in the project is the source and a set of utilities written in Python for building initial conditions
and visualization. THIS IS STILL IN THE VERY EARLY STAGES OF DEVELOPMENT. This means that config params might change and that the sim shouldn't be expected to be entirely stable.

## Dependencies
- Python 2.7
-- The visualization scripts use [matplotlib](http://matplotlib.org/) to create individual frames. Depending on the state of your python installation, matplotlib recomends 
installing some standalone Python environments that support the full [SciPy stack](http://www.scipy.org/install.html). I found the easiest way is just to use pip
```python
pip install matplotlib
```
-- The visualization scripts also use ffmpeg to create an mp4. This repo includes a 64-bit version of ffmpeg for windows (this will likely change) so you should replace this for 32-bit Windows.

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
- TotalTime: Total simulation time
- TimeStep: The simulation time step
- OutputFrequency: Amount of time in between data dumps (this name will likely change)
- GravityStrength: Constant parameter that defines the strength of gravity
- SofteningParam: Constant that is added to r^2 in the denominator of the gravity equation to avoid numerical errors from dividing by small numbers
- DebugOutput: (0 or 1) Controls detail of output. 0 is recommended unless you're debugging your sim parameters.
