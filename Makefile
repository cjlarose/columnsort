CC=g++
CFLAGS=-O2 -Wall

BUILD_DIR=build
SOURCES=column_sorter.cpp matrix.cpp
OBJECTS=$(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

.PHONY: all
all: directories seq-sort par-sort

.PHONY: directories
directories:
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $^

seq-sort: $(OBJECTS) $(BUILD_DIR)/seq_column_sorter.o main.cpp
	$(CC) $(CFLAGS) -DSEQUENTIAL -o $@ $^

par-sort: $(OBJECTS) $(BUILD_DIR)/par_column_sorter.o main.cpp
	$(CC) $(CFLAGS) -DPARALLEL -o $@ $^

generate-testcase: generate_testcase.cpp
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
	rm -f generate-testcase seq-sort par-sort
