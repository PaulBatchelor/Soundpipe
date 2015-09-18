sptbl["decimator"] = {

    files = {
        module = "decimator.c",
        header = "decimator.h",
        example = "ex_decimator.c",
    },

    func = {
        create = "sp_decimator_create",
        destroy = "sp_decimator_destroy",
        init = "sp_decimator_init",
        compute = "sp_decimator_compute",
    },

    params = {
        optional = {
            {
                name = "bitdepth",
                type = "SPFLOAT",
                description = "Bit depth. Expects an integer in the range of 1-16. Fractional values will be truncated.",
                default = 8
            },
            {
                name = "srate",
                type = "SPFLOAT",
                description ="Sampling rate.",
                default = 10000
            },
        }
    },

    modtype = "module",

    description = [[Digital signal degradation

    Otherwise known as a "bitcrusher", Decimator will digitally degrade a signal by altering the bitdepth and sampling-rate. ]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "input",
            description = "Signal input."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Signal output"
        },
    }

}
