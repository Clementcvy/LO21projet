# Compiler and flags used by the console build and automated tests.
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

# Name of the console executable produced by `make`.
TARGET = prog

# Source folders used by the Makefile.
SRC_DIR = src
TEST_DIR = tests

# Production sources for the console application.
APP_SRCS = $(wildcard $(SRC_DIR)/*.cpp) \
           $(wildcard $(SRC_DIR)/model/*.cpp) \
           $(wildcard $(SRC_DIR)/utils/*.cpp) \
           $(wildcard $(SRC_DIR)/core/*.cpp) \
           $(wildcard $(SRC_DIR)/rules/*.cpp) \
           $(wildcard $(SRC_DIR)/scoring/*.cpp) \
           $(wildcard $(SRC_DIR)/ui/*.cpp)

APP_OBJS = $(APP_SRCS:.cpp=.o)

# Test binaries reuse the production code, but exclude src/main.cpp because each
# test file provides its own main function.
TEST_SUPPORT_SRCS = $(filter-out $(SRC_DIR)/main.cpp,$(APP_SRCS))

# testSetupMenu is interactive, so it is built and run only through make test-setup.
TEST_SETUPMENU = $(TEST_DIR)/testSetupMenu
TEST_SRCS = $(filter-out $(TEST_DIR)/testSetupMenu.cpp,$(wildcard $(TEST_DIR)/*.cpp))
TESTS = $(patsubst %.cpp,%,$(TEST_SRCS))

# Declare command-style targets that do not correspond to generated files.
.PHONY: all clean run test test-setup

# Default target: build the console application.
all: $(TARGET)

$(TARGET): $(APP_OBJS)
	@echo "Linking $(TARGET)..."
	$(CXX) $(APP_OBJS) -o $(TARGET)

# Generic rule: compile any .cpp file into the matching .o file.
%.o: %.cpp
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build and run the console application.
run: $(TARGET)
	./$(TARGET)

# Build a non-interactive test binary with the shared production sources.
$(TEST_DIR)/%: $(TEST_DIR)/%.cpp $(TEST_SUPPORT_SRCS)
	@echo "Building $@..."
	$(CXX) $(CXXFLAGS) $< $(TEST_SUPPORT_SRCS) -o $@

# Build the interactive setup menu test separately.
$(TEST_SETUPMENU): $(TEST_DIR)/testSetupMenu.cpp $(SRC_DIR)/ui/SetupMenu.cpp $(SRC_DIR)/model/GameConfig.cpp
	@echo "Building $@..."
	$(CXX) $(CXXFLAGS) $^ -o $@

# Run the interactive setup menu test manually.
test-setup: $(TEST_SETUPMENU)
	./$(TEST_SETUPMENU)

# Build and run all automated, non-interactive tests.
test: $(TESTS)
	@echo "Running tests..."
	@for test in $(TESTS); do \
		echo "== $$test =="; \
		./$$test || exit $$?; \
	done

# Remove generated binaries and object files.
clean:
	@echo "Cleaning up..."
	rm -f $(APP_OBJS) $(TARGET) $(TESTS) $(TEST_SETUPMENU)
