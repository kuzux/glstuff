### What that is
Following a bunch of OpenGL tutorials. Nothing fancy.

### What does it take to build?
- Have make installed. Run `make` to build, `make test` to build & run a bunch of random tests. Run `./target/main` after building to actually run the program. Also have a C/C++ Compiler(GCC or Clang) installed to be able to build the thing
- Current dependencies for building are SDL2, OpenGL, GLEW, GLM (will hopefully be removed soon) and Jansson. 
- Tested on OSX Yosemite. Should build and run under Linux as well. No Windows support in sight.

### Future?
- Rewrite GLM stuff as your own math library. Use that instead of GLM and finally move everything to pure C
- Rewrite the obj parsing code to be C, not C++
- Get a scene system working
- Draw more complex objects/scene
- Add support for normal maps etc.
- Geometry shaders? Post-processing effects? HDR?
- Shadows and stuff
- Particle engine?
- Move the behavior of objects into Lua? scripts
- Add sound support (using SDLMixer or something)
- Animation subsystem
- Some UI Support
- Some sort of stacking scenes for menus etc.

- Get a better build system? (with a configure script etc.)
- Write better tests
- A sample game. Maybe a few?
