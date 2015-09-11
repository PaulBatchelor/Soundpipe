sptbl["inverse"] = {

    files = {
        module = "inverse.c",
        header = "inverse.h",
        example = "ex_inverse.c",
    },

    func = {
        create = "sp_inverse_create",
        destroy = "sp_inverse_destroy",
        init = "sp_inverse_init",
        compute = "sp_inverse_compute",
    },

    params = {
    },

    modtype = "module",

    description = [[Inverse of the input signal.]],

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
            description = "Output signal is the inverted input."
        },
    }

}
