/**
  @file magic.c
  @author Summer Mims
  Project 2 Magic Number Highlighter
*/

#include <stdio.h>
#include <stdlib.h>

/**
  starting point
  @return exit status
*/


/**
  Print a valid integer in red.
  Change text color back to black before exitting function.
*/
void highlightNumber()
{
  int ch;

  // change to text color to red
  printf( "\033[31m" );

  while ( ( ch = getchar() ) != EOF ) {
    //
    if ( ch >= '0' && ch <= '9' ) {
      printf( "%c", ch );
    }

    else {
      ungetc( ch, stdin );
      break;
    }
  }
  
  // change text color back to black
  printf( "\033[0m" );

} // end highlightNumber


/**
  Read and print indentifier until non-identifier character is read.
  Then return control to main to control flow.
*/
void skipIdentifier()
{
  int ch;

  while ( ( ch = getchar() ) != EOF ) {
    // if  digit, number, underscore, still identifier
    if ( ( ch >= 'a' && ch <= 'z' ) || ( ch >= 'A' && ch <= 'Z' )
         || ch == '_' || ( ch >= '0' && ch <= '9' ) ) {
      putchar( ch );
    }
    else {
      putchar( ch );
      break;
    }
  }
} // end skipIdentifier

/**
  This method takes standard input and prints the input to standard output.
  Integer values printed in red. ANSI escape codes are used to change the
  printing color as necessary.
  Integers that are part of an identifier will not be highlighted, only stand
  alone integer values.
*/
int main()
{
  // store character read in
  int ch;

  while ( ( ch = getchar() ) != EOF ) {
    // valid integer
    if ( ch >= '0' && ch <= '9' ) {
      ungetc( ch, stdin );
      highlightNumber();
    }

    // start of an identifier
    // digit or underscore
    else if ( ( ch >= 'a' && ch <= 'z') || ( ch >= 'A' && ch <= 'Z' )
          || ch == '_' ) {
      putchar( ch );
      skipIdentifier();
    }

    // other, keep reading
    else {
      putchar( ch );
    }
  } // end while

  return EXIT_SUCCESS;
}
