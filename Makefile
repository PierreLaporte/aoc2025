CXX := clang++
CXXFLAGS := -Wall -Wextra -std=c++20 -Iinclude
LDFLAGS :=
BUILD := ./build
OBJ_DIR := $(BUILD)/objects/
APP_DIR := $(BUILD)/
TARGET := aoc_exec

SRC := $(wildcard src/*.cpp)
OBJECTS := $(SRC:src/%.cpp=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)$(TARGET)

$(OBJ_DIR)/%.o: src/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(APP_DIR)$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $(APP_DIR)$(TARGET) $(OBJECTS) $(LDFLAGS)

build:
	@mkdir -p $(OBJ_DIR)

clean:
	-@rm -rf $(BUILD)