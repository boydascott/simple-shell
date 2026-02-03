#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include "shellfunc.h"

char* loadEnvironment () {
  printf("Loading environment...\n");
  char* path = getenv("PATH");
  char* home = getenv("HOME");
  chdir(home);
  return path;
}

char** parseInput(char buffer[]) {
  // removes new line from end of buffer
  buffer[strcspn(buffer, "\n")] = 0;
  
  char delims[] = " \t|><&;";
  int i = 0;

  char** token = malloc (sizeof(char*)*50);
  token[i] = strtok(buffer,delims);

  while(token[i] != NULL){
    i++;
    token[i] = strtok(NULL, delims);
  }

  // DO NOT DELETE - handles seg fault and stops everything from breaking C:
  if (token[0] == NULL) {
    token[0] = "";
  }
  
  return token;
}

void execute (char* args[]) {
  pid_t p = fork(); // gets the id of child process, parent process > 0, child will always be 0, error is -1

  if (p > 0) { // checks for parent process
    wait(NULL);
  } else if (p == 0) { // checks for child process
    execvp(args[0], args);
    perror(args[0]);
    exit(1);
  } else { // error
    printf("Something went wrong\n");
  }
}

void executeBuiltIn (char* args[]) {
  char* cmds[] = { "cd", "getpath", "setpath" };
  
  void (*builtIns[])(char**) = { cd, getPath, setPath };
  
  for (int i = 0; i < 3; i++) {
    if (strcmp(args[0], cmds[i]) == 0) {
      builtIns[i](args);
    }
  }
}

void getPath (char* args[]) {
  if (args[1]) {
    printf("Error: Too many parameters, none are required\n");
  } else {
    printf("%s\n", getenv("PATH"));
  }
}

void setPath (char* args[]) {
  if (args[1] == NULL) {
    printf("Error: No parameter provided, please enter a path\n");
  } else if (args[2]) {
    printf("Error: Too many parameters, please only enter one\n");
  } else {
    setenv("PATH", args[1], 1);
  }
}

void cd (char* args[]) {
  printf("cd placeholder\n");
}

void exitShell (char* path) {
  setenv("PATH", path, 1);
  printf("%s\n", getenv("PATH"));
  printf("exiting...\n");
  exit(0);
}
