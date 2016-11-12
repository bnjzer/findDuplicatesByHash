SRC_DIR=src
LIB_DIR=lib
BIN_DIR=bin
INCLUDE_DIR=include
TEST_DIR=test
CC=gcc
AR=ar
CFLAGS=-Wall -pedantic -I$(INCLUDE_DIR)
CFLAGS_TEST=$(CFLAGS) -I$(TEST_DIR)/$(INCLUDE_DIR)
LDFLAGS=-L$(LIB_DIR)
LDFLAGS_TEST=$(LDFLAGS) -L$(TEST_DIR)/$(LIB_DIR)
EXEC=findDuplicatesByHash
EXEC_TEST=$(EXEC)Test

all : $(BIN_DIR)/$(EXEC)

### binary ####

$(BIN_DIR)/$(EXEC) : $(LIB_DIR)/libstack.a $(SRC_DIR)/main.o $(BIN_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(SRC_DIR)/main.o -lstack

$(LIB_DIR)/libstack.a : $(SRC_DIR)/stack.o $(LIB_DIR)
	$(AR) -r $@ $(SRC_DIR)/stack.o

$(SRC_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(BIN_DIR):
	mkdir $@

$(LIB_DIR):
	mkdir $@

### test ###

test: $(TEST_DIR)/$(BIN_DIR)/$(EXEC_TEST)
	./$(TEST_DIR)/$(BIN_DIR)/$(EXEC_TEST)

$(TEST_DIR)/$(BIN_DIR)/$(EXEC_TEST) : $(TEST_DIR)/$(LIB_DIR)/lib$(EXEC_TEST).a $(LIB_DIR)/lib$(EXEC).a $(TEST_DIR)/$(SRC_DIR)/main.o $(TEST_DIR)/$(BIN_DIR)
	$(CC) $(CFLAGS_TEST) $(LDFLAGS_TEST) -o $@ $(TEST_DIR)/$(SRC_DIR)/main.o -l$(EXEC_TEST) -l$(EXEC) -lcunit

$(TEST_DIR)/$(LIB_DIR)/lib$(EXEC_TEST).a : $(TEST_DIR)/$(SRC_DIR)/testForrestParsing.o $(TEST_DIR)/$(SRC_DIR)/testForrestPrinting.o $(TEST_DIR)/$(LIB_DIR)
	$(AR) -r $@ $(TEST_DIR)/$(SRC_DIR)/testForrestParsing.o $(TEST_DIR)/$(SRC_DIR)/testForrestPrinting.o

$(TEST_DIR)/$(SRC_DIR)/%.o : $(TEST_DIR)/$(SRC_DIR)/%.c
	$(CC) $(CFLAGS_TEST) -o $@ -c $<

$(TEST_DIR)/$(BIN_DIR):
	mkdir $@

$(TEST_DIR)/$(LIB_DIR):
	mkdir $@

### clean ###

clean:
	rm -rf $(BIN_DIR)
	rm -rf $(LIB_DIR)
	rm -f $(SRC_DIR)/*.o
	rm -rf $(TEST_DIR)/$(BIN_DIR)
	rm -rf $(TEST_DIR)/$(LIB_DIR)
	rm -f $(TEST_DIR)/$(SRC_DIR)/*.o
