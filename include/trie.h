typedef struct trie_node {
  struct trie_node *children[26 + 10];
  char* path;
} TrieNode;

void trie_insert(TrieNode* node, char* remainingHash, char* path);
char* trie_get(TrieNode* node, char* remainingHash);
