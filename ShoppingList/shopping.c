/**
  @file shopping.c
  @author Summer Mims
  Project 4 Shopping Manager
*/

/**
  Defines main function and other functions not included in item or list.
  Responsible for reading user commands and performing them.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"

/**  Valid commands  */
#define CMD_LOAD "load"
#define CMD_SAVE "save"
#define CMD_ADD "add"
#define CMD_REMOVE "remove"
#define CMD_REPORT "report"
#define CMD_HELP "help"
#define CMD_QUIT "quit"

/** max length for command */
#define CMD_LIMIT 6
/** max length for file name */
#define FILE_LEN 30

/** exit status 0 */
#define EXIT_0 0

/**
  Helper function
  Print all in report
  @return true for all items
*/
static bool testAll( Item *it, void *arg ) {
  return true;
}

/**
  Helper function for report
  Print all from given store
  @return bool
    true if the item's store matches the given store name
    false otherwise
*/
static bool testStore( Item *it, void *arg ) {
  char *str = ( char * )arg;
  if ( strcmp( it->store, str ) == 0 ) {
    return true;
  }
  return false;
}

/**
  Helper function for report
  Print all with price greater than given price
  @return bool
    true if the item's price is greater than the given price
    false otherwise
*/
static bool testGreater( Item *it, void *arg ) {
  double *dp = ( double * )arg;
  if ( it->price > *dp ) {
    return true;
  }
  return false;
}

/**
  Helper function for report
  Print all with price less than given price
  @return bool
    true if the item's price is less than the given price
    false otherwise
*/
static bool testLess( Item *it, void *arg ) {
  double *dp = ( double * ) arg;
  if ( it->price < *dp ) {
    return true;
  }
  return false;
}

/**
  Read line of input from standard input or from a file
  Uses a resizable array to store arbitrary-sized string it reads
  @param *stream
    pointer to the input stream to read from
  @return char *
    pointer to dynamically allocated string
    returns NULL if there's no more input
*/
char *getLine( FILE *stream ){
  // initial capacity
  int capacity = CMD_LIMIT;
  char *buffer = (char *) malloc( capacity + 1 );

  // Number of characters we're currently storing.
  int len = 0;
  // variable to store each character read
  char c;
  while ( fscanf( stream, "%c", &c ) == 1 && c != '\n' ){

    // EOF, exit
    if ( c == EOF ) {
      return NULL;
    }
    // check buffer capacity
    if ( len >= capacity ){
      capacity *= 2;
      buffer = (char *)realloc( buffer, capacity );
    }
    // add c to buffer
    buffer[ len++ ] = c;
  }
  // if nothing was read, EOF
  if ( len == 0 ) {
    free( buffer );
    return NULL;
  }

  // null terminate
  if( len >= capacity ){
    capacity += 2;
    buffer = (char *)realloc( buffer, capacity );
  }
  buffer[len++]='\0';

  // return pointer to buffer with line of input
  return buffer;
}

/**
  Helper function to execute load command
  Command - load file.txt
      load item from a shoppingList that is stored in a file
      File has an item on a single line: Store price item name
        Store cannot have whitespace
        item name can include whitespace
        price is double
      as an item is read from file, add to the shopping list
  @param fileName
    the file to load items from
*/
void load( char fileName[ FILE_LEN ], ShoppingList *list ) {
  // initialize line number count
  int lineNum = 0;

  //open file stream
  FILE *fin = fin = fopen( fileName, "r" );

  // error opening file
  if ( !fin ) {
    printf( "Can't open file" );
    // return to prompt user for command
    return;
  }
  // pointer to store line in
  char *str;
  // read file until EOF
  // when EOF is reached, getLine returns NULL
  while ( ( str = getLine( fin ) ) ) {
    // increase line number after reading line
    lineNum ++;

    // attempt to create item
    Item *it = readItem( str );

    // error creating item
    if ( !it ){
      printf( "Invalid item, line %d\n", lineNum );
      // keep reading from file
    }
    else {
      // add item to shoppingList
      shoppingListAdd( list, it );
      // keep reading from file
    }
  }
  // close file
  fclose( fin );
}

/**
  Helper function to execute save command
  Command - save file.txt
    Save writes the current list to a file
    In order of ascending item id
  @param fileName
    the file to save the list to
*/
void save( char fileName[ FILE_LEN ], ShoppingList *list ) {
  //open file stream
  FILE *fp = fopen( fileName, "w" );

  // error opening file
  if ( !fp ) {
    printf( "Can't open file\n" );
    // return to prompt user for command
    return;
  }

  // write list to file using report function
  shoppingListReportFile( fp, list );
  // close file
  fclose( fp );
}

/**
  Helper function to execute help command
  Command - help
    Print report of valid commands
*/
void help(){
  printf( "%s\n", "load <file>" );
  printf( "%s\n", "save <file>" );
  printf( "%s\n", "add <store> <price> <name>" );
  printf( "%s\n", "remove <id>" );
  printf( "%s\n", "report" );
  printf( "%s\n", "report store <store>" );
  printf( "%s\n", "report less <price>" );
  printf( "%s\n", "report greater <price>" );
  printf( "%s\n", "help" );
  printf( "%s\n", "quit" );
}

