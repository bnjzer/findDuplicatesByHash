#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "trie.h"

int getIndex(char c) {
  if ('a' <= c && c <= 'z')
    return c - 'a';
  else if ('0' <= c && c <= '9')
    return c - '0';
  else
    return -1;
}

void trie_insert(TrieNode* node, char* remainingHash, char* path) {
  if (*remainingHash == '\0') {
    if (node->path != NULL)
      printf("%s\n  %s\n\n", node->path, path);
    else {
      node->path = (char*) malloc((strlen(path)+1) * sizeof(char));
      strcpy(node->path, path);
    }
  } else {
    int idx = getIndex(*remainingHash);
    if (node->children[idx] == NULL) {
      node->children[idx] = (TrieNode*) malloc(sizeof(TrieNode));
      memset(node->children[idx], 0, sizeof(TrieNode));
    }
    trie_insert(node->children[idx], remainingHash + 1, path);
  }
}

char* trie_get(TrieNode* node, char* remainingHash){
  if (*remainingHash == '\0')
    return node->path;

  int idx = getIndex(*remainingHash);
  if (node->children[idx] == NULL)
    return NULL;
  else
    return trie_get(node->children[idx], remainingHash + 1);
}
