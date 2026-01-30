#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include "shellfunc.h"

void exitShell (void) {  
  printf("exiting...\n");
  exit(0);
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

void loadEnvironment () {
  printf("Loading environment...\n");
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
