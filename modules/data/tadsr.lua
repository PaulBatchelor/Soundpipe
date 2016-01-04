sptbl["tadsr"] = {

    files = {
        module = "tadsr.c",
        header = "tadsr.h",
        example = "ex_tadsr.c",
    },

    func = {
        create = "sp_tadsr_create",
        destroy = "sp_tadsr_destroy",
        init = "sp_tadsr_init",
        compute = "sp_tadsr_compute",
    },

    params = {
        optional = {
            {
                name = "atk",
                type = "SPFLOAT",
                description = "Attack",
                default = 0.5
            },
            {
                name = "dec",
                type = "SPFLOAT",
                description ="Sustain",
                default = 0.5
            },
            {
                name = "sus",
                type = "SPFLOAT",
                description ="sustain",
                default = 0.5
            },
            {
                name = "rel",
                type = "SPFLOAT",
                description ="release",
                default = 0.5
            },
        }
    },

    modtype = "module",

    description = [[Triggerable classic ADSR envelope

]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "trig",
            description = "Expects trigger signal."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Envelope signal output."
        },
    }

}
