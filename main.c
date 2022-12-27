#include <stdio.h> 
#include <stdlib.h>

#include "image.h"
#include "types.h"
#include "stencil.h"

#define stencil stencil_v1

int main(){
    PPMImage * img = read_ppm("img/Lena.ppm");
    
    f64 * tab_r = aligned_alloc(64, img->x * img->y * sizeof(f64) );
    f64 * tab_g = aligned_alloc(64, img->x * img->y * sizeof(f64) );
    f64 * tab_b = aligned_alloc(64, img->x * img->y * sizeof(f64) );
    
    f64 * tab2_r = aligned_alloc(64, img->x * img->y * sizeof(f64) );
    f64 * tab2_g = aligned_alloc(64, img->x * img->y * sizeof(f64) );
    f64 * tab2_b = aligned_alloc(64, img->x * img->y * sizeof(f64) );
  
    u64 dimx, dimy;

    load_ppm_data(img, tab_r, tab_g, tab_b , &dimx, &dimy);

    //stencil

    for(int i = 0; i < 100; i++){
        stencil(tab_r,tab2_r, dimx, dimy);
        stencil(tab_g,tab2_g, dimx, dimy);
        stencil(tab_b,tab2_b, dimx, dimy);
    
        stencil(tab2_r,tab_r, dimx, dimy);
        stencil(tab2_g,tab_g, dimx, dimy);
        stencil(tab2_b,tab_b, dimx, dimy);
    }

    stencil(tab_r,tab2_r, dimx, dimy);
    stencil(tab_g,tab2_g, dimx, dimy);
    stencil(tab_b,tab2_b, dimx, dimy);



    write_ppm("out/Lenaflou.ppm", tab2_r, tab2_g,  tab2_b , dimx, dimy);
    
}
