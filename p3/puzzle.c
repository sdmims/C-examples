/**
  @file puzzle.c
  @author Summer Mims
  Project 3: Puzzle
  This file contains the main function and any functions that do not
  pertain to commands or moving the board.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "board.h"
#include "command.h"

/** exit status 1 */
#define EXIT_1 1

/**
  Helper method to determine if puzzle is in solved state.
  Compares current board to initial board.
  Returns true if all elements match.
  Returns false otherwise
*/
bool isSolved( int rows, int cols, int b[][ cols ], int s[][ cols ] )
{
  for ( int i = 0; i < rows; i++ ) {
    for ( int j = 0; j < cols; j++ ) {
      if ( b[ i ][ j ] != s[ i ][ j ] ) {
        return false;
      } // if
    } // j
   } // i
   return true;

} // function

/**
  Helper function to print board in correct color.
  Print in blue if solved.
  print in black otherwise.
*/
void printMe( int rows, int cols, int board[][ cols ], int solvedBoard[][ cols ] )
{
  putchar( '\n' );
  // check if solved - if so print in blue
  if ( isSolved( rows, cols, board, solvedBoard ) ) {
    printf( "\033[34m" );
    printBoard( rows, cols, board );
    printf( "\033[0m" );
  }
  else {
    printBoard( rows, cols, board );
  }
  printf( "%s", "> " );
}

/**
  One optional command line argument for name of configuration file
    If given, first line is two integers for board size.
    Any following will be commands to shuffle puzzle
    If configuration file is invalid
      Print "Invalid configuration" to std error
      Exit status 1
  If no arugment provided
    Create 5 rows and 7 columns
  If more than one argument provided
    Print "usage: puzzle [config-file]" to std error
    Exit status 1
  If file fails to open
    Print "Can't open config file: config.txt"
    Print "usage: puzzle [config-file]" to std error
    Exit status 1
*/
int main( int argc, char *argv[] )
{
  int rows = DEFAULT_ROWS;
  int cols = DEFAULT_COLS;
  FILE *fin = NULL;

  // if more than one argument
  if ( argc > 2 ) {
    fprintf( stderr, "usage: puzzle [config-file]\n" );
    exit( EXIT_1 );
  }

  // valid configuration file
  if ( argc == 2 ) {
    fin = fopen( argv[1], "r" );
    // error reading file
    if ( !fin ) {
      fprintf( stderr, "Can't open config file: %s\n", argv[1] );
      fprintf( stderr, "usage: puzzle [config-file]\n" );
      exit( EXIT_1 );
    }

    // read dimensions
    int n = fscanf( fin, "%d%d", &rows, &cols );
    // error reading dimensions
    if ( n != 2 ) {
      fprintf( stderr, "Invalid configuration\n" );
      exit( EXIT_1 );
    }
    char ch = fgetc( fin );
    while ( ch != '\n' && ch != EOF ) {
      ch = fgetc( fin );
    }
 }

  // create board
  int board[ rows ][ cols ];
  initBoard( rows, cols, board );

  // create solved state board
  int solvedBoard[ rows ][ cols ];
  initBoard( rows, cols, solvedBoard );

  // var to store command
  char cmd[ CMD_LIMIT + 2 ];

  // if config file
  if ( fin ) {
    // read moves from file
    while ( getCommand( fin, cmd ) ) {
      // make move
      if ( !runCommand( cmd, rows, cols, board ) ) {
        // error in file
        fprintf( stderr, "Invalid configuration\n" );
        exit( EXIT_1 );
      }
    } // end while getCMD file

    // close file stream
    fclose( fin );
  }

  // initialize history
  // any commands from config overwritten
  initHistory();

  printMe( rows, cols, board, solvedBoard );
  // get user input
  while ( getCommand( stdin, cmd ) ) {
    // make move
    if ( !runCommand( cmd, rows, cols, board ) ) {
      // invalid command
      printf( "Invalid command\n" );
    }
    printMe( rows, cols, board, solvedBoard );
  } // end while getCMD stdin
}
