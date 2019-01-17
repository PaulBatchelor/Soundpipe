sptbl["adsr"] = {

    files = {
        module = "adsr.c",
        header = "adsr.h",
        example = "ex_adsr.c",
    },

    func = {
        create = "sp_adsr_create",
        destroy = "sp_adsr_destroy",
        init = "sp_adsr_init",
        compute = "sp_adsr_compute",
    },

    params = {
        optional = {
            {
                name = "atk",
                type = "SPFLOAT",
                description = "Attack",
                default = 0.1
            },
            {
                name = "dec",
                type = "SPFLOAT",
                description ="Decay",
                default = 0.1
            },
            {
                name = "sus",
                type = "SPFLOAT",
                description ="Sustain (in range 0-1)",
                default = 0.5
            },
            {
                name = "rel",
                type = "SPFLOAT",
                description ="Release",
                default = 0.3
            },
        }
    },

    modtype = "module",

    description = [[ADSR generator
This is an ADSR generator whose curves are created using a one-pole low pass filter.

NOTE: The attack, decay, and release parameters are "fuzzy" values that don't
exactly correspond to duration in seconds. More accurately, they are special
tau constant units that feed into the filter used to generate the envelope. The
attack value specificly undergoes some "creative" modificiations in order to
create snappier attack times. It is highly recommend to tune parameters by
ear rather than to read the values literally.
]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "gate",
            description = "Gate signal. This should be a steady state signal that jumps from 0 to 1."
        },
    },

    outputs = {
        {
            name = "out",
            description = "ADSR envelope."
        },
    }

}
