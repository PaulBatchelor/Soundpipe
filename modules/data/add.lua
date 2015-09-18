sptbl["add"] = {

    files = {
        module = "add.c",
        header = "add.h",
        example = "ex_add.c",
    },

    func = {
        create = "sp_add_create",
        destroy = "sp_add_destroy",
        init = "sp_add_init",
        compute = "sp_add_compute",
    },

    modtype = "module",

    description = [[A sum of two input signals]],

    ninputs = 2,
    noutputs = 1,

    params = {
    },

    inputs = {
        {
            name = "input1",
            description = "First input to be added."
        },
        {
            name = "input2",
            description = "Second input to be added."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Output the sum of the input signals."
        },
    }

}
