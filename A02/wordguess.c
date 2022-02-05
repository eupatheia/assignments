/*
 * Plays a word game with the user, who guesses a character at a time
 * until the entire word is guessed
 * Random words are chosen from words.txt
 * Jasmine Lei
 * 04 February 2022
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int main() {
  srand(time(0));
  FILE* word_list;
  int total_words, index;
  int turns = 0;
  int guessed = 0;
  char guess;
  char word[32];

  // try to open file list of words
  word_list = fopen("words.txt", "r");
  if (word_list == NULL) {
    printf("Error: unable to open file\n");
    exit(1);
  }
  //read in total number of words
  fgets(word, 32, word_list);
  total_words = atoi(word);

  index = rand() % total_words + 1;
  // read up to the index-th line to select random word
  for (int i = 0; i < index; i++) {
    fgets(word, 32, word_list);
  }
  fclose(word_list);
  // overwrite trailing newline characters
  word[strlen(word) - 1] = '\0';

  // represents currently known/unknown characters in word
  // '_' = unknown character, otherwise guessed character
  char progress[32];
  // start with all unknowns
  for (int i = 0; i < strlen(word); i++) {
    progress[i] = '_';
  }
  progress[strlen(word)] = '\0';

  printf("Welcome to Word Guess!\n");
  // keep playing until all characters guessed
  while (guessed < strlen(word)) {
    turns++;
    printf("\nTurn %d\n\n", turns);
    for (int i = 0; i < strlen(progress); i++) {
      printf("%c ", progress[i]);
    }
    printf("\nGuess a character: ");
    scanf(" %c", &guess); // space gets rid of trailing newline
    int matches = 0;
    for (int i = 0; i < strlen(word); i++) {
      // only count new matches
      if (guess == word[i] && progress[i] != guess) {
        progress[i] = guess;
        guessed++;
        matches++;
      }
    }
    if (matches == 0) {
      printf("Sorry, '%c' not found!\n", guess);
    }
  }
  printf("\n");
  // print final word
  for (int i = 0; i < strlen(progress); i++) {
    printf("%c ", progress[i]);
  }
  printf("\nYou won in %d turns!\n", turns);

  return 0;
}
