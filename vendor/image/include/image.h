/****************************************************************
 *
 * image.h
 *
 * Read and write PPM files. Only works for "raw" format.
 *
 ****************************************************************/

#ifndef IMAGE_H
#define IMAGE_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <ctype.h>

typedef struct { uint8_t r, g, b; } pixel_t;
typedef struct { pixel_t* pixels; size_t width, height; } bitmap_t;

void      alloc_bitmap  (bitmap_t* bitmap, size_t width, size_t height);        //alocate memory for an image
void      free_bitmap   (bitmap_t* bitmap);                                     //deallocate memory of the image
pixel_t*  pixel_bitmap  (bitmap_t* bitmap, size_t row, size_t col);             //get pixel at row and col
void      save_bitmap   (bitmap_t* bitmap, const char* path);                   //write image to ppm file
void      load_bitmap   (bitmap_t* bitmap, const char* path);                   //read image from ppm file

#endif /* IMAGE_H */
