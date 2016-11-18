#include <stdlib.h>
#include <string.h>

#include "stack.h"

StackNode* stack_add(StackNode* node, char* path) {
  StackNode* newNode = (StackNode*) malloc(sizeof(StackNode));
  strcpy(newNode->path, path);
  newNode->next = node;
  return newNode;
}

StackNode* stack_pop(StackNode* node, char* destPath) {
  if(node == NULL) return NULL;

  strcpy(destPath, node->path);
  StackNode* next = node->next;
  free(node);
  return next;
}

int stack_isEmpty(StackNode* node) {
  return node == NULL;
}
