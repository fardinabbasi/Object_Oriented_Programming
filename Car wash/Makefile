CC = g++
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include
CFLAGS = -std=c++20 -Wall -I$(INCLUDE_DIR) -g

EXECUTABLE_FILE = CarWashManager.out

all: $(BUILD_DIR) $(EXECUTABLE_FILE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

OBJECTS = \
	$(BUILD_DIR)/Car.o \
	$(BUILD_DIR)/Stage.o \
	$(BUILD_DIR)/Event.o \
	$(BUILD_DIR)/Worker.o \
	$(BUILD_DIR)/CarWash.o \
	$(BUILD_DIR)/main.o \

$(BUILD_DIR)/Car.o: $(SRC_DIR)/Car.cpp $(INCLUDE_DIR)/Stage.hpp $(INCLUDE_DIR)/Worker.hpp $(INCLUDE_DIR)/Defs.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Car.cpp -o $(BUILD_DIR)/Car.o

$(BUILD_DIR)/CarWash.o: $(SRC_DIR)/CarWash.cpp $(INCLUDE_DIR)/Stage.hpp $(INCLUDE_DIR)/Worker.hpp $(INCLUDE_DIR)/Event.hpp $(INCLUDE_DIR)/Car.hpp $(INCLUDE_DIR)/Defs.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/CarWash.cpp -o $(BUILD_DIR)/CarWash.o

$(BUILD_DIR)/Event.o: $(SRC_DIR)/Event.cpp $(INCLUDE_DIR)/Defs.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Event.cpp -o $(BUILD_DIR)/Event.o

$(BUILD_DIR)/Stage.o: $(SRC_DIR)/Stage.cpp $(INCLUDE_DIR)/worker.hpp $(INCLUDE_DIR)/Car.hpp $(INCLUDE_DIR)/Defs.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Stage.cpp -o $(BUILD_DIR)/Stage.o

$(BUILD_DIR)/Worker.o: $(SRC_DIR)/Worker.cpp $(INCLUDE_DIR)/Defs.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Worker.cpp -o $(BUILD_DIR)/Worker.o

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(INCLUDE_DIR)/utils.hpp $(INCLUDE_DIR)/Stage.hpp $(INCLUDE_DIR)/Worker.hpp $(INCLUDE_DIR)/Defs.hpp $(INCLUDE_DIR)/CarWash.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Main.cpp -o $(BUILD_DIR)/Main.o

$(EXECUTABLE_FILE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE_FILE)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out