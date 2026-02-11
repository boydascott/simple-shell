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

void executeBuiltIn (char* args[], char* history[]) {
  char* cmds[] = { "cd", "getpath", "setpath" };
  
  void (*builtIns[])(char**) = { cd, getPath, setPath };
  
  for (int i = 0; i < 3; i++) {
    if (strcmp(args[0], cmds[i]) == 0) {
      builtIns[i](args);
    } else if (strcmp(args[0], "history") == 0) {
      listHistory(args, history);
      break;
    }
  }
}

// Prints whats stored in PATH
void getPath (char* args[]) {
  if (args[1]) {
    printf("Error: Too many parameters, none are required\n");
  } else {
    printf("%s\n", getenv("PATH"));
  }
}

// overwrites what stored in PATH with users input
void setPath (char* args[]) {
  if (args[1] == NULL) {
    printf("Error: No parameter provided, please enter a path\n");
  } else if (args[2]) {
    printf("Error: Too many parameters, please only enter one\n");
  } else {
    setenv("PATH", args[1], 1); 
  }
}

// cd command, changes working directory
void cd (char* args[]) { 
  // create home variable using getenv, this is the user's home path.
  char* home = getenv("HOME");
  
  // if the input directory is empty, set working directory to home variable. 
  if (args[1] == NULL) chdir(home);
  
  // checks case of user entering two paths, prints error.
  else if (args[2]) printf ("Too many arguments \n");
  
  // otherwise, change directory to input directory, if it is unsuccesful, print using syscall value w/ perror()
  else if (chdir(args[1]) != 0) perror(args[1]);
}

int calculateHistoryIndex(char* arg, int length) {
  int n = 0;
  if (strcmp(arg, "!!") == 0) {
    n = 1;
  } else if (length == 2 || (length == 3 && arg[1] == '-')) {
    n = arg[length-1] - '0';
  } else if (length == 3 || length == 4){
    n = (arg[length-2] - '0') * 10 + (arg[length-1] - '0');
  } else {
    return 0;
  }

  if (arg[1] == '-' || (arg[2] == '0' && arg[1] == '-')) {
    n = 20 - n;
  }

  printf("n: %d\n", n);
  
  return n;
}

char* invokeHistory (char* arg, char* hist[]) {
  int n = 0;
  
  n = calculateHistoryIndex(arg, strlen(arg));
  
  if (n < -19 || n == 0 ||  n > 20) {
    printf("Error: History must be from -19 to 20\n");
  } else if (strcmp(hist[n-1], "") == 0) {
    printf("Error: No history for that index\n");
  } else {
    return hist[n-1];
  }
  
  return "";
}

void listHistory (char* args[], char* hist[]) {
  int i = 0;
  while (strcmp(hist[i], "") != 0) {
    printf("%d: %s\n", i+1, hist[i]);
    i++;
  }
}

void exitShell (char* path) {
  setenv("PATH", path, 1);
  printf("%s\n", getenv("PATH"));
  printf("exiting...\n");
  exit(0);
}
