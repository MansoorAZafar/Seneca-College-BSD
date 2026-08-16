INCLUDE_DIR=include
CLIENT_DIR=client
SERVER_DIR=server
TEST_DIR=tests
CORE_DIR=core
UTIL_DIR=utility

SERVER_FILES=$(wildcard $(SERVER_DIR)/src/*.cpp)
CLIENT_FILES=$(wildcard $(CLIENT_DIR)/src/*.cpp)
CORE_FILES=$(wildcard $(CORE_DIR)/*/*.cpp)
TEST_FILES=$(wildcard $(TEST_DIR)/*.cpp)
UTIL_FILES=$(wildcard $(UTIL_DIR)/*.cpp)

SERVER_INCLUDE=$(SERVER_DIR)/include
CLIENT_INCLUDE=$(CLIENT_DIR)/include


COMPILER=g++
OPTIONS=-Wall -Werror -std=c++17 -Wunreachable-code -Wconversion -Wshadow -Wextra -I$(INCLUDE_DIR) $(CORE_FILES) $(UTIL_FILES)
COMPILE=$(COMPILER) $(OPTIONS)

BUILD_TARGET=out

SERVER_TARGET=server.exe
CLIENT_TARGET=client.exe

all: app

app: $(BUILD_TARGET)/$(CLIENT_TARGET) $(BUILD_TARGET)/$(SERVER_TARGET)


$(BUILD_TARGET)/$(CLIENT_TARGET): $(CLIENT_FILES) | $(BUILD_TARGET)
	$(COMPILE) -I$(CLIENT_INCLUDE) $(CLIENT_FILES) -o $@

$(BUILD_TARGET)/$(SERVER_TARGET): $(SERVER_FILES) | $(BUILD_TARGET)
	$(COMPILE) -I$(SERVER_INCLUDE) $(SERVER_FILES) -o $@

$(BUILD_TARGET):
	mkdir -p $(BUILD_TARGET)

logger-test:
	$(COMPILE) $(TEST_FILES) -o test.exe

clean:
	rm -rf *.exe *.log $(BUILD_TARGET)