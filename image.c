#include <stdlib.h>
#include <stdio.h>

#include "image.h"

int write_ppm(char * filename, f64 * tab_r, f64 * tab_g,  f64 * tab_b , u64 dimx, u64 dimy)
{
    // const int dimx = 800, dimy = 800;
    int i, j;
    FILE *fp = fopen(filename, "wb"); /* b - binary mode */
    (void) fprintf(fp, "P6\n%d %d\n255\n", (int)dimx, (int)dimy);
    for (j = 0; j < dimy; ++j) {
        for (i = 0; i < dimx; ++i) {
            int index = j * dimx + i;
            static unsigned char color[3];
            color[0] = tab_r[index];  /* red */
            color[1] = tab_g[index];  /* green */
            color[2] = tab_b[index];  /* blue */
            (void) fwrite(color, 1, 3, fp);
        }
    }
    (void) fclose(fp);
    return EXIT_SUCCESS;
}

int load_ppm_data(PPMImage * img, f64 * tab_r, f64 * tab_g, f64 * tab_b , u64 * dimx, u64 * dimy){
    *dimx = img->x; 
    *dimy = img->y;
    
    printf("dimx : %d\n", (int)*dimx);
    printf("dimy : %d\n", (int)*dimy);
    for( u64 y = 0; y < *dimy; y++){
        for( u64 x = 0; x < *dimx; x++){
            u64 index = y * (*dimx) + x;
            tab_r[index] = (float) img->data[index].red;
            tab_g[index] = (float) img->data[index].green;
            tab_b[index] = (float) img->data[index].blue;

        }
    }
    return EXIT_SUCCESS;
}

PPMImage *read_ppm(const char *filename)
{
         char buff[16];
         PPMImage *img;
         FILE *fp;
         int c, rgb_comp_color;
         //open PPM file for reading
         fp = fopen(filename, "rb");
         if (!fp) {
              fprintf(stderr, "Unable to open file '%s'\n", filename);
              exit(1);
         }

         //read image format
         if (!fgets(buff, sizeof(buff), fp)) {
              perror(filename);
              exit(1);
         }

    //check the image format
    if (buff[0] != 'P' || buff[1] != '6') {
         fprintf(stderr, "Invalid image format (must be 'P6')\n");
         exit(1);
    }

    //alloc memory form image
    img = (PPMImage *)malloc(sizeof(PPMImage));
    if (!img) {
         fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
    }

    //check for comments
    c = getc(fp);
    while (c == '#') {
    while (getc(fp) != '\n') {};
         c = getc(fp);
    }

    ungetc(c, fp);
    //read image size information
    if (fscanf(fp, "%d %d", &img->x, &img->y) != 2) {
         fprintf(stderr, "Invalid image size (error loading '%s')\n", filename);
         exit(1);
    }

    //read rgb component
    if (fscanf(fp, "%d", &rgb_comp_color) != 1) {
         fprintf(stderr, "Invalid rgb component (error loading '%s')\n", filename);
         exit(1);
    }

    //check rgb component depth
    if (rgb_comp_color!= RGB_COMPONENT_COLOR) {
         fprintf(stderr, "'%s' does not have 8-bits components\n", filename);
         exit(1);
    }

    while (fgetc(fp) != '\n') ;
    
    //memory allocation for pixel data
    img->data = (PPMPixel*)malloc(img->x * img->y * sizeof(PPMPixel));

    if (!img) {
         fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
    }

    //read pixel data from file
    if (fread(img->data, 3 * img->x, img->y, fp) != img->y) {
         fprintf(stderr, "Error loading image '%s'\n", filename);
         exit(1);
    }

    fclose(fp);
    return img;
}

