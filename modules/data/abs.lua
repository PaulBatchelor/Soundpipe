sptbl["abs"] = {

    files = {
        module = "abs.c",
        header = "abs.h",
        example = "ex_abs.c",
    },

    func = {
        create = "sp_abs_create",
        destroy = "sp_abs_destroy",
        init = "sp_abs_init",
        compute = "sp_abs_compute",
    },

    params = {
    },

    modtype = "module",

    description = [[Absolute value of the input signal.]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "input",
            description = "Input signal."
        },
    },

    outputs = {
        {
            name = "out",
            description = "All postiive output signal."
        },
    }

}
