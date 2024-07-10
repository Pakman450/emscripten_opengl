# Makefile for compiling hello_triangle with Emscripten

# Compiler
EMCC = em++

# Compiler flags
CXXFLAGS = -std=c++11
SHADERFLAGS = --embed-file shaders --no-entry
EMFLAGS = -s USE_SDL=2 -s FULL_ES3 -s WASM=0 -s ENVIRONMENT=web $(SHADERFLAGS)

# Where the nlohmann-json libraries are
INCLUDE =

# Source files
SOURCES = main.cpp
# Output file
OUTPUT = em_main.js

# Default target
all: $(OUTPUT)

# Rule to compile the project
$(OUTPUT): $(SOURCES)
	$(EMCC) $(CXXFLAGS) $(SOURCES) $(EMFLAGS) $(INCLUDE) -o $(OUTPUT)

# Clean target
clean:
	rm -f $(OUTPUT)

.PHONY: all clean
