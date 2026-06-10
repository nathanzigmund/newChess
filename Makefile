# Compiler settings
CXX = g++
CXXFLAGS = -g -I./include -Wall -std=c++17

#SFML libraries to link
SFML_FLAGS = -lSDL2 -lSDL2_image
LDFLAGS = $(shell pkg-config --libs -sdl2 -sdl2_image )
# Target executable name
TARGET = bin/chess

# Files
SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:src/%.cpp=obj/%.o)

# Default rule
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	@mkdir -p bin
	$(CXX) $(OBJS) -o $(TARGET) $(SFML_FLAGS)

# Compile source files to object files
obj/%.o: src/%.cpp
	@mkdir -p obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -rf obj bin
