COMPILER=g++
OPTIONS=-g -std=c++17 -pedantic -Wall -Wextra -Werror -Wshadow -Wconversion -Wunreachable-code
COMPILE=$(COMPILER) $(OPTIONS)
BUILD=build

all: program

program: Lab1.cpp
	$(COMPILE) $< -o $@

build:
	mkdir -p $(BUILD)

run: all
	./program

clean:
	rm -rf $(BUILD) program

.PHONY: all build clean run