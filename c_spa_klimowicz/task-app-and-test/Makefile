TARGETAPP=app
TARGETTEST=ut_main
SRC_APP=./src
SRC_TEST=./ut

BUILD_TMP_DIR=./tmp
BUILD_DIR=./bin

DIRS=$(BUILD_TMP_DIR) $(BUILD_DIR)

SOURCES_APP = $(shell find $(SRC_APP) -name \*.c -type f)
SOURCES_TEST = $(shell find $(SRC_TEST) -name \*.c -type f)
OBJECTS_APP = $(addprefix $(BUILD_TMP_DIR)/,$(notdir $(SOURCES_APP:.c=.o)))
OBJECTS_TEST = $(addprefix $(BUILD_TMP_DIR)/,$(notdir $(SOURCES_TEST:.c=.o)))

BINARIESAPP=$(BUILD_DIR)/$(TARGETAPP)
BINARIESTEST=$(BUILD_DIR)/$(TARGETTEST)

CC=gcc
CFLAGS= -I$(SRC_APP) -g -c -Wall 

build: dirs $(BINARIESAPP) 

dirs:
	@mkdir -p $(DIRS)

$(BUILD_DIR)/$(TARGETAPP): $(OBJECTS_APP)
	$(CC) -o $@ $(OBJECTS_APP)

$(BUILD_DIR)/$(TARGETTEST): $(OBJECTS_TEST)
	$(CC) -o $@ $(OBJECTS_TEST) ./src/mult.c

$(BUILD_TMP_DIR)/%.o : $(SRC_APP)/%.c
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_TMP_DIR)/%.o : $(SRC_TEST)/%.c
	$(CC) $(CFLAGS) $< -o $@

test: clean dirs $(BINARIESTEST)
	$(BUILD_DIR)/ut_main

leaks: clean build test
	valgrind -q $(BUILD_DIR)/$(TARGETAPP) 2 3
	valgrind -q $(BUILD_DIR)/$(TARGETTEST)

all: build test leaks

clean:
	rm -rf $(DIRS)


