# PhysicsEngine

### Technologies used
* C++17
* Makefile
* Shell script
* Doxygen (for inline documentation)
* SFML (for demo)
* Valgrind & GDB (for debugging)

### Installing requirements
PhysicsEngine has been developed with Debian 9

For Debian based distributions
```
sudo apt-get install build-essential
sudo apt-get install make
sudo apt-get install doxygen
sudo apt-get install libsfml-dev
```
Notice: old SFML versions (< 2.4) don't work and in this case demo can't be compiled.
However, PhysicsEngine itself will work just fine without SFML.

### USAGE
PhysicsEngine shared object file, libphysengine, can be compiled using test-directory Makefile. Then by including the headers (/include) and linking with libphysengine PhysicsEngine can be used in any application.

/demo contains a demo which demonstrates capabilities of PhysicsEngine with graphics created with SFML. More info about demo can be found from demo-directory Readme.

/test contains unit tests for PhysicsEngine. More info in test-directory Readme.

To create documentation, run command (in project root directory):
```
doxygen
```
Essential documentation now in doc/index.html

### Features
* 2D rigid body physics
* Simple collisions
* Support for dynamic and static objects
* Support for multiple threads in updating objects
* Possibility to apply both forces and linear velocities

### Limitations
* Currently only rectangle shape support
* No support for sensors nor joints
* No object rotation implemented
* No real-time collision detection implemented -> fast moving objects can pass through
* In general physics related implementations lacking

### Bugs
* Especially x-dimensional gravity know to cause glitches
* Objects can cross each others frames in certain situations
