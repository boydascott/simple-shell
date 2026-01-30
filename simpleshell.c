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
  char buffer[512];
  char delims[] = " \t|><&;";
  printf("> ");
  fgets(buffer, sizeof(buffer), stdin);
  
  
  while (*buffer != 'q') {
    splitstring(buffer, delims);
    printf("> ");
    fgets(buffer, sizeof(buffer), stdin);
  }

  return 0;
}
