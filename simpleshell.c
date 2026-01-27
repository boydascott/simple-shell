#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main (void) {
  char* buffer = malloc(sizeof(char) * 512);

  printf("> ");
  fgets(buffer, sizeof(buffer), stdin);
  buffer[strcspn(buffer, "\n")] = 0; // deletes new line

  printf("%s", buffer);

  if (buffer == NULL) {
      printf("ctrl-d");
  }
  
  while (strcmp(buffer, "exit") != 0 && fgets(buffer, sizeof(buffer), stdin) != NULL) {
    printf("%s\n", buffer);
    printf("> ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
  }
  
  free(buffer);
  buffer = NULL;

  return 0;
}
