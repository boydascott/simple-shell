#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

void exitShell (void);
void parseInput(char buffer[]);

int main (void) {
  char buffer[512] = "0";
  char* output = "0";

  do {
    // Display promt
    printf("> ");
    
    // Read + Parse input
    output = fgets(buffer, sizeof(buffer), stdin);
    
    if (strcmp(buffer, "0") != 0) {
      parseInput(buffer);
    }
  }
  while (output && strcmp(output, "exit"));
	 
  exitShell();

  return 0;
}

void exitShell (void) {
  printf("exiting...");
  exit(0);
}

void parseInput(char buffer[]) {
  buffer[strcspn(buffer, "\n")] = 0;
  char delims[] = " \t|><&;";
  
  char* token = strtok(buffer,delims);

  while(token != NULL){
    printf("%s\n", token);

    token = strtok(NULL, delims);
  }
}
