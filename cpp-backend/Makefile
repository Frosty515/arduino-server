SHELL := /bin/bash

cxx_source_files := $(shell find src -name *.cpp)
cxx_object_files := $(patsubst src/%.cpp, bin-int/%.cpp.o, $(cxx_source_files))

asm_source_files := $(shell find src -name *.asm)
asm_object_files := $(patsubst src/%.asm, bin-int/%.asm.o, $(asm_source_files))

c_source_files := $(shell find src -name *.c)
c_object_files := $(patsubst src/%.c, bin-int/%.c.o, $(c_source_files))

CXX = g++
CC = gcc
ASM = nasm
LD = g++
CXXFLAGS = -m64 -std=c++20 -Wall -Wextra -Isrc -Idependencies/libserial/include -O2 -fno-exceptions -g
CFLAGS = -m64 -std=c17 -Wall -Wextra -Isrc -O2 -g
ASMFLAGS = -f elf64
LDFLAGS = -lcjson dependencies/libserial/bin/libserial.a
TARGET = bin/cpp-backend

.PHONY: all build clean clean-all run dependencies

all: clean dependencies .WAIT build
	@echo --------------
	@echo Build Complete
	@echo --------------

build: $(cxx_object_files) $(asm_object_files) $(c_object_files)
	@mkdir -p bin
	@echo -------
	@echo Linking
	@echo -------
	$(LD) $(asm_object_files) $(c_object_files) $(cxx_object_files) -o $(TARGET) $(LDFLAGS)

clean:
	@rm -fr bin bin-int

clean-all:
	@echo ------------
	@echo Cleaning all
	@echo ------------
	@rm -fr bin bin-int
	@make -C dependencies/libserial clean

dependencies:
	@echo ----------------
	@echo Installing deps
	@echo ----------------
ifeq (,$(wildcard dependencies/libserial/bin/libserial.a))
	@make -C dependencies/libserial
endif

run: all
	@echo -------
	@echo Running
	@echo -------
	@$(TARGET)

$(cxx_object_files): bin-int/%.cpp.o : src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -o $@ -c $(patsubst bin-int/%.cpp.o, src/%.cpp, $@) $(CXXFLAGS)

$(asm_object_files): bin-int/%.asm.o : src/%.asm
	@mkdir -p $(dir $@)
	$(ASM) $(ASMFLAGS) $(patsubst bin-int/%.asm.o, src/%.asm, $@) -o $@

$(c_object_files): bin-int/%.c.o : src/%.c
	@mkdir -p $(dir $@)
	$(CC) -o $@ -c $(patsubst bin-int/%.c.o, src/%.c, $@) $(CFLAGS)
