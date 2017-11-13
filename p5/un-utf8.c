/**
  @file un-utf8.c
  @author Summer Mims
  Project 5 UTF-8 Character Report
*/

/**
  Main component.
  Open and read from input file
  Detect errors
  Use codepoints component to print names of valid components
  Input:  Read encoded UTF-8
  Output: Print out character name
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "codepoints.h"

/** mask for FF */
#define MASK_FF 0xFF

/** mask for F0 */
#define MASK_F0 0xF0

/** mask for 0F */
#define MASK_0F 0x0F

/** mask for 80 */
#define MASK_80 0x80

/** mask for 08 */
#define MASK_08 0x08

/** mask for 0F */
#define MASK_3F 0x3F

/** mask for 0F */
#define MASK_1F 0x1F

/** mask for 07 */
#define MASK_07 0x07

/** mask for E0 */
#define MASK_E0 0xE0

/** mask for 10 */
#define MASK_10 0x10

/** mask for 20 */
#define MASK_20 0x20

/** mask for C0 */
#define MASK_C0 0xC0

/**
  Main function for program
  User provides input text file as command argument
*/
int main( int argc, char *argv[] )
{
  FILE *fin = NULL;

  // check for command line arguments
  if ( argc == 2 ) {
    fin = fopen( argv[ 1 ], "rb" );

    // error opening file
    if ( !fin ) {
      fprintf( stderr, "Can't open file: %s\n", argv[ 1 ] );
      fprintf( stderr, "usage: un-utf8 <input-file>\n");
      exit( EXIT_1 );
    }

    // load code points table config
    loadTable();

    // variable for byte number
    int byteNum = 0;
    // variable to increment byteNum by
    int incNum = 0;
    // variable to store character input
    char c;

    // read in a single character
    while ( ( c = fgetc( fin ) ) != EOF ) {
      // increment byteNum by 1 byte
      incNum = 1;
      // convert c to unsigned
      unsigned int code = c;
      // var to store second, third, and fourth bytes
      char c2;
      char c3;
      char c4;

      // valid 1 byte must have leading 0 - 0xxx xxxx
      if ( ( code & MASK_80 ) != MASK_80 ) {
        goto report;
      }

      // valid 2 byte must have leading 110 - 110x xxxx
      else if ( ( ( code & MASK_C0 ) == MASK_C0 ) && ( ( code & MASK_20 ) != MASK_20 ) ) {
        // get second byte
        c2 = fgetc( fin );
        // increment byte number by 2 bytes
        incNum = 2;
        if ( c2 == EOF ) {
          goto incompleteByte;
        }
        else if ( ( c2 & MASK_80 ) == MASK_80 ) {
          // mask original byte with 1F and shift left 6 places
          // mask second byte with 3F and inclusive OR
          code = ( ( code & MASK_1F ) << 6 ) | ( c2 & MASK_3F );
          // check for overlong, if first 5 bits were not needed
          if ( ( ( code >> 7 ) & MASK_FF ) ==  0 ) {
            goto overlongError;
          }
        }
        else {
          // invalid byte at byte 2
          code = c2;
          goto invalidByte;
        }
      }

      // valid 3 byte must have leading 1110 - 1110 xxxx
      else if ( ( ( code & MASK_E0 ) == MASK_E0 ) && ( ( code & MASK_10 ) != MASK_10 ) ) {
        // get second byte
        c2 = fgetc( fin );
        // increment byte number by 2 bytes
        incNum = 2;
        if ( c2 == EOF ) {
          goto incompleteByte;
        }
        else if ( ( c2 & MASK_80 ) == MASK_80 ) {
          // get third byte
          c3 =  fgetc( fin );
          // increment byte number by 3 bytes
          incNum = 3;
          if ( c3 == EOF ) {
            goto incompleteByte;
          }
          else if ( ( c3 & MASK_80 ) == MASK_80 ) {
            // mask original byte with 0F and shift left 12 places
            // mask second byte with 3F and shift left 6 places and inclusive OR
            // mask third byte with 3F and inclusive OR
            code = ( ( code & MASK_0F ) << 12 ) | ( ( c2 & MASK_3F ) << 6 ) | ( c3 & MASK_3F );
            // check for overlong, if first 5 bits were not needed
            if ( ( ( code >> 11 ) & MASK_FF ) == 0 ) {
              goto overlongError;
            }
          }
          else {
            // invalid byte at byte 3
            code = c3;
            goto invalidByte;
          }
        }
        else {
          // invalid byte at byte 2
          code = c2;
          goto invalidByte;
        }
      }

      // valid 4 byte must have leading 11110 - 1111 0xxx
      else if ( ( ( code & MASK_F0 ) == MASK_F0 ) && ( ( code & MASK_08 ) != MASK_08 ) ) {
        // get second byte
        c2 = fgetc( fin );
        // increment byte number by 2 bytes
        incNum = 2;
        if ( c2 == EOF ) {
          goto incompleteByte;
        }
        else if ( ( c2 & MASK_80 ) == MASK_80 ) {
          // get third byte
          c3 =  fgetc( fin );
          // increment byte number by 3 bytes
          incNum = 3;
          if ( c3 == EOF ) {
            goto incompleteByte;
          }
          else if ( ( c3 & MASK_80 ) == MASK_80 ) {
            // get fourth byte
            c4 = fgetc( fin );
            // increment byte number by 3 bytes
            incNum = 4;
            if ( c4 == EOF ) {
              goto incompleteByte;
            }
            else if ( ( c4 & MASK_80 ) == MASK_80 ) {
              // mask original byte with 07 and shift left 18 places
              // mask second byte with 3F and shift left 12 places and inclusive OR
              // mask third byte with 3F and shift left 6 places and inclusive OR
              // mask fourth byte with 3F
              code = ( ( code & MASK_07 ) << 18 ) | ( ( c2 & MASK_3F ) << 12 ) \
                     | ( ( c3 & MASK_3F ) << 6 ) | ( c4 & MASK_3F );
              // check for overlong, if first 5 bits were not needed
              if ( ( ( code >> 16 ) & MASK_FF ) == 0) {
                goto overlongError;
              }
            }
            else {
              // invalid byte at byte 4
              code = c4;
              goto invalidByte;
            }
          }
          else {
            // invalid byte at byte 3
            code = c3;
            goto invalidByte;
          }
        }
        else {
          // invalid byte at byte 2
          code = c2;
          goto invalidByte;
        }
      }
      else {
        // invalid byte at byte 1
        goto invalidByte;
      }

      // good input
      report:
        // find corresponding code point in cpt table
        if ( !reportCode( code ) ) {
          // description not provided
          fprintf( stderr, "Unknown code: 0x%X at %d\n", code, byteNum );
        }
        goto notReport;

      // possible errors
      invalidByte:
        // invalid byte values
        fprintf( stderr, "Invalid byte: 0x%X at %d\n", \
                 (unsigned char) code, ( byteNum + incNum - 1) );
        goto notReport;
      incompleteByte:
        // incomplete code - reaches EOF before finishing multi-byte code
        fprintf( stderr, "Incomplete code at %d\n", byteNum );
        goto notReport;
      overlongError:
        // overlong encoding error
        fprintf( stderr, "Invalid encoding: 0x%X at %d\n", code, byteNum );
        goto notReport;

      notReport:
        // increment byte number
        byteNum += incNum;
    } // end while

    // close file
    fclose( fin );
    // free memory
    freeTable();
    // exit with success
    exit( EXIT_0 );
  } // end if arg==2

  // incorrect number of command line parameters
  else {
    fprintf( stderr, "usage: un-utf8 <input-file>\n");
    exit( EXIT_1 );
  }
}
