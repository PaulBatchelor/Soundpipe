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
                name = "ft_samp",
                type = "sp_ftbl *",
                description = "Pointer to wave ftable",
                default = "N/A"
            },
            {
                name = "ft_win",
                type = "sp_ftbl *",
                description = "Pointer to windowing function.",
                default = "N/A"
            },
            {
                name = "maxoverlap",
                type = "int32_t",
                description = "Maximum density.",
                default = 5
            },
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
            {
                name = "begin",
                type = "SPFLOAT",
                description = "Offset to begin playback (in seconds).",
                default = 0
            },
            {
                name = "wsize",
                type = "SPFLOAT",
                description = "Window size (in second).",
                default = 0.1
            },
            {
                name = "randw",
                type = "SPFLOAT",
                description = "Bandwidth of a random number generator. This is to be added to wsize.",
                default = 0.02
            },
            {
                name = "overlap",
                type = "SPFLOAT",
                description = "Determines density of overlapping windows.",
                default = 5
            },
            {
                name = "timemode",
                type = "int",
                description = "Timewarp mode. 0=stretch time, 1=scrubbing",
                default = 0
            }
        }
    },

    modtype = "module",

    description = [[Apply independent pitch and time stretching modification to a sample.
]],

    ninputs = 0,
    noutputs = 1,

    inputs = {
    },

    outputs = {
        {
            name = "out",
            description = "Audio output."
        },
    }
}
