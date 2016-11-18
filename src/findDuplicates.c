#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <openssl/md5.h>

#include "stack.h"
#include "trie.h"

int getMD5(char* path, char* md5) {
  FILE *file;
  MD5_CTX mdContext;
  int bytesRead, bufferSize = 1024, i;
  unsigned char data[bufferSize];
  unsigned char finalMd5[MD5_DIGEST_LENGTH];

  if ((file = fopen(path, "rb")) == NULL) {
    fprintf(stderr, "%s can't be opened\n", path);
    perror(NULL);
    return EXIT_FAILURE;
  }

  MD5_Init(&mdContext);
  while ((bytesRead = fread(data, 1, bufferSize, file)) != 0)
    MD5_Update(&mdContext, data, bytesRead);
  MD5_Final(finalMd5, &mdContext);
  fclose(file);

  for(i = 0; i < MD5_DIGEST_LENGTH; i++) {
    sprintf(md5+(2*i), "%02x", finalMd5[i]);
  }
  i = 2*i + 1;

  return EXIT_SUCCESS;
}

void insertMd5(TrieNode* trieRoot, char* md5, char* correspondingPath) {
  trie_insert(trieRoot, md5, correspondingPath);
}

void findMd5(TrieNode* trieRoot, char* md5, char* correspondingPath) {
  char *duplicatePath = trie_get(trieRoot, md5);
  if (duplicatePath != NULL)
    printf("%s\n  %s\n\n", duplicatePath, correspondingPath);
}

void browseDirWithFunc(StackNode* stackTop, TrieNode* trieRoot, void (*funcOnMd5)(TrieNode*, char*, char*)) {
  DIR *dir;
  struct dirent *ent;
  Path currentPath;
  char md5[2 * MD5_DIGEST_LENGTH + 1];

  while (!stack_isEmpty(stackTop)) {
    stackTop = stack_pop(stackTop, currentPath);

    if ((dir = opendir(currentPath)) != NULL) {
      while ((ent = readdir(dir)) != NULL) {
        if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
          Path fullPath;
          strcpy(fullPath, currentPath);
          if (currentPath[strlen(currentPath) - 1] != '/')
            strcat(fullPath, "/");
          strcat(fullPath, ent->d_name);

          if (ent->d_type == DT_DIR)
            stackTop = stack_add(stackTop, fullPath);
          else {
            getMD5(fullPath, md5);
            if (md5 == NULL)
              fprintf(stderr, "Can't compute md5sum for file %s\n", fullPath);
            else
              (*funcOnMd5)(trieRoot, md5, fullPath);
          }
        }
      }
      closedir(dir);
    } else {
      fprintf(stderr, "Couldn't open dir %s\n", currentPath);
    }
  }
}

void findDuplicates(StackNode* stackTop, TrieNode* trieRoot) {
  browseDirWithFunc(stackTop, trieRoot, insertMd5);
}

void findDuplicatesIn2Dirs(StackNode* stackTop, TrieNode* trieRoot) {
  browseDirWithFunc(stackTop, trieRoot, findMd5);
}

