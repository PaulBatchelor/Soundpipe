sptbl["div"] = {

    files = {
        module = "div.c",
        header = "div.h",
        example = "ex_div.c",
    },

    func = {
        create = "sp_div_create",
        destroy = "sp_div_destroy",
        init = "sp_div_init",
        compute = "sp_div_compute",
    },

    modtype = "module",

    description = [[A division of two input signals]],

    ninputs = 2,
    noutputs = 1,

    params = {
    },

    inputs = {
        {
            name = "input1",
            description = "The first input which will be divided by the second input."
        },
        {
            name = "input2",
            description = "The second input which will be divided the first input."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Output as division of input signals"
        },
    }

}
