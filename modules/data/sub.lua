sptbl["sub"] = {

    files = {
        module = "sub.c",
        header = "sub.h",
        example = "ex_sub.c",
    },

    func = {
        create = "sp_sub_create",
        destroy = "sp_sub_destroy",
        init = "sp_sub_init",
        compute = "sp_sub_compute",
    },

    modtype = "module",

    description = [[A difference of two input signals.]],

    ninputs = 2,
    noutputs = 1,

    params = {
    },

    inputs = {
        {
            name = "input1",
            description = "The first input which will be subtracted from by the second input."
        },
        {
            name = "input2",
            description = "The second input which will be subtracted from the first input."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Output as difference of input signals."
        },
    }

}
