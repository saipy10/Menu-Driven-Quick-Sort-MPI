# Makefile for MPI Parallel QuickSort

CXX = mpic++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
TARGET = quicksort_mpi
SOURCES = main.cpp
HEADERS = quicksort.h mpi_utils.h file_utils.h
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(TARGET)

# Build executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Compile source files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $<

# Run with 4 processes
run: $(TARGET)
	mpirun -np 4 ./$(TARGET)

# Run with custom number of processes
run-%: $(TARGET)
	mpirun -np $* ./$(TARGET)

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET) output.txt

# Clean everything including output
distclean: clean
	rm -f output.txt

# Display help
help:
	@echo "Available targets:"
	@echo "  make              - Build the program"
	@echo "  make run          - Build and run with 4 processes"
	@echo "  make run-2        - Build and run with 2 processes"
	@echo "  make run-8        - Build and run with 8 processes"
	@echo "  make clean        - Remove build artifacts"
	@echo "  make distclean    - Remove all generated files"
	@echo "  make help         - Show this message"

.PHONY: all run clean distclean help
