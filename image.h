#pragma once

#include <stdlib.h>
#include <stdio.h>


#include "types.h"

typedef struct {
     unsigned char red,green,blue;
} PPMPixel;

typedef struct {
     int x, y;
     PPMPixel *data;
} PPMImage;

#define CREATOR "RPFELGUEIRAS"
#define RGB_COMPONENT_COLOR 255



int write_ppm(char * filename, f64 * tab_r, f64 * tab_g,  f64 * tab_b , u64 dimx, u64 dimy);
int load_ppm_data(PPMImage * img, f64 * tab_r, f64 * tab_g, f64 * tab_b , u64 * dimx, u64 * dimy);
// int read_ppm(char * filename, f64 * tab_r, f64 * tab_g,  f64 * tab_b , u64 dimx, u64 dimy);
PPMImage *read_ppm(const char *filename);

