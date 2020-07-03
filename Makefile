SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

TESTS_DIR := tests
TESTS_SRC_DIR := $(TESTS_DIR)/src
TESTS_OBJ_DIR := $(TESTS_DIR)/obj
TESTS_BIN_DIR := $(TESTS_DIR)/bin

EXE := $(BIN_DIR)/shellock
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

TESTS_SRC := $(wildcard $(TESTS_SRC_DIR)/*.c)
TESTS_OBJ := $(TESTS_SRC:$(TESTS_SRC_DIR)/%.c=$(TESTS_OBJ_DIR)/%.o)
TESTS_BIN := $(TESTS_OBJ:$(TESTS_OBJ_DIR)/%.o=$(TESTS_BIN_DIR)/%)

DFLAGS   := -g
CPPFLAGS :=
CFLAGS   := -Wall -Iinclude -MMD -MP
LDFLAGS  := -Llib
LDLIBS   :=
CHECK_LIBS := -pthread -lcheck_pic -pthread -lrt -lm -lsubunit

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(TESTS_OBJ_DIR)/%.o: $(TESTS_SRC_DIR)/%.c | $(TESTS_OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR) $(TESTS_OBJ_DIR) $(TESTS_BIN_DIR):
	mkdir -p $@

$(TESTS_BIN_DIR)/check_%: $(TESTS_OBJ_DIR)/check_%.o $(OBJ_DIR)/%.o | $(TESTS_BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(CHECK_LIBS) $(LDLIBS) -o $@

debug: CFLAGS += $(DFLAGS)
debug: $(EXE)

test: CFLAGS += $(DFLAGS)
test: $(TESTS_BIN)

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR) $(TESTS_BIN_DIR) $(TESTS_OBJ_DIR)

-include $(OBJ:.o=.d) $(TESTS_OBJ:.o=.d)