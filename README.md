# prend
A really basic OpenGL 3D renderer, written in object-oriented C++. It's just a learning project; don't take it too seriously.

I'm building this loosely alongside [this excellent tutorial](http://opengl.datenwolf.net/gltut/html/index.html), although the vast majority of my code differs strongly from the example structure. (FBX importing isn't in the tutorial at all, for example.)

The short-term goals:
- Load vertex position and color data from Autodesk FBX format (mostly done)
- Get this model data into VRAM through OpenGL (done)
- Load GLSL shader code to apply to those models (done)
- Handle perspective and other TRS matrix operations (done)
- Provide a matrix-free API for ^these operations
- Map file-loaded textures to models
- Apply simple lighting to models
- Draw the final image to an OpenGL window (done)

# building
Who knows why you'd want to, but,

You can build using either the provided Visual Studio solution or the provided batch builders, depending on which you trust more (or less). If using the batch builders, you'll need to set up your root paths in *util/setup_env.bat*.

The majority of the renderer (*prend*) is a statically linked library, used by the actual excutable entry point (*pexe*). The static library is emitted by default into a *lib/* directory inside the project root.

The project requires some external libraries:
- SDL2 is used for window management
- GLEW is used to acquire GL functions
- Autodesk's FBX SDK is used to import FBX model data

Both the VS solution and the batch builders expect to find these in the aforementioned *lib/* directory. Make sure to set up the approprate paths -- either in prend's MSVC++ project or the *util/setup.bat* file -- once you acquire the libraries.

The batch builders use Clang++ in C++17 mode. If you'd prefer to substitute your own compiler, you'll need to modify *build_prend.bat* and *build_pexe.bat* accordingly. I'll assume you know what you're doing if you're taking that step.
