TARGET = main

CC = gcc
CFLAGS = -g -Wall 
CLIBS = -lm -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lGL -lGLEW

BIN_DIR = ./bin
OBJ_DIR = ./obj
SRC_DIR = ./src

MODULES = engine engine/input engine/utils
SUB_DIRS = $(addprefix $(SRC_DIR)/, $(MODULES))

INCS = $(wildcard $(SRC_DIR)/*.h $(foreach fd, $(SUB_DIRS), $(fd)/*.h))
SRCS = $(wildcard $(SRC_DIR)/*.c $(foreach fd, $(SUB_DIRS), $(fd)/*.c))
NO_DIR_SRCS = $(notdir $(SRCS))
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

INC_DIRS = $(addprefix -I, $(SUB_DIRS))

.PHONY: clean 

OUTPUT = $(BIN_DIR)/3d

all: clean 3d

3d: $(OBJS)
	$(CC) $(CFLAGS) $(INC_DIRS) $(OBJS) -o $(OUTPUT) $(CLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCS)
	mkdir -p $(@D)
	@echo "Compiling $<"
	$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@ $(CLIBS)

clean:
	rm -rf $(OBJS) $(OUTPUT)

