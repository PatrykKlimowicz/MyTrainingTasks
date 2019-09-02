SRC_DIR=./src

BUILD_TMP_DIR=./tmp
BUILD_DIR=./bin

DIRS=$(BUILD_TMP_DIR) $(BUILD_DIR) 

SOURCES_APP = $(shell find $(SRC_DIR) -name \*.c -type f)
OBJECTS_APP = $(addprefix $(BUILD_TMP_DIR)/,$(notdir $(SOURCES_APP:.c=.o)))

TARGET=$(BUILD_DIR)/args

CC=gcc
CFLAGS=-fpic -I$(SRC_DIR) -I./src/ -c -Wall

build : dirs $(TARGET)

all: build test

dirs:
	@mkdir -p $(DIRS)

$(TARGET): $(OBJECTS_APP) 
	$(CC) -o $(TARGET) $(OBJECTS_APP) 

$(BUILD_TMP_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

test: build
	valgrind --tool=memcheck --leak-check=full --track-origins=yes $(TARGET) $(ARGS)

clean:
	rm -rf $(DIRS)

loop: clean all
