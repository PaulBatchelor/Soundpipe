sptbl["brown"] = {

    files = {
        module = "brown.c",
        header = "brown.h",
        example = "ex_brown.c",
    },

    func = {
        create = "sp_brown_create",
        destroy = "sp_brown_destroy",
        init = "sp_brown_init",
        compute = "sp_brown_compute",
    },

    params = {
    },

    modtype = "module",

    description = [[Brownian noise generator.
]],

    ninputs = 0,
    noutputs = 1,

    inputs = {
    },

    outputs = {
        {
            name = "out",
            description = "Brownian noise output."
        },
    }

}
