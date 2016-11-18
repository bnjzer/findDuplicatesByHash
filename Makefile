SRC_DIR=src
LIB_DIR=lib
BIN_DIR=bin
INCLUDE_DIR=include
CC=gcc
AR=ar
CFLAGS=-Wall -pedantic -I$(INCLUDE_DIR) -g
LDFLAGS=-L$(LIB_DIR)
EXEC=findDuplicatesByHash

all : $(BIN_DIR)/$(EXEC)

### binary ####

$(BIN_DIR)/$(EXEC) : $(LIB_DIR)/libstack.a $(LIB_DIR)/libtrie.a $(SRC_DIR)/main.o $(SRC_DIR)/parsing.o $(SRC_DIR)/findDuplicates.o
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@  $(SRC_DIR)/main.o $(SRC_DIR)/parsing.o $(SRC_DIR)/findDuplicates.o -lstack -ltrie -lssl -lcrypto

$(LIB_DIR)/libstack.a : $(SRC_DIR)/stack.o
	mkdir -p $(LIB_DIR)
	$(AR) -r $@ $<

$(LIB_DIR)/libtrie.a : $(SRC_DIR)/trie.o
	mkdir -p $(LIB_DIR)
	$(AR) -r $@ $<

$(SRC_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

### clean ###

clean:
	rm -rf $(BIN_DIR)
	rm -rf $(LIB_DIR)
	rm -f $(SRC_DIR)/*.o
