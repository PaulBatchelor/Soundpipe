sptbl["wavin"] = {

    files = {
        module = "wavin.c",
        header = "wavin.h",
        example = "ex_wavin.c",
    },

    func = {
        create = "sp_wavin_create",
        destroy = "sp_wavin_destroy",
        init = "sp_wavin_init",
        compute = "sp_wavin_compute",
        other = {
            sp_wavin_seek = {
                description = "Seeks to position in file.",
                args = {
                    {
                        name = "sample",
                        type = "unsigned long",
                        description = "Sample position",
                        default = 0
                    }
                }
            },
            sp_wavin_get_sample = {
                description = "Get a particular sample from the file.",
                args = {
                    {
                        name = "pos",
                        type = "SPFLOAT",
                        description = "Sample position",
                        default = 0
                    }
                }
            }
        }
    },

    params = {
        mandatory = {
            {
                name = "filename",
                type = "const char *",
                description = "Filename",
                default = "N/A"
            },
        },

    },

    modtype = "module",

    description = [[Reads a mono WAV file.

This module reads a mono WAV file from disk. It uses the public-domain 
dr_wav library for decoding, so it can be a good substitute for libsndfile.
]],

    ninputs = 0,
    noutputs = 1,

    inputs = {
    },

    outputs = {
        {
            name = "out",
            description = "output signal."
        },
    }

}
