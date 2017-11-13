/**
  @file list.c
  @author Summer Mims
  Project 4 Shopping Manager
*/

/**
  Defines the ShoppingList struct.
  Defines the functions for working with a shopping list.

  A shoppingList is an arbitray length list of items
  Each item will have a unique integer for Item ID, starting at 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"

/** number of items to start */
#define INIT_ITEMS 10

/**
  Dynamically allocate an instance of ShoppingList
  Initialize fields to empty
  Initialize with enough capacity to store a few items before needing to reallocate
  @ return ShoppingList *
    pointer to the ShoppingList instance
*/
ShoppingList *makeShoppingList() {
  // allocate for ShoppingList
  ShoppingList *list = ( ShoppingList * ) malloc( sizeof( ShoppingList ) );
  list->length = 0;
  list->capacity = INIT_ITEMS;
  // allocate for item list
  list->items  = ( Item ** ) malloc( list->capacity * sizeof( Item * ) );

  return list;
}

/**
  Free all dynamically allocated memory used by a ShoppingList
  Includes the shoppingList object, resizable array of Item pointers, item instances
  @param *list
    pointer to the ShoppingList instance to free
*/
void freeShoppingList( ShoppingList *list ){
  // free each item
  int j = 0;
  for ( j = 0; j < list->length; j++ ) {
    freeItem( list->items[j] );
  }

  // free list of items
  free( list->items );
  // free list
  free( list );
}

/**
  Add a given item to a given shoppinglist
  Resize internal array if needed
  @param *list
    pointer to the ShoppingList to add the item to
  @param *it
    pointer to the item to add to the ShoppingList
*/
void shoppingListAdd( ShoppingList *list, Item *it ){
  // check capacity
  if ( list->length >= list->capacity ) {
      list->capacity *= 2;
      list->items = ( Item ** ) realloc( list->items, sizeof( Item *) * list->capacity );
  }
  list->items[ list->length ] = it;
  list->length++;
}

/**
  Remove item from given shoppingList with the given id
  @param *list
    the ShoppingList to remove the item from
  @param *it
    pointer to the item to remove
  @return bool
    return true is item is removed successfully
    return false if item is not found
*/
bool shoppingListRemove( ShoppingList *list, int *id ) {
  int j = 0;
  for ( j = 0; j < list->length; j++ ) {
    if ( list->items[ j ]->id  == *id ) {
      // shift all items left
      for ( int k = j; k < list->length - 1; k++ ) {
        list->items[ k ] = list->items[ k + 1 ];
      }
      // decrease length
      list->length--;
      return true;
    }
  }
  // match not found, return false
  return false;
}

/**
  Goes through a shoppingList
  Report selected items
  Computed their total cost

  Item Format
    ItemID in 4 character field, right justified
    Space
    StoreName in 12 character field, left justified
    Space
    Price in 7 character field, two fractional digits
    Space
    ItemName till end of line
  Total price is printed aligned with other prices, as the last line

  If no items, still total to zero but print no items
*/
void shoppingListReport( ShoppingList *list, bool test( Item *it, void *arg ), void *arg )
{
  double total = 0;

  for ( int j = 0; j < list->length; j++ ) {

    // if item is true, report and add to total
    if ( test( list->items[ j ], arg ) ) {
      printf( "%4d %-12s %7.2lf %s\n", list->items[ j ]->id, list->items[ j ]->store, \
        list->items[ j ]->price, list->items[ j ]->name );
      total+=list->items[ j ]->price;
    }
  }
  // print 18 spaces for alignment of total
  for ( int i = 0; i < 18; i++ ) {
    printf( "%c", ' ' );
  }
  printf("%7.2lf\n", total );
}

/**
  Goes through a shoppingList
  Report selected items to file
  Computed their total cost

  Item Format
    ItemID in 4 character field, right justified
    Space
    StoreName in 12 character field, left justified
    Space
    Price in 7 character field, two fractional digits
    Space
    ItemName till end of line
  Total price is printed aligned with other prices, as the last line

  If no items, still total to zero but print no items
*/
void shoppingListReportFile( FILE *stream, ShoppingList *list )
{
  for ( int j = 0; j < list->length; j++ ) {
    fprintf( stream, "%s %.2lf %s\n", list->items[ j ]->store, \
      list->items[ j ]->price, list->items[ j ]->name );
  }
}
