#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
  char *from = malloc(sizeof(char) * length1);
  char *to = malloc(sizeof(char) * length2);
  strcpy(from, argv[1]);
  strcpy(to, argv[2]);

  // Read in file
  char *character = malloc(sizeof(char));
  
  while (read(0, &character[0], 1) > 0) {

    // For each character, translate it if exists in operands
    int translated = 0;
    char *translateTo = malloc(sizeof(char));
    for (i = 0; i < length1; i++) {
      if (from[i] == *character) {
	translateTo[0] = to[i];
	write(1, translateTo, 1);
	translated = 1;
	break;
      }
    }

    if (!translated)
      write(1, character, 1);

    free(translateTo);
  }

  free(character);
  free(from);
  free(to);
  free(fromUnique);
}

