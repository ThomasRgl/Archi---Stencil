
#include "stencil.h"


void stencil_v1(f64 * tab, f64 * tab2, u64 size_x, u64 size_y){
    
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

