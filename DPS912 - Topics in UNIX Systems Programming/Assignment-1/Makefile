COMPILER=g++
OPTIONS=-Wall -Werror -std=c++17 -Wunreachable-code -Wconversion -Wshadow -Wextra
COMPILE=$(COMPILER) $(OPTIONS)

BUILD_TARGET=out
PARENT_TARGET=parent
WORKER_TARGET=worker

all: $(PARENT_TARGET) $(WORKER_TARGET)

$(PARENT_TARGET): $(BUILD_TARGET)/parent.o $(BUILD_TARGET)/WorkerArgs.o
	$(COMPILE) $^ -o $(BUILD_TARGET)/$@

$(WORKER_TARGET): $(BUILD_TARGET)/worker.o $(BUILD_TARGET)/WorkerArgs.o
	$(COMPILE) $^ -o $(BUILD_TARGET)/$@

$(BUILD_TARGET)/%.o: %.cpp | $(BUILD_TARGET)
	$(COMPILE) -c $< -o $@

$(BUILD_TARGET):
	mkdir -p $@

clean:
	rm -rf $(BUILD_TARGET) $(PARENT_TARGET) $(WORKER_TARGET) *.bin *.log

.PHONY: all clean