/**
  @file item.h
  @author Summer Mims
  Project 4 Shopping Manager
*/

/**
  Defines the item struct
  Defines the functions for working with the items on the shopping list.
*/

/** Maximum length of a store name */
#define STORE_MAX 12

/** Struct Representation for an item to be purchased. */
typedef struct {
  /** Unique ID for this particular item.  */
  int id;
  
  /** Store where we're supposed to buy the item.  */
  char store[ STORE_MAX + 1 ];
  
  /** Price of this item in dollars (but you might normally store this
      as an integer number of cents). */
  double price;
  
  /** Name of this item.  Pointer to a string of arbitrary length. */
  char *name;
} Item;

/**  Function prototypes */

/**
  Create a new, dynamically allocated item based on str.
  @param str
    contains store for item, price, item name
  @return Item *
    pointer to the new item if function reading is succesful
  @return NULL
    if str is not correct format
*/
Item *readItem( char *str );

/**
  Free the memory of given item
  Frees the item sruct and the memory for item's name
  @param it
    the item to free
*/
void freeItem( Item *it );
