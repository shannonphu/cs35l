#include <stdio.h>
#include <stdlib.h>

// Input points to array of non-space bytes
// followed by space byte.
// Serves as the custom sorting we want to use
// in qsort.
int frobcmp(const void *a, const void *b)
{
  // Defrobnicate the strings and compare character
  // by character

  char *str1 = (char *)a;
  char *str2 = (char *)b;
  printf("%s %s\n", str1, str2);
  int i = 0;
  while (str1[i] != ' ') {
    char firstChar = str1[i];
    char secondChar = str2[i];
    if (firstChar == secondChar)
      continue;
    printf("i = %d\n", i);
    /*if (firstChar == secondChar == '\n')
      break;
    */
    printf("%c == %c\n", firstChar, firstChar ^ 42);
    printf("%c == %c\n", secondChar, secondChar ^ 42);
    //    printf("%c", (str1[2] ^ 42));
    if ((firstChar ^ 42) < (secondChar ^ 42))
      return -1;
    else if ((firstChar ^ 42) > (secondChar ^ 42))
      return 1;

    i++;
  }

  return 0;
}

// Loop through the 2D array and print out
// its contents
void printOut(char **words, int numLines)
{
  int i, j;
  for (i = 0; i <= numLines; i++) {
    j = 0;
    while (words[i][j] != ' ') {
      printf("%c", words[i][j]);
      j++;
    }
    printf("\n");
  }
}

int main(int argc, char *argv[])
{
  int index = 0;
  char *input = malloc(100 * sizeof(char));
  int size = 100 * sizeof(char *);
  
  // Declare 2-D array holding every line of
  // input (assuming 100 lines)
  char **allInput = malloc(size);
  // Declare array holding string until space (assuming 50 char)
  char *line = malloc(50 * sizeof(char));
  int lineNum = 0;

  // Build 2-D array
  while (1) {
    int character = getchar();
    if (character == EOF)
      break;

    // If new line reached, put space at end of
    // C string, reset index counter of line to 0,
    // and allocate new array for next word.
    if (character == ' ') {
      line[index] = ' ';
      allInput[lineNum] = line;
      lineNum++;
      line = malloc(50 * sizeof(char));
      index = 0;
      continue;
    }

    line[index] = character;
    index++;
  }

  line[index] = ' ';
  allInput[lineNum] = line;

  //  qsort(allInput, 100, sizeof(char *), frobcmp);
  printf("lineNum: %d\n", lineNum);
  printOut(allInput, lineNum);
  printf("--------\n");
  
  int res = frobcmp(input, "*~BO *{_CIA *hXE]D *LER #@_GZY");

  printf("%d\n", res);
}
