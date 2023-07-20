CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

LIB_DIR = lib
OBJ_DIR = obj
APP_DIR = app

LIB_SRCS = fileFinder.cpp
LIB_OBJS = $(LIB_SRCS:%.cpp=$(OBJ_DIR)/%.o)

APP_SRCS = main.cpp
APP_OBJS = $(APP_SRCS:%.cpp=$(OBJ_DIR)/%.o)

EXECUTABLE = fileFinderApp

all: $(LIB_DIR)/libfilefinder.a $(APP_DIR)/$(EXECUTABLE)

$(LIB_DIR)/libfilefinder.a: $(LIB_OBJS)
	ar rcs $@ $(LIB_OBJS)

$(APP_DIR)/$(EXECUTABLE): $(APP_OBJS)
	$(CXX) $(CXXFLAGS) -L$(LIB_DIR) $^ -lfilefinder -o $@

$(OBJ_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(LIB_DIR) $(OBJ_DIR) $(APP_DIR):
	mkdir -p $@

clean:
	rm -rf $(LIB_DIR) $(OBJ_DIR) $(APP_DIR)

.PHONY: all clean