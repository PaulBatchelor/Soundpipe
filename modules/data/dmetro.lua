sptbl["dmetro"] = {

    files = {
        module = "dmetro.c",
        header = "dmetro.h",
        example = "ex_dmetro.c",
    },

    func = {
        create = "sp_dmetro_create",
        destroy = "sp_dmetro_destroy",
        init = "sp_dmetro_init",
        compute = "sp_dmetro_compute",
    },

    params = {
        optional = {
            {
                name = "time",
                type = "SPFLOAT",
                description ="Time between triggers (in seconds). This will update at the start of each trigger.",
                default = 1.0
            },
        }
    },

    modtype = "module",

    description = [[Delta Metro

    Produce a set of triggers spaced apart by time.

An implementation note: while dmetro does indeed use sample
precision, it will intentionally add 1 sample to the
duration time as a way to avoid divide-by-zero errors. A
dmetro of one second will really be one second and 1 sample.
For most musical purposes, this is negligible. For more
scientific purposes, this could cause problems, and it is
recommended to find or build another module.]],

    ninputs = 0,
    noutputs = 1,

    inputs = {
    },

    outputs = {
        {
            name = "out",
            description = "Trigger output."
        },
    }

}
