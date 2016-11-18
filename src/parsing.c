#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int checkIsDir(char* path){
  struct stat dirStats;
  if (stat(path, &dirStats) != 0 || ! S_ISDIR(dirStats.st_mode)) {
    fprintf(stderr, "Error: %s is not a directory\n\n", path);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int parseArgs(int argc, char **argv, char *dir_path, char *dir2_path) {
  if (argc < 2 || 3 < argc) {
    fprintf(stderr, "Error: bad number of arguments\n\n");
    return EXIT_FAILURE;
  }

  strcpy(dir_path, *(argv+1));
  if (checkIsDir(*(argv+1)) == EXIT_FAILURE)
    return EXIT_FAILURE;

  if (argc == 3) {
    strcpy(dir2_path, *(argv+2));
    if (checkIsDir(*(argv+2)) == EXIT_FAILURE)
      return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

void usage(char* progName){
  printf("Usage: %s <dir> [dir2]\n\n\
  dir: browsed recursively to find duplicates\n\
  dir2: if set, the program looks for duplicates between dir and dir2 recursively\n\n\
  dir and dir2 must be directories\n", progName);
}

