CC=g++
CFLAGS=-I
CFLAGS+=-Wall
LOGGER_FILE=Logger.cpp
FILES=$(LOGGER_FILE)
FILES+=Automobile.cpp
FILES+=TravelSimulator.cpp
SERVER_FILES=LogServer.cpp
LIBS=-lpthread

all: travel server

travel: $(FILES)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

server: $(SERVER_FILES)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	rm -f *.o travel server *.log
	
