#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shellfunc.h"


int main (void) {
  char buffer[512];
  char* output = "";
  char* builtIn = "cd getpath setpath alias unalias history";
  char** parsed;
  char** hist = malloc(sizeof(char*) * 20);
  int cmdSaved = 0;

  for (int i = 0; i < 20; i++) {
    hist[i] = malloc(sizeof(char)*512);
  }
  
  char* path = loadEnvironment();
  
  do {
    // Display prompt
    printf("> ");
    
    // Read + Parse input
    output = fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;

    parsed = parseInput(buffer);
    
    if (strcspn("!", parsed[0]) == 0) {
      strcpy(buffer, invokeHistory(parsed[0], hist));
      parsed = parseInput(buffer);
    } else {
      int i = 0;
      char cmd[512] = {};
      
      while (parsed[i]) {
	strcat(cmd, parsed[i]);
	strcat(cmd, " ");
	i++;
      }
      strcpy(hist[cmdSaved], cmd);
      cmdSaved = (cmdSaved + 1) % 20;
    }
    
    if (strstr(builtIn, parsed[0]) || !output || strcmp(parsed[0], "exit") == 0) {
      executeBuiltIn(parsed, hist);
    } else {
      execute(parsed);
    }    
  } while (output && strcmp(parsed[0], "exit") != 0); // exits while loop if output is NULL or buffer == exit

  // memory management
  free(parsed);
  parsed = NULL;
  
  
  // cleanly exit shell
  exitShell(path);

  return 0;
}
