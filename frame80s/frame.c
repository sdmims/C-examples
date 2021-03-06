/**
  @file frame.c
  @author Summer Mims
  Project 2 70s Style Soft Image Frame
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "frame.h"

/**
  Exit status 101
*/
#define EXIT_101 101
/**
  Exit status 100
*/
#define EXIT_100 100
/**
  Exit status 102
*/
#define EXIT_102 102
/**
  pixel offset for coordinates
*/
#define PIXEL_OFFSET 0.5
/**
  maximum number for a pixel
*/
#define PIXEL_MAX 255
/**
  minimum number for a pixel
*/
#define PIXEL_MIN 0

/**
  global variable for frame radius
*/
double frameRadius;

/**
  global variable for distance to corners
*/
double cornerDistance;

/**
  starting point
  @return exit status
*/

/**
  Function called at start of reading input image.
  Checks the first two characters to ensure the input file is the right type.
  If not, it exits the program with exit status 100.
*/
void checkFileType()
{
  int fileAlpha;
  int fileNumeric;

  if ( ( fileAlpha = getchar() ) != 'P' ){
    // return exit status of 100
    exit( EXIT_100 );
  }

  if ( ( fileNumeric = getchar() ) != '3' ){
    // return exit status of 100
    exit( EXIT_100 );
  }

  // print output file type
  printf( "%c%c\n", fileAlpha, fileNumeric );
}

/**
  This is a helper function to print a pixel formatted to three columns.
*/
void printPixel( int pixel )
{
  // print formatted to three character width
  if ( pixel < 10 ){
    printf( "  %d ", pixel );
  }
  else if ( pixel < 100 ){
    printf( " %d ", pixel );
  }
  else {
    printf( "%d ", pixel);
  }
}

/**
  This function computes the new, weighted combination of the RGB components.
  It rounds the result to the nearest integer and prints it out formatted.
*/
void shade( int color, int borderColor, double dist )
{
  // weight value
  double weight = ( dist-frameRadius - PIXEL_OFFSET ) /
                  ( cornerDistance - frameRadius - PIXEL_OFFSET );

  // value of new mixed pixel
  int newPixel = round( color * ( 1 - weight ) + borderColor * weight );
  printPixel( newPixel );
}

/**
  This program reads and writes images in a simple,
  uncompressed format, PPM.
  The program will add a frame to the image.
  Each image format starts with a 3-line header
  P3 = plain PPM format
  Next line is the image size
  Last line is intesity for red, green, and blue components.
*/
int main()
{
  // check file type
  checkFileType();

  // Second line must be at least 2 x 2.
  int width;
  int height;
  int readIn = scanf( "%d%d", &width, &height );
  if ( width < 2 || height < 2 || readIn != 2){
    // return exit status of 101
    exit( EXIT_101 );
  }

  // if size is valid, can determine frame radius and corner distance
  if ( width < height ){
    frameRadius = (double) ( width - 2 ) / 2;
  }
  else {
   frameRadius = (double) ( height - 2 ) / 2;
  }
  double centerY = (double) height / 2;
  double centerX = (double) width / 2;

  cornerDistance = sqrt( ( height - PIXEL_OFFSET - centerY ) *
                       ( height - PIXEL_OFFSET -   centerY ) +
                       ( width - PIXEL_OFFSET - centerX ) *
                       ( width - PIXEL_OFFSET - centerX ) );

  // Third line must be between 0 and 255
  int maximum = 0;
  scanf( "%d", &maximum );

  if ( maximum < PIXEL_MIN || maximum > PIXEL_MAX ){
    // return exit status of 101
    exit( EXIT_101 );
  }

  // print headers
  printf( "%d %d\n%d\n", width, height, maximum );
  
  // store red pixel
  int redPixel;
  // store green pixel
  int greenPixel;
  // store blue pixel
  int bluePixel;
  // store distance for each pixel
  double dist;

  for ( double i = PIXEL_OFFSET; i < height; i ++ ){
    for ( double j = PIXEL_OFFSET; j < width; j ++ ){
      int readIn = scanf("%d%d%d", &redPixel, &greenPixel, &bluePixel );

      // check three pixels read
      if ( readIn != 3 ){
        exit( EXIT_102 );
      }
      // check each pixel is valid
      if ( redPixel < PIXEL_MIN || redPixel > PIXEL_MAX ){
        exit( EXIT_102 );
      }
      if ( greenPixel < PIXEL_MIN || greenPixel > PIXEL_MAX ){
        exit( EXIT_102 );
      }
      if ( bluePixel < PIXEL_MIN || bluePixel > PIXEL_MAX ){
        exit( EXIT_102 );
      }

      // calculate distance from center
      dist = sqrt( ( i - centerY ) * ( i - centerY ) +
                 ( j - centerX ) * ( j - centerX ) );

      // if the distance is less than or equal to frame radius
      // do nothing
      if ( ( dist - PIXEL_OFFSET ) <= frameRadius ){
        printPixel( redPixel );
        printPixel( greenPixel );
        printPixel( bluePixel );
      }
      else {
        shade( redPixel, FRAME_RED, dist );
        shade( greenPixel, FRAME_GREEN, dist );
        shade( bluePixel, FRAME_BLUE, dist );
      }
    } // for j
    // begin new row
    putchar( '\n' );
  } // for i
} // end main
