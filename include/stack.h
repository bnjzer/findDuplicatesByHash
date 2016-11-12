typedef char Path[PATH_MAX];

typedef struct stack_node {
  Path path;
  struct stack_node* next;
} stack_node;

stack_node* stack_add (stack_node* node, char* path);
stack_node* stack_pop (stack_node* node, char* destPath);
int stack_isEmpty (stack_node* node);
