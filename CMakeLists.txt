cmake_minimum_required(VERSION 3.0)

# Set the project name
project(example)

# Set the C standard
set(CMAKE_C_STANDARD 11)

# Set the source files
set(SRC main.c)

# Specify the target output
set(CMAKE_EXECUTABLE_SUFFIX ".js")

# Path to pre.js
set(PRE_JS "${CMAKE_CURRENT_SOURCE_DIR}/pre.js")

# Add the executable target
add_executable(${PROJECT_NAME} ${SRC})

# Set compiler flags
set_target_properties(${PROJECT_NAME} PROPERTIES
    COMPILE_FLAGS "-O2 -s USE_SDL=2 -s WASM=1"
    LINK_FLAGS "-s USE_SDL=2 \
                --pre-js ${PRE_JS} \
                --shell-file ${CMAKE_CURRENT_SOURCE_DIR}/index.html \
                -s ENVIRONMENT='web' \
                -s EXPORTED_RUNTIME_METHODS=[\"cwrap\"] \
                -s EXPORT_ES6=1 \
                -s MODULARIZE=1"
)

# Copy index.html to build directory
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/index.html ${CMAKE_CURRENT_BINARY_DIR}/index.html COPYONLY)
