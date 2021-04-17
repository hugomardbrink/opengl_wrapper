# simple openGL wrapper 

This is a wrapper for the [openGL](https://www.opengl.org//) api meant for Windows. It will be based on the modern 3.3+ iteration of openGL.

It is developed in core-profile.

The project is a learning experience using different educational material found online. 
 
# Build

This project is built in [Visual Studio 2019](https://visualstudio.microsoft.com/vs/) due to the simplicity.

The following libraries are needed:

[GLAD](https://glad.dav1d.de) - Provides available openGL extensions for target platform

[GLFW3](https://www.glfw.org/) - Window & context management

[GLM](https://github.com/g-truc/glm) - Mathematics library with GLSL specifications

[STB_IMAGE](https://github.com/nothings/stb) - Loads images

# Configuring

 ## GLAD
 Use the web downloader and use `Core` under profile and gl version `3.3`. Rest should be left as is.
 
 Put `glad.c` in the `/src` folder. Then put `glad.h` in `dependencies/include/glad` and `khrplatform.h` in `dependencies/include/KHR`.
 
 ## GLFW3
 Download from the website and put the Visual Studio 2019 binary `glfw3.lib` in `dependecies/binaries`.
 
 ## GLM
 Download the repo and put the `glm` root folder in `dependencies/include`.
 
 ## STB_IMAGE
 Download `stb_image.h` and put it in `/src`.
 
 After this create `stb_image.cpp` in `/src` and add the following code to it:
 
      #define STB_IMAGE_IMPLEMENTATION
      #include "stb_image.h"
      
## Other

If linking is not working properly, ensure following solution settings:
* `$(ProjectDir)dependencies\include` is added as **Additional Include Directories**.
* `$(ProjectDir)dependencies\binaries` is added under **Additional Library Directories**.
* `glfw3.lib` is added under **Additional dependencies**.

# Side note
`main.cpp`, shaders and images in `assets/textures` and `/shaders` are placeholders to demonstrate how the wrapper is used.
