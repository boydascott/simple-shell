#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shellfunc.h"


int main (void) {
  char buffer[513];
  char* output = "";
  char* builtIn = "cd getpath setpath history ! !! !- alias unalias";
  char** parsed;
  
  loadEnvironment();
  
  do {
    // Display prompt
    printf("> ");
    
    // Read + Parse input
    output = fgets(buffer, sizeof(buffer), stdin);

    parsed = parseInput(buffer);
    
    if (strstr(builtIn, parsed[0]) || !output || strcmp(parsed[0], "exit") == 0) {
      executeBuiltIn(parsed);
    } else {
      execute(parsed);
    }    
  } while (output && strcmp(parsed[0], "exit") != 0); // exits while loop if output is NULL or buffer == exit

  // memory management
  free(parsed);
  parsed = NULL;
  
  
  // cleanly exit shell
  exitShell();

  return 0;
}
