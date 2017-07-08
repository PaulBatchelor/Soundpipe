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
        other = {
            sp_lpc_synth = {
                description = [[Toggle synth mode. 
                Instead of reading an input, manipulate the parameters in  
                a scaled ftable.]],
                args = { 
                    {
                        name = "ft",
                        type = "sp_ftbl *",
                        description = "ftable of size 7",
                        default = "N/A"
                    }
                }
            }
        }
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
delay. The delay can be calculated in seconds as (framesize * 4) / samplerate.

In addition to using the LPC as a decoder/encoder, this module can also be 
set to synth mode. Instead of reading from an input signal, the LPC can
instead read from parameters set directly in a scaled ftable. 

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
