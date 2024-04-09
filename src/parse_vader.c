// Make clangd shut up
#define _CRT_SECURE_NO_WARNINGS

#include "parse_vader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Parses a line from `file` into a Words. Puts the output in `wordPtr`
// Returns EXIT_SUCESS upon success and EXIT_FAILURE on failure
int parseLine(FILE *file, struct Words *wordPtr) {
  // Read a line from file into buff
  char buff[LINE_SIZE];
  char *ret = fgets(buff, LINE_SIZE, file);

  if (ret == NULL) { // Check the return value
    return EXIT_FAILURE;
  }

  // Tokenize buff by \t

  // Read the word
  char *token = strtok(buff, "\t");
  if (token == NULL) {
    return EXIT_FAILURE;
  }

  char *word = malloc(strlen(buff) + 1);
  // Check the return value
  if (word == NULL) {
    fprintf(stderr, "Unable to allocate memory\n");
    return EXIT_FAILURE;
  }
  wordPtr->word = word;
  strcpy(wordPtr->word, token);

  // Read the score
  token = strtok(NULL, "\t");
  if (token == NULL) {
    return EXIT_FAILURE;
  }

  wordPtr->score = strtof(token, NULL);

  // Read the SD
  token = strtok(NULL, "\t");
  if (token == NULL) {
    return EXIT_FAILURE;
  }

  wordPtr->SD = strtof(token, NULL);

  // Read the SIS_array
  token = strtok(NULL, "\t");
  if (token == NULL) {
    return EXIT_FAILURE;
  }

  int scanRet = sscanf(token, "[%d, %d, %d, %d, %d, %d, %d, %d, %d, %d]",
                       wordPtr->SIS_array, (wordPtr->SIS_array) + 1,
                       (wordPtr->SIS_array) + 2, (wordPtr->SIS_array) + 3,
                       (wordPtr->SIS_array) + 4, (wordPtr->SIS_array) + 5,
                       (wordPtr->SIS_array) + 6, (wordPtr->SIS_array) + 7,
                       (wordPtr->SIS_array) + 8, (wordPtr->SIS_array) + 9);

  if (scanRet != 10) {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

void freeWords(struct Words *words, int numWords) {
  for (int i = 0; i < numWords; i++) {
    free(words[i].word);
  }
  free(words);
}

int readWordsFromFile(FILE *file, struct Words **wordsPtr, int *numWordsPtr) {
  // Allocate an array to store all the words
  struct Words *words = malloc(sizeof(struct Words));
  // Check the return value
  if (words == NULL) {
    fprintf(stderr, "Unable to allocate memory\n");
    return EXIT_FAILURE;
  }

  // Keep track of the number of words read
  int numWords = 0;

  int ret;
  // Keep parsing each line until there's an error
  do {
    struct Words word;
    ret = parseLine(file, &word);

    if (ret == EXIT_SUCCESS) {
      numWords++;
      words = realloc(words, sizeof(struct Words) * numWords);

      if (words == NULL) {
        fprintf(stderr, "Unable to allocate memory\n");
        return EXIT_FAILURE;
      }

      words[numWords - 1] = word;
    }
  } while (ret == EXIT_SUCCESS);

  // Hand the words and numWords to the caller
  *wordsPtr = words;
  *numWordsPtr = numWords;

  return EXIT_SUCCESS;
}

struct Words *findWord(struct Words *words, int numWords, char *word) {
  for (int i = 0; i < numWords; i++) {
    if (strncmp(words[i].word, word, LINE_SIZE) == 0) {
      return words + i;
    }
  }

  return NULL;
}
