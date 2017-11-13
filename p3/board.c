/**
  @file board.c
  @author Summer Mims
  Project 3: Puzzle
  This file defines functions for working with the puzzle board.
  The board is a variable sized two-dimensional array of ints.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "board.h"

/**
  Initializes a board to given dimensions.
  Fills in values in given board.
*/
void initBoard( int rows, int cols, int board[][cols] )
{
  int c = 1;
  for ( int i = 0; i < rows; i++ ){
    for ( int j = 0; j < cols; j++ ) {
     board[i][j] =  c;
     c++;
    }
  }
}

/**
  Prints board to standard output.
  Prints the board in blue if it is in the solved state.
*/
void printBoard( int rows, int cols, int board[][cols] )
{
  for ( int i = 0; i < rows; i++ ){
    for ( int j = 0; j < cols; j++ ) {
     if ( board[i][j] < 10 ) {
       printf( "  %d", board[i][j] );
     }
     else {
       printf( " %d", board[i][j] );
     }
    }
    putchar( '\n' );
  }
}

/**
  For internal use in board.c
  Finds a given tile in a given board.
  Places the row and column location in the r and c pointers.
  Returns true if tile exist
  Returns false if tile DNE
*/
static bool findTile( int tile, int rows, int cols, int board[][cols], int *r, int *c )
{
  for ( int i = 0; i < rows; i++ ){
    for ( int j = 0; j < cols; j++ ) {
      if ( board[i][j] == tile ) {
        // tile is found
        *r = i;
        *c = j;
        return true;
      }
    }
  }
  // tile not found
  return false;
}

/**
  Makes moves down on board.
  Uses the findTile function to find the location of the tile to move.
*/
bool moveDown( int tile, int rows, int cols, int board[][cols] )
{
  int r = 0;
  int c = 0;
  if ( findTile( tile, rows, cols, board, &r, &c )) {
    // if the tile is found, only need the c value
    // store the last tile
    int temp = board[ rows - 1 ][ c ];

    for ( int i =  rows - 1; i >= 1; i-- ){
      board[ i ][ c ] = board [ i - 1 ][ c ];
    }
    board[ 0 ][ c ] = temp;
    // move performed, return true
    return true;
  }
  return false;
}

/**
  Makes moves up on board.
  Uses the findTile function to find the location of the tile to move.
*/
bool moveUp( int tile, int rows, int cols, int board[][cols] )
{
  int r = 0;
  int c = 0;
  if ( findTile( tile, rows, cols, board, &r, &c )) {
    // if the tile is found, only need the c value
    // store the first tile
    int temp = board[ 0 ][ c ];

    for ( int i =  0; i < ( rows - 1 ); i++ ){
      board[ i ][ c ] = board [ i + 1 ][ c ];
    }
    board[ rows - 1 ][ c ] = temp;
    // move performed, return true
    return true;
  }
  return false;
}

/**
  Makes moves left on board.
  Uses the findTile function to find the location of the tile to move.
*/
bool moveLeft( int tile, int rows, int cols, int board[][cols] )
{
  int r = 0;
  int c = 0;
  if ( findTile( tile, rows, cols, board, &r, &c )) {
    // if the tile is found, only need the r value
    // store the first tile
    int temp = board[ r ][ 0 ];

    for ( int i =  0; i < ( cols - 1 ); i++ ){
      board[ r ][ i ] = board [ r ][ i + 1 ];
    }
    board[ r ][ cols - 1 ] = temp;
    // move performed, return true
    return true;
  }
  return false;
}

/**
  Makes moves right on board.
  Uses the findTile function to find the location of the tile to move.
*/
bool moveRight( int tile, int rows, int cols, int board[][cols] )
{
  int r = 0;
  int c = 0;
  if ( findTile( tile, rows, cols, board, &r, &c )) {
    // if the tile is found, only need the r value
    // store the last tile
    int temp = board[ r ][ cols - 1 ];

    for ( int i =  cols - 1; i >= 1; i-- ){
      board[ r ][ i ] = board [ r ][ i - 1 ];
    }
    board[ r ][ 0 ] = temp;
    // move performed, return true
    return true;
  }
  return false;
}
