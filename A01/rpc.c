/* rpc.c
 * Jasmine Lei
 * 28 January 2022
 * Plays a game of rock, paper, scissors against the user
 * for a given number of rounds
 */

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

/* Given the AI's choice and the player's choice,
 * where 0 = rock, 1 = paper, and 2 = scissors,
 * returns an int representing the winner of the round,
 * where -1 = AI wins, 0 = tie, 1 = player wins
 */
int pick_winner(int ai_choice, int player_choice) {
  if (ai_choice == player_choice) {
    return 0;  // tie
  } else if (ai_choice + player_choice == 1) {
    printf("Paper covers rock\n");
    if (ai_choice == 0) {
      return 1;
    } else {
      return -1;
    }
  } else if (ai_choice + player_choice == 2) {
    printf("Rock bashes scissors\n");
    if (ai_choice == 0) {
      return -1;
    } else {
      return 1;
    }
  } else {  // ai_choice + player_choice == 3
    printf("Scissors cut paper\n");
    if (ai_choice == 2) {
      return -1;
    } else {
      return 1;
    }
  }
}

int main() {
  srand(time(0));
  int rounds, ai_choice, winner;
  char player_play[75];
  int ai_points = 0;
  int player_points = 0;

  printf("Welcome to Rock, Paper, Scissors.\n");
  printf("How many rounds do you want to play? ");
  scanf("%d", &rounds);

  for (int i = 0; i < rounds; i++) {
    printf("\nWhich do you choose: rock, paper, or scissors? ");
    scanf("%s", player_play);
    // ai chooses a random int: 0, 1, or 2;
    ai_choice = rand() % 3;
    if (ai_choice == 0) {
      printf("AI chose rock\n");
    } else if (ai_choice == 1) {
      printf("AI chose paper\n");
    } else {
      printf("AI chose scissors\n");
    }
    // decide the winner of this round
    if (strcmp(player_play, "rock") == 0) {
      winner = pick_winner(ai_choice, 0);
    } else if (strcmp(player_play, "paper") == 0) {
      winner = pick_winner(ai_choice, 1);
    } else if (strcmp(player_play, "scissors") == 0) {
      winner = pick_winner(ai_choice, 2);
    } else {
      printf("You entered an invalid choice: %s\n", player_play);
    }
    // if there was a winner, increase tally
    if (winner == 1) {
      player_points++;
    } else if (winner == -1) {
      ai_points++;
    }
    printf("AI score: %d, Player score: %d\n", ai_points, player_points);
  }

  // print final results
  if (player_points > ai_points) {
    printf("\nPlayer wins!\n");
  } else if (player_points < ai_points) {
    printf("\nAI wins!\n");
  } else {
    printf("\nIt's a tie!\n");
  }

  return 0;
}
