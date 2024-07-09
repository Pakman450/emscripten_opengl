# Makefile for compiling hello_triangle with Emscripten

# Compiler
EMCC = emcc

# Compiler flags
CXXFLAGS = -std=c++11
EMFLAGS = -s USE_SDL=2 -s FULL_ES2=1 -s WASM=0 -s ENVIRONMENT=web

# Where the nlohmann-json libraries are
INCLUDE = -I$(JSONBASE)


# Source files
SOURCES = hello_triangle.cpp events.cpp camera.cpp

# Output file
OUTPUT = ../em_main.js

# Default target
all: $(OUTPUT)

# Rule to compile the project
$(OUTPUT): $(SOURCES)
	$(EMCC) $(CXXFLAGS) $(SOURCES) $(EMFLAGS) $(INCLUDE) -o $(OUTPUT)

# Clean target
clean:
	rm -f $(OUTPUT)

.PHONY: all clean
