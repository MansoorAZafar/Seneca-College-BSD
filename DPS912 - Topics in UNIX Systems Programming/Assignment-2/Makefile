# TODO
INCLUDE_DIR=include
DEPENDENCIES_DIR=dependencies
CORE_DIR=core

CORE_FILES=$(wildcard $(CORE_DIR)/*.cpp)

COMPILER=g++
OPTIONS=-Wall -Werror -std=c++20 -Wunreachable-code -Wconversion -Wshadow -Wextra -I$(INCLUDE_DIR) -I$(DEPENDENCIES_DIR)  $(CORE_FILES)
COMPILE=$(COMPILER) $(OPTIONS)

all: foo

foo:
	$(COMPILE) src/ticketClient.cpp -o client.exe
	$(COMPILE) src/ticketServer.cpp -o server.exe
	$(COMPILE) src/ticketMonitor.cpp -o monitor.exe

clean:
	rm -rf *.exe *.log

.PHONY: clean foo 