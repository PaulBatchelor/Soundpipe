sptbl["wavout"] = {

    files = {
        module = "wavout.c",
        header = "wavout.h",
        example = "ex_wavout.c",
    },

    func = {
        create = "sp_wavout_create",
        destroy = "sp_wavout_destroy",
        init = "sp_wavout_init",
        compute = "sp_wavout_compute",
    },

    params = {
        mandatory = {
            {
                name = "filename",
                type = "const char*",
                description = "The filename of the output file.",
                default = "N/A"
            }
        },
    },

    modtype = "module",

    description = [[Writes a mono signal to a WAV file.
This module uses the public-domain dr_wav library to write WAV files
to disk. This module is ideal for instances where GPL-licensed libsndfile 
cannot be used for legal reasons.
]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "input",
            description = "Mono input signal."
        },
    },

    outputs = {
        {
            name = "out",
            description = "A passthrough signal: a copy of the input signal."
        },
    }

}
