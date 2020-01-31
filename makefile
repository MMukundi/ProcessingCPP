CC = g++ -std=c++17 -ggdb
GLLibs = -lglfw -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

source := $(filter-out main.cpp, $(wildcard *.cpp))

objects := $(patsubst %.cpp,ObjectFiles/%.o,$(source))

ObjectFiles/%.o:%.cpp
	$(CC) -c -o $@ $<

Processing: $(objects) Processing.h
	libtool -g -static $(objects) -o Processing

Example: Processing Example.cpp
	$(CC) -o Example Example.cpp Processing $(GLLibs)