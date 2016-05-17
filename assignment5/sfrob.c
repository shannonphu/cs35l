#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int total = 0;

// Input points to array of non-space bytes
// followed by space byte.
// Serves as the custom sorting we want to use
// in qsort which is indirectly called by cmp
int frobcmp(char const *a, char const *b)
{
  // Defrobnicate the strings and compare character
  // by character
  total++;
  int i = 0;
  while (a[i] != ' ' && b[i] != ' ') {
    char firstChar = a[i];
    char secondChar = b[i];
    
    if (firstChar != secondChar) {
      return (firstChar ^ 42) - (secondChar ^ 42);
    }

    i++;
  }

  // Check if one is prefix of another since no differences
  if (a[i] == ' ' && b[i] != ' ') {
    return -1;
  } else if (b[i] == ' ' && a[i] != ' ') {
    return 1;
  }

  return 0;
}

int cmp(const void *a, const void *b)
{
  char *str1 = *(char **)a;
  char *str2 = *(char **)b;
  
  return frobcmp(str1, str2);
}

// Loop through the 2D array and print out
// its contents
void printOut(char **words, int numLines, int frob)
{
  int i, j;
  for (i = 0; i < numLines; i++) {
    j = 0;
    while (words[i][j] != ' ') {
      if (!frob)
	putchar(words[i][j] ^ 42);
      else
	putchar(words[i][j]);
      j++;
    }
    putchar(' ');
  }
  
}

int main(int argc, char *argv[])
{
  int index = 0;

  // Start off with enough memory for 10 "lines"
  int arraySize = 5 * sizeof(char *);
  int lineSize = 5 * sizeof(char);
  
  // Declare 2-D array holding every line of
  // input (assuming 10 lines)
  char **allInput = (char **)malloc(arraySize);

  // Declare array holding string until space
  // (assuming 10 char per string initially)
  char *line = malloc(lineSize);
  int lineNum = 0;

  if (!allInput || !line) {
    fprintf(stderr, "No memory. Exiting.\n");
    exit(1);
  }
  
  // Build 2-D array
  while (1) {
    int character = getchar();
    if (character == EOF) { 
      break;
    }

    // if need more memory for a line
    if (index != 0 && index % 5 == 0) {
      lineSize += 5 * sizeof(char);
      char *temp = (char *)realloc(line, lineSize);
      if (!temp) {
	fprintf(stderr, "Not enough memory. Exiting.\n");
	exit(1);
      }
      line = temp;
    }

    line[index] = character;

    // If new line reached, put space at end of
    // C string, reset index counter of line to 0,
    // and allocate new array for next word.
    if (character == ' ') {

      // If need more memory for more lines
      if (lineNum != 0 && lineNum % 5 == 0) {
	arraySize += 5 * sizeof(char *);
	char **temp2 = (char **)realloc(allInput, arraySize);
	if (!temp2) {
	  fprintf(stderr, "Not enough memory. Exiting.\n");
	  exit(1);
	}
	allInput = temp2;
      }

      allInput[lineNum] = line;
      lineNum++;
      line = malloc(5 * sizeof(char));
      index = 0;
      lineSize = 5 * sizeof(char);
      continue;
    }

    index++;
  }
  
  // If the last word entered doesn't have a
  // space at the end, put one there.
  
  if (strcmp(line, "") != 0 && line[index] != ' ') {
    line[index] = ' ';
    allInput[lineNum++] = line;
  } else {
    free(line);
  }

  // Sort the array of C-strings
  qsort(allInput, lineNum, sizeof(char *), cmp);
  
  printOut(allInput, lineNum, 1);

  if (*line != '\000')
    free(line);
  free(allInput);

  printf("Comparisons: %d", total);
  //////////////////////////
  // Comparison tests
  //////////////////////////
  char *test1 = "*{_CIA\030\031 ";
  char *test2 = "*`_GZY\v ";
  
  // should return \0Quick cmp \0Jumps! so 1
  assert( frobcmp(test1, test2) > 0 );

  // should return \0Jumps! cmp \0Quick so -1
  assert( frobcmp(test2, test1) < 0 );

  // should return \0Jumps! < \0Jumps! so 0
  assert( frobcmp(test2, test2) == 0 );

  return 0;
}
