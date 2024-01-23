BIN_DIR := .
INC_DIR := -Iinclude
SRC_DIR := $(BIN_DIR)/source
OBJ_DIR := $(BIN_DIR)/obj

EXE := $(BIN_DIR)/raytracer
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CC := g++

CXXFLAGS := -I -M -MMD -MP $(INC_DIR) 
CFLAGS := -Wall -g

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $(CXXFLAGS) $(CFLAGS) -lm $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CXXFLAGS) $(CFLAGS) -c $< -o $@
	
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@
	
clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

-include $(OBJ:.o=.d)
