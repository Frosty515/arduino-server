SHELL := /bin/bash

cxx_source_files := $(shell find src -name *.cpp)
cxx_object_files := $(patsubst src/%.cpp, bin-int/%.cpp.o, $(cxx_source_files))

CXX = g++
AR = ar
CXXFLAGS = -m64 -std=c++20 -Wall -Wextra -Isrc -Iinclude -O2 -g
TARGET = bin/libserial.a

.PHONY: all build clean

all: clean .WAIT build
	@echo --------------
	@echo Build Complete
	@echo --------------

build: $(cxx_object_files)
	@mkdir -p bin
	@echo -------
	@echo Linking
	@echo -------
	$(AR) rcs $(TARGET) $(cxx_object_files)

clean:
	@rm -fr bin bin-int

$(cxx_object_files): bin-int/%.cpp.o : src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -o $@ -c $(patsubst bin-int/%.cpp.o, src/%.cpp, $@) $(CXXFLAGS)
