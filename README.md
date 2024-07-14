## Demo

Minimal repro for [issue](https://github.com/emscripten-core/emscripten/issues/10542)

### Project Structure

```
.
├── CMakeLists.txt     # CMake configuration file
├── index.html         # HTML file to integrate with Emscripten output
├── main.c             # Main C/C++ source file
├── Makefile           # Builder for convenience when pulling images
├── pre.js             # JavaScript bindings file to disable inputs
├── build/                 # Build directory (auto-generated)
│   ├── example.js         # Generated JavaScript file
│   ├── example.wasm       # Generated WebAssembly file
|   ├── index.html         # Copied index.html from src
│   └── ...
└── README.md
```

### Start the Emscripten Docker container and build the project:

To build with the latest emsdk image, run:

```
make;
```

To adjust the docker image version of emsdk, run:

```
make DOCKER_IMAGE_VERSION=3.1.53;
```

The emsdk image version shown above allows html inputs to recieve their respective events when disabled.

### Run the Project:

You will need to start a file server of some kind, I am using python:

```
cd ./build && python -m http.server;
```

Open the index.html file in a web browser at http://localhost:8000/index.html to run the compiled demo.
