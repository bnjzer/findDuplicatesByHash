#include <linux/limits.h>

typedef char Path[PATH_MAX + 1];

typedef struct stack_node {
  struct stack_node* next;
  Path path;
} StackNode;

StackNode* stack_add(StackNode* node, char* path);
StackNode* stack_pop(StackNode* node, char* destPath);
int stack_isEmpty(StackNode* node);
