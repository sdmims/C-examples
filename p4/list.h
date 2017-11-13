/**
  @file list.h
  @author Summer Mims
  Project 4 Shopping Manager
*/
#include "item.h"

/**
  Defines the ShoppingList struct.
  Defines the functions for working with a shopping list.
*/

/** Representation for a shopping list, an arbitrary-length list of Items. */
typedef struct {
  /** Resizable array of pointers to Items. */
  Item **items;
  
  /** Current number of items on the list. */
  int length;
  
  /** Current capacity of the list, how many pointers we have room for. */
  int capacity;
} ShoppingList;

/** Function prototypes */

/**
  Dynamically allocate an instance of ShoppingList
  Initialize fields to empty
  Initialize with enough capacity to store a few items before needing to reallocate
  @ return ShoppingList *
    pointer to the ShoppingList instance
*/
ShoppingList *makeShoppingList();

/**
  Free all dynamically allocated memory used by a ShoppingList
  Includes the shoppingList object, resizable array of Item pointers, item instances
  @param *list
    pointer to the ShoppingList instance to free
*/
void freeShoppingList( ShoppingList *list );

/**
  Add a given item to a given shoppinglist
  Resize internal array if needed
  @param *list
    pointer to the ShoppingList to add the item to
  @param *it
    pointer to the item to add to the ShoppingList
*/
void shoppingListAdd( ShoppingList *list, Item *it );

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
bool shoppingListRemove( ShoppingList *list, int *id );

/**
  Goes through a shoppingList
  Report selected items
  Computed their total cost
*/
void shoppingListReport( ShoppingList *list, bool test( Item *it, void *arg ), void *arg );

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
void shoppingListReportFile( FILE *stream, ShoppingList *list );
