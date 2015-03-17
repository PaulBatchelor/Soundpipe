#include <stdlib.h>
#include <stdio.h>
#include "soundpipe.h"

void write_noise(sp_data *data, void *ud) {
    data->out = (rand() % 1000) / 1000.0;
    data->out = (data->out * 2) - 1;
}
int main() {
    srand(time(NULL));
    sp_data *sp;
    sp_create(&sp);
    sp_process(sp, NULL, write_noise);
    sp_destroy(&sp);
    return 0;
}
