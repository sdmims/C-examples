/**
  @file codepoints.c
  @author Summer Mims
  Project 5 UTF-8 Character Report
*/

/**
  Read and maintain list of codepoints.
  Each codepoints has a numeric code and string name
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "codepoints.h"

/** static length for cpt */
static int len;

/** global static variable for table of code points */
static struct CodePoint *cpt;

/**
  Helper function to sort table
  Comparison function for qsort
  @return positive if first is greater, negative if first is less, zero if equal
*/
int compareCP( const void *p, const void *q ) {
  // cast p, q to pointers to CodePoints
  struct CodePoint *x = ( struct CodePoint * ) p;
  struct CodePoint *y = ( struct CodePoint * ) q;

  // sort by val name
  if ( x->val > y->val ) {
    return +1;
  }
  else if ( y->val > x->val ) {
    return -1;
  }
  else {
    return 0;
  }
}

/**
  Open unicode text file.
  Read code point descriptions into data structure, code point table
*/
void loadTable() {
  // capacity of table
  int capacity = INIT_CP;
  len = 0;

  // initialize struct memory for table
  cpt = malloc( capacity * sizeof( struct CodePoint ) );

  // read from file
  FILE *fin = fopen( "unicode.txt", "rb" );

  // this shouldn't happen
  if ( !fin ) {
      fprintf( stderr, "Can't open unicode.txt\n" );
      freeTable();
      exit( EXIT_1 );
  }

  unsigned int val;
  char name[ NAME_MAX + 1 ];

  // read file till EOF
  char line[ LINE_MAX ];
  while ( fgets( line, sizeof( line ), fin ) ) {
    // parse each line of input till newline character
    sscanf( line, "%x %90[^\n]%*s", &val, name );

    // create new code point with values
    struct CodePoint c = { val };
    strcpy( c.name, name );

    // check memory size
    if ( len >= capacity ) {
      capacity *= TWO;
      cpt = ( struct CodePoint * ) realloc( cpt, sizeof( struct CodePoint ) * capacity );
    }

    // add code point to table
    cpt[ len ] = c;
    len++;
  }
  // after EOF, sort table
  qsort( ( void * )cpt, len, sizeof( struct CodePoint ), compareCP );
}

/**
  Free memory for the code point table
*/
void freeTable() {
  free( cpt );
}

/**
  Given the numeric value of a code point, print a line to standard output
  with the name and code (return true)..
  Otherwise return false
  @param int the numeric value of a code point
  @return bool return true if the code is in the code point table
*/
bool reportCode( int code ) {
  // local variables for binary search
  int min = 0;
  int max = len - 1;
  int mid;

  // binary search for code in table
  while ( min <= max ) {
    mid = ( min + max ) / TWO;
    if ( cpt[ mid ].val < code ) {
      min = mid + 1;
    }
    else if ( cpt[ mid ].val == code ) {
      printf( "%s\n", cpt[ mid ].name );
      return true;
    }
    else {
      max = mid - 1;
    }
  }

  // value not found in table
  return false;
}
