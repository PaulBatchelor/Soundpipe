sptbl["lpc"] = {

    files = {
        module = "lpc.c",
        header = "lpc.h",
        example = "ex_lpc.c",
    },

    func = {
        create = "sp_lpc_create",
        destroy = "sp_lpc_destroy",
        init = "sp_lpc_init",
        compute = "sp_lpc_compute",
    },

    params = {
        mandatory = {
            {
                name = "framesize",
                type = "int",
                description = "Sets the frame size for the encoder.",
                default = 512
            },
        },

        optional = {
        }
    },

    modtype = "module",

    description = [[A linear predictive coding filter.
This module is a wrapper for the open source library openlpc, which implements
the LPC10 audio codec optimized for speech signals. This module takes in an
input signal, downsamples it, and produces a decoded LPC10 audio signal, which
has a similar sound to that of a speak and spell. In this context, the LPC
signal is meant to be more of a audio effect rather than a utility for
communication. 

Because the LPC10 encoder
relies on frames for encoding, the output signal has a few milliseconds of
delay. 
 
]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "input",
            description = "Input signal to be processed with LPC."
        },
    },

    outputs = {
        {
            name = "output",
            description = "LPC encoded signal."
        },
    }

}
