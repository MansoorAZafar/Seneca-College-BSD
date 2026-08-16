COMPILER=g++
OPTIONS=-std=c++20 -Wall

build: q1.cpp q3.cpp
	$(COMPILER) $(OPTIONS) q1.cpp -o q1.exe
	$(COMPILER) $(OPTIONS) q3.cpp -o q3.exe

clean:
	rm -f *.exe


all: build

.PHONY: clean, all, build 