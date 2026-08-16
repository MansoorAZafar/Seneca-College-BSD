INCLUDE_DIR=include
SRC_DIR=src

TARGET=lab7.exe
SRC_FILES=$(wildcard $(SRC_DIR)/*.cpp)

COMPILER=g++
OPTIONS=-Wall -Werror -std=c++17 -Wunreachable-code -Wconversion -Wshadow -Wextra -I$(INCLUDE_DIR)
COMPILE=$(COMPILER) $(OPTIONS)

all: $(TARGET)

$(TARGET):
	$(COMPILE) $(SRC_FILES) -o $@

extra:
	$(COMPILE) extra-cpp17.cpp -o extra.exe

clean:
	rm -rf *.exe *.o
