# Compiler settings
CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -g
LDFLAGS =

# Source and object directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Source files (automatically find .c and .cpp files in SRC_DIR)
SOURCES = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*.cpp)
# Object files (replace .c and .cpp with .o, and place in OBJ_DIR)
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES)))

# Executable name
TARGET = main

# Default rule: build the executable
all: $(BIN_DIR)/$(TARGET)

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CFLAGS) -c $< -o $@

# Link object files to create the executable
$(BIN_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(LDFLAGS) $^ -o $@

# Clean build artifacts
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Run the executable
run: $(BIN_DIR)/$(TARGET)
	$(BIN_DIR)/$(TARGET)

.PHONY: all clean run