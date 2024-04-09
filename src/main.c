// Make clangd shut up
#define _CRT_SECURE_NO_WARNINGS

#include "parse_vader.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Converts a null terminated string to lowercase
void strToLower(char *str) {
  for (int i = 0; str[i] != '\0'; i++) {
    if (isupper(str[i])) {
      str[i] = tolower(str[i]);
    }
  }
}

int main(int argc, char *argv[]) {
  // Check the number of arguments
  if (argc != 3) {
    printf("Usage ./mySA <lexicon_file> <validation_file> \n");
  }

  // Read the vader lexicon file
  FILE *vaderLexiconFile = fopen(argv[1], "r");
  if (vaderLexiconFile == NULL) {
    printf("Unable to open file\n");
    return EXIT_FAILURE;
  }

  // Read the files from the word
  int numWords = 0;
  struct Words *words;

  int ret = readWordsFromFile(vaderLexiconFile, &words, &numWords);
  if (ret == EXIT_FAILURE) {
    return EXIT_FAILURE;
  }

  // Read the file of stuff to analyze
  FILE *validationFile = fopen(argv[2], "r");
  if (validationFile == NULL) {
    printf("Unable to open file\n");
    return EXIT_FAILURE;
  }

  printf("%-100s %s\n", "string sample", "score");
  for (int i = 0; i < 120; i++) {
    printf("-");
  }
  printf("\n");

  // Read each line into a buffer
  char buff[255];
  while (fgets(buff, 255, validationFile) != NULL) {
    // Remove the trailing newline
    buff[strcspn(buff, "\n\r")] = 0;
    printf("%-100s", buff);

    float scoreSum = 0;
    int numTokens = 0;

    // Split the string by spaces and some punctuation
    // Note that this doesn't work in cases where "words"
    // have punctuation in it
    char *token = strtok(buff, " \r\n,.!");
    while (token != NULL) {
      numTokens++;

      // Find the word and add its score to the sum
      strToLower(token);
      struct Words *word = findWord(words, numWords, token);
      if (word != NULL) {
        scoreSum += word->score;
      }

      // Get the next token
      token = strtok(NULL, " \r\n,.!");
    }

    // Print the average score
    printf("%.5f\n", scoreSum / numTokens);
  }

  freeWords(words, numWords);
  fclose(vaderLexiconFile);
  fclose(validationFile);

  return EXIT_SUCCESS;
}
