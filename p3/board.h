/**
  @file board.h
  @author Summer Mims
  Project 3: Puzzle
*/

/** default rows and columns */
#define DEFAULT_ROWS 5
#define DEFAULT_COLS 7

/**
  prototye for initBoard
  Initializes a board to given dimensions.
  Fills in values in given board.
  Default to 5x7 board if no user input
*/
void initBoard( int rows, int cols, int board[][ cols ] );

/**
  prototype for printBoard
  Prints board to standard output.
  Prints the board in blue if it is in the solved state.
*/
void printBoard( int rows, int cols, int board[][ cols ] );

/**
  Makes moves up on board.
  Uses the findTile function to find the location of the tile to move.
*/
bool moveUp( int tile, int rows, int cols, int board[][ cols ] );

/**
  Makes moves down on board.
  Uses the findTile function to find the location of the tile to move.
*/
bool moveDown( int tile, int rows, int cols, int board[][ cols ] );

/**
  Makes moves left on board.
  Uses the findTile function to find the location of the tile to move.
*/
bool moveLeft( int tile, int rows, int cols, int board[][ cols ] );

/**
  Makes moves right on board.
  Uses the findTile function to find the location of the tile to move.
*/
bool moveRight( int tile, int rows, int cols, int board[][ cols ] );
