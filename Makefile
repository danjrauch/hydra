TARGET_EXEC ?= main
TEST_EXEC ?= test

BUILD_DIR ?= ./bin
SRC_DIRS ?= ./src
TEST_DIR ?= ./tests

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

TESTS := $(shell find $(TEST_DIR) -name *.cpp -or -name *.c)
TOBJS := $(TESTS:%=$(BUILD_DIR)/%.o)
TDEPS := $(TOBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# CPPFLAGS ?= $(INC_FLAGS) -MMD -MP
CFLAGS ?= -c -Iinclude -Wall

# Using Criterion as a test framework
# https://github.com/Snaipe/Criterion
# $(BUILD_DIR)/$(TEST_EXEC) : EXTRA_FLAGS = -lcriterion

all: $(BUILD_DIR)/$(TARGET_EXEC) # $(BUILD_DIR)/$(TEST_EXEC)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/$(TEST_EXEC): $(TOBJS)
	$(CC) $(TOBJS) -o $@ $(LDFLAGS) $(EXTRA_FLAGS)

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# assembly
$(BUILD_DIR)/%.s.o: %.s
	$(MKDIR_P) $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

.SILENT: clean run test # grind
.PHONY: clean
clean:
	$(RM) -r $(BUILD_DIR)

test:
	./$(BUILD_DIR)/$(TEST_EXEC)

run:
	./$(BUILD_DIR)/$(TARGET_EXEC) p.forth

# grind:
# 	mpirun -n 4 valgrind --leak-check=yes $(BUILD_DIR)/$(TARGET_EXEC)

-include $(DEPS)

MKDIR_P ?= mkdir -p