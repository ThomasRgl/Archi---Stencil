#include <stdio.h> 
#include <stdlib.h>

#include "image.h"
#include "types.h"


void stencil(f64 * tab, f64 * tab2, u64 size_x, u64 size_y){
    
    for( u64 y = 1; y < size_y - 1; y++){
        for( u64 x = 1; x < size_x - 1; x++){
            u64 index = y * size_x + x;
            f64 acc = 0.0f;
            acc += tab[index + size_y + 1]; 
            acc += tab[index + size_y + 0]; 
            acc += tab[index + size_y - 1]; 

            acc += tab[index + 0      + 1]; 
            acc += tab[index + 0      + 0]; 
            acc += tab[index + 0      - 1]; 

            acc += tab[index - size_y + 1]; 
            acc += tab[index - size_y + 0]; 
            acc += tab[index - size_y - 1]; 

            tab2[index] = acc/9;

        }
    }
}

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
