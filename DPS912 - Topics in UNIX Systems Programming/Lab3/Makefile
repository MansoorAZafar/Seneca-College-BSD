COMPILER=g++
OPTIONS=-Wall -Werror -Wshadow
TARGET=Lab3

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)

all: $(TARGET)

%.o: %.cpp
	$(COMPILER) $(OPTIONS) -c $< -o $@

$(TARGET): $(OBJS)
	$(COMPILER) $(OPTIONS) $(OBJS) -o $@	

clean:
	rm -f $(TARGET) *.o

.PHONY: all clean
	
