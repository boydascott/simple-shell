#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

void splitstring(char buffer[],char delims[]) {  
  char* token = strtok(buffer,delims);

     while(token != NULL){
          printf("%s\n", token);

          token = strtok(NULL, delims);
     }
  
  return ;
}

int main (void) {
  char* buffer = malloc(sizeof(char) * 512);
  char delims[] = " \t|><&;";
  printf("> ");
  fgets(buffer, sizeof(buffer), stdin);
  buffer[strcspn(buffer, "\n")] = 0; // deletes new line
  
  while (strcmp(buffer, "exit") != 0 && fgets(buffer, sizeof(buffer), stdin) != NULL) {
    splitstring(buffer, delims);
    printf("%s\n", buffer);
    printf("> ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
  }
  
  free(buffer);
  buffer = NULL;

  return 0;
}
