/**
  @file command.h
  @author Summer Mims
  Project 3: Puzzle
*/

/** Maximum number of characters for a command */
#define CMD_LIMIT 30

/** Maximum number of commands stored */
#define MAX_COMMANDS 10

/** Array of strings to hold 10 most recent commands */
extern char history[ MAX_COMMANDS ][ CMD_LIMIT + 1 ];

/** The number of commands in the history */
extern int histLen;

/**
  Reads and discards charactrs up to newline.
  Can be used to discard the rest of a line if too long.
*/
void skipLine( FILE *stream );

/**
  Function prototype for getCommand
  Reads a line of up to 31 characters from given stream.
  Stored in cmd.
  Returns true if successfully reads a line.
  Returns false at EOF
*/
bool getCommand( FILE *stream, char cmd[ CMD_LIMIT + 2 ] );

/**
  Helper function to initialize history
  Reset len to 0
*/
void initHistory();

/**
  Helper function to add commands to history.
  If histLen is greater than max, do not add command.
*/
void addHistory( char cmd[ CMD_LIMIT + 1 ] );

/**
  Helper function to perform undo moves.
  Reads move from history.
  Performs opposite move
*/
bool undo( int rows, int cols, int board[][ cols ] );

/**
  function protptype for runCommand
  Performs the given commands.
  Returns true if command is valid.
  Returns false if invalid
*/
bool runCommand( char cmd[ CMD_LIMIT + 1], int rows, int cols, int board[][ cols ] );
