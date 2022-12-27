#pragma once 
#include <stdio.h> 
#include <stdlib.h>

#include "image.h"
#include "types.h"



//naive version
void stencil_v1(f64 * tab, f64 * tab2, u64 size_x, u64 size_y);
