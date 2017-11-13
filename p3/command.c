/**
  @file command.c
  @author Summer Mims
  Project 3: Puzzle
  This file defines functions for reading and executing user commands.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "command.h"
#include "board.h"

/** string commands */
#define CMD_UP "up"
#define CMD_DOWN "down"
#define CMD_LEFT "left"
#define CMD_RIGHT "right"
#define CMD_UNDO "undo"
#define CMD_QUIT "quit"

/** exit success */
#define EXIT_0 0

// initiate history
int histLen = 0;
char history[ MAX_COMMANDS ][ CMD_LIMIT + 1 ];

/**
  Reads and discards charactrs up to newline.
  Can be used to discard the rest of a line if too long.
*/
void skipLine( FILE *stream )
{
  char ch = fgetc( stream );
  while ( ch != '\n' && ch != EOF ) {
    ch = fgetc( stream );
  }
}

/**
  Reads a line of up to 31 characters from given stream.
  Stored in cmd.
  Returns true if successfully reads a line.
  Returns false at EOF
*/
bool getCommand( FILE *stream, char cmd[ CMD_LIMIT + 2 ] )
{
  int c = fscanf( stream, "%30[^\n]", cmd );
  // if did not read command, return false
  // no need for skipLine
  if ( c != 1 ) {
    return false;
  }
  skipLine( stream );
  return true;
}


/**
  Commands
  up n
    n is the number of a tile
    Moves all tiles in column up by one
    Topmost wraps to bottom
  down n
    n is the number of a tile
    Moves all tiles in column down by one
    Bottom wraps to top
  left n
    n is the number of a tile
    Moves all tiles in row left by one
    Left wraps to right
  right n
    n is the number of a tile
    Moves all tiles in row right by one
    Right wraps to left
  undo
    Undoes most recent command
    Program keeps an undo history of 10 most recent moves
    Undo or quit commands are not saved
    Commands from config file are not saved
  quit
    Terminate program immediately
  invalid commands
    Longer than 30 characters
    Invalid number
    Not format of six specified commands
    Print "Invalid command" and prompt again
*/

/**
  Helper function to initialize history
  Reset len to 0
*/
void initHistory()
{
  histLen = 0;
}

/**
  Helper function to add commands to history.
  If histLen is greater than max, do not add command.
*/
void addHistory( char cmd[ CMD_LIMIT + 1 ] )
{
    if ( histLen == MAX_COMMANDS ) {
    // need to shift all commands left
    for ( int i = 0; i < histLen - 1; i++ ) {
      strcpy( history[ i ], history [ i + 1 ] );
    }
    strcpy( history[ histLen - 1 ], cmd );
    // do not increase histLen; already at 10
  }
  if ( histLen < MAX_COMMANDS ) {
    // puts command at index histLen-1
    strcpy( history[ histLen ], cmd );
    histLen++;
  }

}

/**
  Helper function to perform undo moves.
  Reads move from history.
  Performs opposite move
*/
bool undo( int rows, int cols, int board[][ cols ] )
{
  if ( histLen == 0 ) {
    return false;
  }

  // get last history cmd
  char cmd[ CMD_LIMIT ];
  strcpy( cmd, history[ histLen - 1 ] );

  int tileUndo = 0;
  char moveUndo[ CMD_LIMIT ];
  
  sscanf( cmd, "%s%d", moveUndo, &tileUndo );

  // do the opposite
  if ( strcmp( moveUndo, CMD_UP ) == 0 ) {
    moveDown( tileUndo, rows, cols, board );
  }
  else if ( strcmp( moveUndo, CMD_DOWN ) == 0 ) {
    moveUp( tileUndo, rows, cols, board );
  }
  else if ( strcmp( moveUndo, CMD_LEFT ) == 0 ) {
    moveRight( tileUndo, rows, cols, board );
  }
  else if ( strcmp( moveUndo, CMD_RIGHT ) == 0 ) {
    moveLeft( tileUndo, rows, cols, board );
  }
  // decrease history len
  histLen--;
  return true;
}

/**
  Performs the given commands.
  Returns true if command is valid.
  Returns false if invalid
*/
bool runCommand( char cmd[ CMD_LIMIT + 1 ], int rows, int cols, int board[][ cols ] )
{
  // parse cmd into move and tile
  char move[ CMD_LIMIT ];
  int tile = 0;
  char extra[ CMD_LIMIT ];
  int m = sscanf( cmd, "%s%d%s", move, &tile, extra );

  // if m = 1, can only be 2 commands - undo or quit
  if ( m == 1 ) {
    if ( strcmp( move, CMD_UNDO ) == 0 ) {
      return undo( rows, cols, board );
    }
    else if ( strcmp( move, CMD_QUIT ) == 0 ) {
      exit (EXIT_0 );
    }
  }
  // if m = 2, can be any move
  else if ( m == 2 ) {
    // check tile number
    if ( tile > rows * cols) {
      return false;
    }
    if ( tile < 1 ) {
      return false;
    }
    // check for valid move
    if ( strcmp( move, CMD_UP ) == 0 ) {
      // make the move
      moveUp( tile, rows, cols, board );
      // add to history
      addHistory( cmd );
      return true;
    }
    else if ( strcmp( move, CMD_DOWN ) == 0 ) {
      // make the move
      moveDown( tile, rows, cols, board );
      // add to history
      addHistory( cmd );
      return true;
    }
    else if ( strcmp( move, CMD_LEFT ) == 0 ) {
      // make the move
      moveLeft( tile, rows, cols, board );
      // add to history
      addHistory( cmd );
      return true;
    }
    else if ( strcmp( move, CMD_RIGHT ) == 0 ) {
      // make the move
      moveRight( tile, rows, cols, board );
      // add to history
      addHistory( cmd );
      return true;
    }
  }
  // anything else invalid command
  return false;
}
