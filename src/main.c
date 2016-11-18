#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "trie.h"
#include "parsing.h"
#include "findDuplicates.h"

int main(int argc, char **argv){
  char dir_path[PATH_MAX];
  char dir2_path[PATH_MAX];

  if (parseArgs(argc, argv, dir_path, dir2_path) == EXIT_FAILURE){
    usage(*argv);
    return EXIT_FAILURE;
  }

  // Find duplicates in dir by building the trie with the hashes of files
  StackNode* stackTop = NULL;
  stackTop = stack_add(stackTop, dir_path);
  TrieNode trieRoot;
  findDuplicates(stackTop, &trieRoot);

  if (strlen(dir2_path) > 0) {
    // Read the trie to check if files in dir2 have their hash in dir
    stackTop = NULL;
    stackTop = stack_add(stackTop, dir2_path);
    findDuplicatesIn2Dirs(stackTop, &trieRoot);
  }

  return EXIT_SUCCESS;
}
