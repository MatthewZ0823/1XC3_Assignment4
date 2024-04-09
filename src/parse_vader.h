#include <stdio.h>

#ifndef PARSE_VADER_H
#define PARSE_VADER_H

#define LINE_SIZE 255
#define SIS_ARRAY_SIZE 10

// Struct containing a word with its assosicated score and others
struct Words {
  char *word;
  float score;
  float SD;
  int SIS_array[SIS_ARRAY_SIZE];
};

// Frees a list of Words from memory
void freeWords(struct Words *words, int numWords);

// Reads a list of words from `file` and puts copies the result into `wordsPtr`
// and `numWordsPtr`. Caller is responsible for freeing `*wordsPtr`
// Returns EXIT_SUCCESS upon success and EXIT_FAILURE upon failure
int readWordsFromFile(FILE *file, struct Words **wordsPtr, int *numWordsPtr);

// Returns a pointer to a Words in a list `words` that matches `word`
// Returns NULL if not found
struct Words *findWord(struct Words *words, int numWords, char *word);

#endif
