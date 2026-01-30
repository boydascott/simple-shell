#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>




void exitShell (void) {  
  printf("exiting...");
  exit(0);
}

char** parseInput(char buffer[]) {
  char** ptr;
  ptr = malloc(sizeof(char*) * 50);
  buffer[strcspn(buffer, "\n")] = 0;
  char delims[] = " \t|><&;";
  int i = 0;
  
  char* token = strtok(buffer,delims);

  while(token != NULL){
    ptr[i] = token;
    printf("%s\n", token);

    token = strtok(NULL, delims);
    i++;
  }

  if (ptr[0] == NULL) {
    ptr[0] = "";
  }
  
  return ptr;
}
