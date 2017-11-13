/**
  @file codepoints.h
  @author Summer Mims
  Project 5 UTF-8 Character Report
*/

/**
  Read and maintain list of codepoints.
  Each codepoints has a numeric code and string name
*/

/** constant for exit status 1 */
#define EXIT_1 1

/** constant for exit status 0 */
#define EXIT_0 0

/** maximum characters for code name */
#define NAME_MAX 90

/** initial line length */
#define LINE_INIT 90

/** initial number of codepoints */
#define INIT_CP 30;

/** max length of file line */
#define LINE_MAX 256

/** number 2 */
#define TWO 2

/**
  Struct for CodePoint
*/
struct CodePoint {
  // numeric is hexadecimal
  unsigned int val;
  // name of code point, can be up to 90 printable characters long
  char name[ NAME_MAX + 1 ];
};

/**
  Open unicode text file.
  Read code point descriptions into data structure, code point table
*/
void loadTable();

/**
  Free memory for the code point table
*/
void freeTable();

/**
  Given the numeric value of a code point, print a line to standard output
  with the name and code (return true)..
  Otherwise return false
  @param int the numeric value of a code point
  @return bool return true if the code is in the code point table
*/
bool reportCode( int code );
