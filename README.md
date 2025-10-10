# OpenGL Tutorials
![Water](assets/screenshots/water.png)

This repository contains implementations of various OpenGL tutorials and a
modular engine framework for graphics programming in C++.

The tutorials are taken from [LearnOpenGL](https://learnopengl.com/)
and adapted for this engine framework.

## Features
- Modular engine architecture (core, graphics, renderer, scene, window)
- Asset loader using the Assimp library
- Integration with ImGui (currently directly via OpenGL backend)
- Multiple tutorials covering:
  - Window creation
  - Shaders
  - Textures
  - Transformations
  - Camera and lighting
  - Framebuffers
  - Cubemaps
  - Normal and parallax mapping
  - Blending

## Directory Structure
- `3rd_party/` — External libraries
- `build/` — Visual Studio solution and project files
- `build/bin/` — Compiled binaries for tutorials and engine
- `include/` — Public headers for engine modules and libraries
- `src/` — Source code for engine, asset loader, tutorials, and third-party integrations

## Getting Started
1. **Clone the repository:**
2. **Install dependencies:**
   - Visual Studio 2022 or newer
3. **Open and build the solution:**
   - Open `build/opengl-tutorials.sln` in Visual Studio and build it
. **Run tutorials:**
   - Executables are located in `build/bin/Debug-x64/` and `build/bin/Release-x64/`

## License
This project is licensed under the [MIT License](LICENSE).

## Credits
- [Assimp](https://github.com/assimp/assimp)
- [ImGui](https://github.com/ocornut/imgui)
- [Glad](https://github.com/Dav1dde/glad)
