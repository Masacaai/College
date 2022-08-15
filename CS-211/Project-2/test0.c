
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "prog3.h"

int main(){

    char **m;

    m = alloc_square_mtx(8);

    pop_mtx_alpha(m, 8);

    floating_boulders(m, 8, 20);

    display_mtx(m, 8);

    free_square_mtx(m, 8);

    return 0;
}
