CC=g++
CFLAGS=-O2 -Wall --std=c++0x
#CFLAGS=-Wall --std=c++0x -DDEBUG
#CFLAGS=-O2 -Wall --std=c++0x -pg

BUILD_DIR=build
SOURCES=column_sorter.cpp matrix.cpp
OBJECTS=$(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SOURCES))
SEQ_OBJECTS=$(OBJECTS) $(BUILD_DIR)/seq_column_sorter.o
PAR_OBJECTS=$(OBJECTS) $(BUILD_DIR)/par_column_sorter.o $(BUILD_DIR)/barrier.o

.PHONY: submission
submission: directories seq-sort par-sort

.PHONY: all
all: directories seq-sort par-sort generate-testcase

.PHONY: directories
directories:
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.cpp %.h Makefile
	$(CC) $(CFLAGS) -c -o $@ $<

seq-sort: $(SEQ_OBJECTS) main.cpp
	$(CC) $(CFLAGS) -DSEQUENTIAL -o $@ $^

par-sort: $(PAR_OBJECTS) main.cpp
	$(CC) $(CFLAGS) -pthread -DPARALLEL -o $@ $^

generate-testcase: generate_testcase.cpp
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
	rm -f generate-testcase seq-sort par-sort
