//---------------------------------------------------------------------
// match_braces.c
// CS223 - Spring 2022
// Identify matched braces from a given file
// Name: Jasmine Lei
// Date: 11 February 2022
//

#include <stdio.h>
#include <stdlib.h>

struct node {
  char sym;
  int linenum;
  int colnum;
  struct node* next;
};

// Push a new node to a stack (implemented as a linked list).
// The new node should store the given symbol, line number, and column number
// Param sym: a character symbol, '{' for this program
// Param line: the line number of the symbol
// Param line: the column number of the symbol
// Param top: the top node of the stack (NULL if empty)
// Returns the new top of the stack
struct node* push(char sym, int line, int col, struct node* top) {
  struct node * new_node = NULL;
  new_node = malloc(sizeof(struct node));
  if (new_node == NULL) {
    printf("Failed malloc, returning unchanged stack.\n");
    return top;
  }
  new_node->sym = sym;
  new_node->linenum = line;
  new_node->colnum = col;
  // connect to previous top, even if top == NULL
  new_node->next = top;
  return new_node;
}

// Pop the top node from a stack (implemented as a linked list) and frees it
// Param top: the top node of the current stack (NULL if empty)
// Returns the new top of the stack
struct node* pop(struct node* top) {
  if (top == NULL) {
    // nothing to pop
    return top;
  }
  // move top pointer and free the original top
  struct node * temp = top;
  top = top->next;
  free(temp);
  return top;
}

// Delete (e.g. free) all nodes in the given stack
// Param top: the top node of the stack (NULL if empty)
void clear(struct node* top) {
  struct node * temp = top;
  while (top != NULL) {
    temp = top->next;
    free(top);
    top = temp;
  }
  // here, all nodes freed and top == NULL, as desired
}

// Print all nodes in the given stack (from top to bottom)
// Param top: the top node of the stack (NULL if empty)
void print(struct node* top) {
  while (top != NULL) {
    printf("%c %d,%d\n", top->sym, top->linenum, top->colnum);
    top = top->next;
  }
}

int main(int argc, char* argv[]) {
  FILE* file;
  int line = 1;
  int column = 0;
  char ch;
  struct node * stack = NULL;

  if (argc != 2) {
    // wrong number of arguments
    printf("usage: ./match_braces\n");
    exit(1);
  }

  file = fopen(argv[1], "r");
  if(file == NULL) {
    printf("Cannot open file: %s\n", argv[1]);
    exit(1);
  }

  ch = fgetc(file);
  while (ch != EOF) {
    column++;
    if (ch == '{') {
      stack = push(ch, line, column, stack);
    } else if (ch == '}') {
      if (stack == NULL) {
        // no matching brace on the stack
        printf("Unmatched brace on Line %d and Column %d\n", line, column);
      } else {
        printf("Found matching braces: (%d, %d) -> (%d, %d)\n",
            stack->linenum, stack->colnum, line, column);
        stack = pop(stack);
      }
    } else if (ch == '\n') {
      line++;
      column = 0;
    }
    ch = fgetc(file);
  }

  // anything still on stack at end of file is an unmatched left brace
  while (stack != NULL) {
    printf("Unmatched brace on Line %d and Column %d\n",
        stack->linenum, stack->colnum);
    stack = pop(stack);
  }

  fclose(file);
  clear(stack);
  return 0;
}
