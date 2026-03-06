CC := g++
CFLAGS := -Iinclude -g
LIBS := -lSDL3 -lSDL3_image
BINARY := bin/run
SOURCES := $(shell find src/ -type f)
OBJECTS := $(SOURCES:src/%.cpp=build/%.o)
SUBDIRS := $(shell find src/ -type d)

all: dir $(BINARY) 

$(BINARY): $(OBJECTS)
	$(CC) $(CFLAGS) $(LIBS) $^ -o $@

$(OBJECTS): build/%.o : src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

dir:
	@mkdir -p bin $(SUBDIRS:src/%=build/%)

clear:
	@rm -fr build bin