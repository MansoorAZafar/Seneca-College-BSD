COMPILER=g++
OPTIONS=-g -pedantic -Wall -Wextra -Wshadow -Wconversion -Wunreachable-code
COMPILE=$(COMPILER) $(OPTIONS)
TARGET=Lab2

SRCS := $(wildcard *.cpp)
HEADERS := $(wildcard *.h)
OBJS := $(SRCS:.cpp=.o)


%.o: %.cpp
	$(COMPILER) $(OPTIONS) -c $< -o $@

all: $(TARGET)

$(TARGET): $(OBJS) libPidUtil.a
	$(COMPILE) -o $@ $^ 

.PHONY: all run clean

run:
	./$(TARGET)

clean:
	rm -rf *.o $(TARGET)
