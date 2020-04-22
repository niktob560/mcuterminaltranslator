TARGET=translator
LIBS=
OPTIMIZE=-Og
LFLAGS=-Wall -Wextra -lm $(LIBS)
CPP=g++
LD=ld
BUILD_DIR=Build
SOURCE_DIR=Src
BIN_DIR=Bin
INCLUDE_DIR=Inc
TEST_DIR=Test


CPP_INCLUDES = \
-I$(INCLUDE_DIR)

CPP_SOURCES = \
Src/main.cpp \
Src/translator.cpp

CPP_DEFS =#-DUSE_MULTIDEVICE -DUSE_DYNAMIC_ID -DDEVICE_ID=1


OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(CPP_SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CPP_SOURCES)))

TOBJECTS = $(filter-out $(BUILD_DIR)/main.o,$(OBJECTS))



CFLAGS=$(CPP_DEFS) $(CPP_INCLUDES) $(OPTIMIZE) -std=gnu++11 -Wno-pragmas -Wall -Wextra -Werror -Og -g -Wparentheses -Wsequence-point -Wreturn-type -Wswitch -Wuninitialized -Wno-write-strings -Wcast-align -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wduplicated-branches -Wduplicated-cond -Wextra-semi -Wfloat-equal -Wlogical-op -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo -Werror -IInclude -Wall -Wextra -Wpedantic -pedantic-errors -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -fno-devirtualize -fno-use-cxa-atexit


all: $(BIN_DIR)/$(TARGET) directories

$(BIN_DIR)/$(TARGET): $(BIN_DIR)/lib$(TARGET).so $(BUILD_DIR)/main.o  Makefile
	@$(CPP) $(BUILD_DIR)/main.o $(BIN_DIR)/lib$(TARGET).so $(LIBS) -o $@
	@echo -e '\033[1;32m'"CC " $@ '\033[0m'


$(BIN_DIR)/lib$(TARGET).so: $(TOBJECTS)
	@$(CPP) -shared $^ -o $@
	@echo -e '\033[1;32m'"CC " $@ '\033[0m'


$(BUILD_DIR)/%.o: %.cpp Makefile | $(BUILD_DIR)
	@$(CPP) -c $(CFLAGS) -fPIC -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.cpp=.lst)) $< -o $@
	@echo -e '\033[1;32m'"CC " $@ '\033[0m'


test: directories all
	@cxxtest/bin/cxxtestgen --error-printer -o $(TEST_DIR)/test.cpp $(TEST_DIR)/test.h
	@g++ $(CPP_DEFS) -O6 -o $(TEST_DIR)/test $(TOBJECTS) $(TEST_DIR)/test.cpp -I cxxtest -I $(INCLUDE_DIR)
	@$(TEST_DIR)/test


directories: $(BUILD_DIR) $(BIN_DIR) $(SOURCE_DIR) $(INCLUDE_DIR) $(TEST_DIR)


$(BUILD_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@

$(SOURCE_DIR):
	mkdir -p $@

$(INCLUDE_DIR):
	mkdir -p $@

$(TEST_DIR):
	mkdir -p $@


clean:
	@rm -rf $(BUILD_DIR)/*
	@rm -rf $(TEST_DIR)/*.cpp
	@rm -rf $(TEST_DIR)/main
	@rm -rf $(BIN_DIR)/*
	@echo -e '\033[1;31m'"Cleaned"'\033[0m'


run: main
	./run
