# Docker image
DOCKER_IMAGE = emscripten/emsdk:3.1.53 # uncomment me to use the older image

# Build directory
BUILD_DIR = build

# Source directory
SRC_DIR = $(shell pwd)

# CMake options
CMAKE_OPTS = -DCMAKE_TOOLCHAIN_FILE=/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake

# Build target
all: $(BUILD_DIR) $(BUILD_DIR)/index.html

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/index.html: $(BUILD_DIR)
	docker run --rm -v $(SRC_DIR):/src -w /src $(DOCKER_IMAGE) cmake -B$(BUILD_DIR) $(CMAKE_OPTS)
	docker run --rm -v $(SRC_DIR):/src -w /src $(DOCKER_IMAGE) cmake --build $(BUILD_DIR)

# Clean target
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean $(BUILD_DIR)