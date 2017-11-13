/**
  @file item.c
  @author Summer Mims
  Project 4 Shopping Manager
*/

/**
  Defines the item struct
  Defines the functions for working with the items on the shopping list.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "item.h"

/**
  Create a new, dynamically allocated item based on str.
  @param str
    contains store for item, price, item name
  @return Item *
    pointer to the new item if function reading is succesful
  @return NULL
    if str is not correct format
*/
Item *readItem( char *str ){
  /** static itemId number */
  static int itemId;

  // allocate for item
  Item *i = ( Item * ) malloc( sizeof( Item ) );

  // parse item from str
  int position = 0;
  int n = sscanf( str, "%12s%lf %n", i->store, &(i->price), &position );

  // handle long names by allocating needed space from strlen
  if ( n == 2 ) {
    char nm[ strlen( str ) + 1 - position ];
    strncpy( nm, str + position, strlen( str ) - position );
    nm[ strlen( str ) - position ] = '\0';
    i->name = ( char * ) malloc( ( strlen( nm ) + 1 ) * sizeof( char )  );
    strcpy( i->name, nm );
    // create unique item
    itemId++;
    i->id = itemId;
    return i;
  }
  // item is not valid; free memory and return null
  free( i );
  return NULL;
}

/**
  Free the memory of given item; the item sruct and the memory for item's name
  @param it
    the item to free
*/
void freeItem( Item *it ){
  // free name space
  free( it->name );
  // free item space
  free( it );
}
