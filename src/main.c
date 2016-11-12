#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/limits.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include "stack.h"

int checkIsDir(char* path){
  struct stat dirStats;
  if (stat(path, &dirStats) != 0 || ! S_ISDIR(dirStats.st_mode)) {
    printf("Error: %s is not a directory\n", path);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int parseArgs(int argc, char **argv, char *dir1_path, char *dir2_path) {
  if (argc != 3) {
    printf("Bad number of arguments\n");
    return EXIT_FAILURE;
  }

  strcpy(dir1_path, *(argv+1));
  strcpy(dir2_path, *(argv+2));

  if (checkIsDir(*(argv+1)) == EXIT_FAILURE)
    return EXIT_FAILURE;

  return checkIsDir(*(argv+2));
}

void usage(char* progName){
  printf("Usage: %s <dir1> <dir2>\n\
      <dir1> and <dir2> must both be directories\n", progName);
}

void listFiles(stack_node* top){
  DIR *dir;
  struct dirent *ent;
  Path currentPath;

  while ( ! stack_isEmpty(top)) {
    top = stack_pop (top, currentPath);

    if ((dir = opendir (currentPath)) != NULL) {
      while ((ent = readdir (dir)) != NULL) {
        if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
          Path fullPath;
          strcpy (fullPath, currentPath);
          strcat (fullPath, "/");
          strcat (fullPath, ent->d_name);

          if (ent->d_type == DT_DIR)
            top = stack_add(top, fullPath);
          else 
            printf ("%s\n", fullPath);
        }
      }
      closedir (dir);
    } else {
      printf("Couldn't open dir %s\n", currentPath);
    }
  }
}

int main(int argc, char **argv){
  char dir1_path[PATH_MAX];
  char dir2_path[PATH_MAX];

  if (parseArgs(argc, argv, dir1_path, dir2_path) == EXIT_FAILURE){
    usage(*argv);
    return EXIT_FAILURE;
  }

  stack_node* top = NULL;
  top = stack_add (top, dir1_path);
  listFiles(top);

  return EXIT_SUCCESS;
}
