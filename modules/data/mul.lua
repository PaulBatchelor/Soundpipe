sptbl["mul"] = {

    files = {
        module = "mul.c",
        header = "mul.h",
        example = "ex_mul.c",
    },

    func = {
        create = "sp_mul_create",
        destroy = "sp_mul_destroy",
        init = "sp_mul_init",
        compute = "sp_mul_compute",
    },

    modtype = "module",

    description = [[A multiplication of two input signals.]],

    ninputs = 2,
    noutputs = 1,

    params = {
    },

    inputs = {
        {
            name = "input1",
            description = "The first input to be multiplied."
        },
        {
            name = "input2",
            description = "The second input to be multiplied."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Multiplication of input signals"
        },
    }

}
