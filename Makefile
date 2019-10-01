TARGET=main
LIBS=
OPTIMIZE=-Og
LFLAGS=-Wall -Wextra -lm $(LIBS)
CPP=g++
LD=ld
BUILD_DIR=Build
SOURCE_DIR=Src
BIN_DIR=Bin
INCLUDE_DIR=Inc
TEST_DIR=test


CPP_INCLUDES = \
-I$(INCLUDE_DIR)

CPP_SOURCES = \
Src/main.cpp \
Src/strbase.cpp


OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(CPP_SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CPP_SOURCES)))



CFLAGS=$(CPP_DEFS) $(CPP_INCLUDES) $(OPTIMIZE) -Wall -Wextra -std=gnu++11 -g


all: $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(OBJECTS) Makefile
	$(CPP) $(OBJECTS) $(LDFLAGS) $(LIBS) -o $@


$(BUILD_DIR)/%.o: %.cpp Makefile | $(BUILD_DIR)
	$(CPP) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.cpp=.lst)) $< -o $@



directories: $(BUILD_DIR) $(BIN_DIR) $(SOURCE_DIR)


$(BUILD_DIR):
	mkdir $@

$(BIN_DIR):
	mkdir $@

$(SOURCE_DIR):
	mkdir $@

$(INCLUDE_DIR):
	mkdir $@

$(TEST_DIR):
	mkdir $@


clean:
	rm -rf $(BUILD_DIR)/*


run: main
	./run
