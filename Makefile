# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -pthread -lsqlite3

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = include

# Source and object files
SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/request_handler.cpp $(SRC_DIR)/database.cpp $(SRC_DIR)/logger.cpp $(SRC_DIR)/threadpool.cpp
OBJS = $(SRCS:.cpp=.o)

# Output executable
TARGET = server

# Default build target
all: $(TARGET)

# Compile the server
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(TARGET) $(OBJS)

# Run the server
run: all
	./$(TARGET)
