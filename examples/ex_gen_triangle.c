#include <stdio.h>
#include "soundpipe.h"

int main() {
    sp_data *sp;
    sp_create(&sp);
    sp_ftbl *ft;
    sp_ftbl_create(sp, &ft, 4096);
    sp_gen_triangle(sp, ft);
    int i;
    FILE *fp= fopen("plot.dat", "w");
    for(i = 0; i < ft->size; i++) {
        fprintf(fp, "%d %g\n", i, ft->tbl[i]);
    }
    printf( "%d plot points written to plot.dat.\n", ft->size); 
    printf("Run write_plot.sh to see the result.\n");
    fclose(fp);
    sp_ftbl_destroy(&ft);
    sp_destroy(&sp);
    return 0;
}
