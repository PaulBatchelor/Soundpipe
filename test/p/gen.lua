name = arg[1]
sptbl = {}

dofile ("../../sp_dict.lua")

header=[[
#include <stdlib.h>
#include <stdio.h>
#include "soundpipe.h"
#include "config.h"

int main() {
    srand(time(NULL));
    sp_data *sp;
    sp_create(&sp);
    sp->sr = SR;
    sp->len = sp->sr * LEN;
    uint32_t t;
    SPFLOAT in = 0, out = 0;
]]

compute=[[
    sp_FOO *unit;
    sp_FOO_create(&unit);

    sp_FOO_init(sp, unit);

    for(t = 0; t < sp->len; t++) {
        sp_FOO_compute(sp, unit, &in, &out);
    }

    sp_FOO_destroy(&unit);
]]


footer=[[
    sp_destroy(&sp);
    return 0;
}
]]

compute = string.gsub(compute, "FOO", name)

print(header)
print(compute)
print(footer)
