#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

  // If no arguments passed in, report error and return
  if (argv[1] == NULL || argv[2] == NULL) {
    printf("Invalid number of arguments passed in.\n");
    exit(1);
  }
  
  int i, j;
  int length1 = strlen(argv[1]);
  int length2 = strlen(argv[2]);

  // If the 2 operands differ in length, report error and return
  if (length1 != length2) {
    printf("Arguments are different lengths.\n");
    exit(1);
  }

  char *fromUnique = malloc(sizeof(char) * length1);
  int numInFromUnique = 0;
  for (i = 0; i < length1; i++) {
    char c = argv[1][i];
    for (j = 0; j < numInFromUnique; j++) {
      if (c == fromUnique[j]) {
	printf("Repeated byte in first operand.\n");
	exit(1);
      }
    }
    fromUnique[numInFromUnique] = c;
    ++numInFromUnique;
  }   

  // Get arguments
  char *from = (char *)malloc(sizeof(char) * length1);
  char *to = (char *)malloc(sizeof(char) * length2);
  strcpy(from, argv[1]);
  strcpy(to, argv[2]);

  /*  printf("%s %s", from, to);
  
  if (from[0] != '\'' || to[0] != '\'' || from[0] != '\"' || to[0] != '\'') {
    printf("Invalid argument format.\n");
    exit(1);
  }

  printf("%c", from[length1 - 2]);
  if (from[length1 - 1] != '\"' || from[length1 - 1] != '\'' || to[length1 - 1] != '\"' || to[length1 - 1] != '\'') {
    printf("Invalid argument format.\n");
    exit(1);
    } */

  // Read in file
  while (1) {
    char character = getchar();
    
    if (character == EOF)
      break;

    // For each character, translate it if exists in operands
    int translated = 0;
    for (i = 0; i < length1; i++) {
      if (from[i] == character) {
	char translateTo = to[i];
	putchar(translateTo);
	translated = 1;
	break;
      }
    }

    if (!translated)
      putchar(character);
  }

  free(from);
  free(to);
  free(fromUnique);
}

