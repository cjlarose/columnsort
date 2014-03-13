CC=g++
CFLAGS=-O2 -pg

BUILD_DIR=build
SOURCES=column_sorter.cpp matrix.cpp main.cpp
OBJECTS=$(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

.PHONY: all
all: directories seq-sort

.PHONY: directories
directories:
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $^

seq-sort: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

generate-testcase: generate_testcase.cpp
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
	rm -f seq-sort
