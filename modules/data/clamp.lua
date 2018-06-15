sptbl["clamp"] = {

    files = {
        module = "clamp.c",
        header = "clamp.h",
        example = "ex_clamp.c",
    },

    func = {
        create = "sp_clamp_create",
        destroy = "sp_clamp_destroy",
        init = "sp_clamp_init",
        compute = "sp_clamp_compute",
    },

    params = {
        optional = {
            {
                name = "min",
                type = "SPFLOAT",
                description = "Minimum value.",
                default = 0
            },
            {
                name = "max",
                type = "SPFLOAT",
                description ="Maximum value.",
                default = 1
            },
        }
    },

    modtype = "module",

    description = [[Performs a clamp operation on an input signal.

This module performs what is known as a "clamp" operation, which sets the
bounds of a signal in between a minimum and a maximum value. Anything exceeding
the bounds in either direction will be set to the closest valid value. In
other words: if x is less than minimum, set x to the minimum;
if x is greater than the maximum, set x to be the maximum.
]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "input",
            description = "Input audio signal."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Output audio signal."
        },
    }

}