/**
  Read command
  Helper function to read command and direct to execute
  Commands:
    load "file.txt"
    save "file.txt"
    add storeName price itemName
    remove itemID
    report; report store storeName; report less/greater price
    help
    quit
  @return bool
    return true is command if valid
    return false if command if invalid or error reading
*/
bool readCmd( ShoppingList *list ) {
  // read input from user from standard input
  char *str = getLine( stdin );

  // EOF, exit
  if ( str==NULL ){
    exit( EXIT_0 );
  }
  // print blank line before responding to input
  putchar( '\n' );

  // input not read, return false
  if ( !str ) {
    return false;
  }
  // string array to store command with room for null terminator
  char cmd[ CMD_LIMIT + 1 ];
  // parse first word to see if valid command
  int position = 0;
  int m = sscanf( str, "%6s%n", cmd, &position );

  // check if is valid command
  // if valid, call appropriate function and return true
  if ( m == 1 ) {

    // command is quit, exit with success
    if ( strcmp( cmd, CMD_QUIT ) == 0  ) {
      exit( EXIT_0 );
    }

    // command is help, call help and return true
    if ( strcmp( cmd, CMD_HELP ) == 0 ) {
      help();
      goto valid;
    }

    // command is load
    if ( strcmp( cmd, CMD_LOAD ) == 0 ) {
      char fileName[ FILE_LEN ];
      // parse second word to see if file name
      int n = sscanf( str, "load %s", fileName );
      // valid name, call load and return true
      if ( n == 1 ) {
        load( fileName, list );
        goto valid;
      }
    }

    // command is save
    if ( strcmp( cmd, CMD_SAVE ) == 0 ) {
      char fileName[ FILE_LEN ];
      // parse second word to see if file name
      int n = sscanf( str, "save %s", fileName );
      // valid name, call save and return true
      if ( n == 1 ) {
        save( fileName, list );
        goto valid;
      }
    }

    // command is remove
    // format: remove itemID
    // Invalid if argument is not int, or id not on the list
    if ( strcmp( cmd, CMD_REMOVE ) == 0 ) {
      int itemID;
      // parse second part to see if integer for item ID
      int n = sscanf( str, "remove %d", &itemID );
      // valid number, return bool from listRemove
      if ( n == 1 ) {
        if ( shoppingListRemove( list, &itemID ) ) {
          goto valid;;
        }
        else {
          goto invalid;
        }
      }
    }

    // command is add
    if ( strcmp( cmd, CMD_ADD ) == 0 ) {
      char maybeIt[ strlen( str ) + 1 - position ];
      strncpy( maybeIt, str + position, strlen( str ) - position );
      maybeIt[ strlen( str ) - position ] = '\0';

      // create new item
      Item *it = readItem( maybeIt );
      // valid command, add item and return true
      if ( !it ) {
        // item was invalid
        goto invalid;
      }
      else {
        // add to list
        shoppingListAdd( list, it );
        goto valid;

      }
    }

    // command is report
    if ( strcmp( cmd, CMD_REPORT ) == 0 ) {
      char storeName[ STORE_MAX +1 ];
      char extra[ STORE_MAX ];
      double price;
      // parse second part for aditional parameters
      // check command is report store storeName
      int n1 = sscanf( str, "report store %12s%s", storeName, extra );
      // check command is report less price
      int n2 = sscanf( str, "report less %lf", &price );
      // check command is report greater price
      int n3 = sscanf( str, "report greater %lf", &price );
      // check command is report
      int n4 = sscanf( str, "report %s", extra );

      // call report for full list
      // if n4 matches, means there was something after 'report'
      if ( n4 != 1 ) {
        // call full list report
        shoppingListReport( list, testAll, NULL );
        // valid command, return true
        goto valid;
      }
      // call report with store specified
      if ( n1 == 1 ) {
        //call report with store
        shoppingListReport( list, testStore, storeName );
        // valid command, return true
        goto valid;
      }
      // call report with prices less than
      if ( n2 == 1 ) {
        //call report with less
        shoppingListReport( list, testLess, &price );
        // valid command, return true
        goto valid;
      }
      // call report with prices greater than
      if ( n3 == 1 ) {
        //call report with greater
        shoppingListReport( list, testGreater, &price );
        // valid command, return true
        goto valid;
      }
      // invalid report command, return false
      goto invalid;
    } // end if report
  } // end if m==1

  // invalid, free memory and return false
  invalid:
    free( str );
    return false;
  // valid, free memory and return true
  valid:
    free( str );
    return true;
}

/**
  main function for shoppingList program, project 4
*/
int main()
{
  //create list
  ShoppingList *list = makeShoppingList();
  
  // store prompt number
  int pNum = 1;
  
  // get user input
  while ( pNum > 0 ) {
    // prompt for user command
    // begin prompt with "#> " where # starts at 1 and increases with each prompt
    printf( "%d> ", pNum );

    // input was invalid
    if ( !readCmd( list ) ) {
      printf( "Invalid command\n" );
    }

    // increment prompt number
    pNum ++;
  } // end while getCMD stdin
}
