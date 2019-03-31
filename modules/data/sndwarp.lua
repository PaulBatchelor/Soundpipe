sptbl["sndwarp"] = {

    files = {
        module = "sndwarp.c",
        header = "sndwarp.h",
        example = "ex_sndwarp.c",
    },

    func = {
        create = "sp_sndwarp_create",
        destroy = "sp_sndwarp_destroy",
        init = "sp_sndwarp_init",
        compute = "sp_sndwarp_compute",
    },

    params = {
        mandatory = {
            {
                name = "ftpSamp",
                type = "sp_ftbl *",
                description = "Pointer to wave ftable",
                default = "N/A"
            },
            {
                name = "ibegin",
                type = "SPFLOAT",
                description = "Offset to begin playback.",
                default = 0
            },
            {
                name = "iwsize",
                type = "int32_t",
                description = "Window size (in samples).",
                default = 4410
            },
            {
                name = "irandw",
                type = "int32_t",
                description = "Bandwidth of a random number generator. This is to be added to iwsize.",
                default = 882
            },
            {
                name = "ioverlap",
                type = "int32_t",
                description = "Determines density of overlapping windows.",
                default = 5
            },
            {
                name = "ftpWind",
                type = "sp_ftbl *",
                description = "Pointer to windowing function.",
                default = "N/A"
            },
            {
                name = "itimemode",
                type = "int",
                description = "Some time flag.",
                default = 1
            }
        },

        optional = {
            {
                name = "amp",
                type = "SPFLOAT",
                description = "Amplitude.",
                default = 1
            },
            {
                name = "timewarp",
                type = "SPFLOAT",
                description ="Timewarp factor. 1=normal, 2=halfspeed, 0.5=double time",
                default = 2
            },
            {
                name = "resample",
                type = "SPFLOAT",
                description ="Pitch stretch factor. 1=normal, 2=double speed, 0.5=halfspeed",
                default = 2
            },
        }
    },

    modtype = "module",

    description = [[A short title describing the module

    This is a description of the entire module.  This is not a real module. This description should be a comprehensive sumary of what this function does.

Inside the Lua table, this is expressed as a multiline string, however it does not adhere to the tradtional 80 column rule found in programming.

Write as much text as needed here...
]],

    ninputs = 2,
    noutputs = 2,

    inputs = {
        {
            name = "clock",
            description = "this is the clock source for a made up plugin."
        },
        {
            name = "input",
            description = "this is the audio input for a made up plugin."
        },
    },

    outputs = {
        {
            name = "out_left",
            description = "Stereo left output for sndwarp."
        },
        {
            name = "out_right",
            description = "Stereo right output for sndwarp."
        },
    }

}
