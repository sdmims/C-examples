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

  // boolean to indicate if int expression possible
  // start at true
  int check = 1;

  //is the text red
  //false is black, true is red
  int red = 0;

  while ( ( ch = getchar() ) != EOF ) {

    // integers
    if ( ch >= '0' && ch <= '9' ) {
        // if check true, print in red
        if ( check == 1 ){
          if ( red == 0 ) {
            printf( "\033[31m%c", ch );
            red = 1;
          }
          else {
            printf ( "%c", ch );
          }
        }
        else {
          printf( "%c", ch );
        }
    }  // end if

    // digits
    else if ( ( ch >= 'a' && ch <= 'z') || ( ch >= 'A' && ch <= 'Z' ) 
              || ch == '_' ) {
      // print normal
      if ( red == 1 ) {
        printf( "\033[0m%c", ch );
        red = 0;
      }
      else {
        printf( "%c", ch );
      }
      // set check to false
      check = 0;
    } // end else if

    // other characters
    else {
      // print normal
      if ( red == 1 ) {
        printf( "\033[0m%c", ch );
        red = 0;
      }
      else {
        printf( "%c", ch );
      }
      // set check to true
      check = 1;
    } // end else

  } // end while

  // check if still in red
  if ( red == 1 ) {
    printf( "\033[0m" );
  }
