#include <linux/limits.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

stack_node* stack_add (stack_node* node, char* path) {
  stack_node* newNode = (stack_node*) malloc (sizeof(stack_node));
  strcpy (newNode->path, path);
  newNode->next = node;
  return newNode;
}

stack_node* stack_pop (stack_node* node, char* destPath) {
  strcpy (destPath, node->path);
  stack_node* next = node->next;
  free(node);
  return next;
}

int stack_isEmpty (stack_node* node) {
  return node == NULL;
}
