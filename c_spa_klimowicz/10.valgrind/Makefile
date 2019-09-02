TARGET=memcheck_err

SRC_DIR=./src

BUILD_TMP_DIR=./tmp
BUILD_DIR=./bin

DIRS=$(BUILD_TMP_DIR) $(BUILD_DIR) 

SOURCES_APP = $(shell find $(SRC_DIR) -name \*.c -type f)
OBJECTS_APP = $(addprefix $(BUILD_TMP_DIR)/,$(notdir $(SOURCES_APP:.c=.o)))

BINARIES=$(BUILD_DIR)/$(TARGET)

CC=gcc
CFLAGS= -I$(SRC_DIR) -g -c -w

build: dirs $(BINARIES)

dirs:
	@mkdir -p $(DIRS)

$(BUILD_DIR)/$(TARGET): $(OBJECTS_APP)
	$(CC) -o $@ $(OBJECTS_APP)

$(BUILD_TMP_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

test: build
	valgrind --tool=memcheck $(BUILD_DIR)/$(TARGET)

clean:
	rm -rf $(DIRS)

loop: clean all
