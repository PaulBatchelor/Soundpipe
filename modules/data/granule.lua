sptbl["granule"] = {

    files = {
        module = "granule.c",
        header = "granule.h",
        example = "ex_granule.c",
    },

    func = {
        create = "sp_granule_create",
        destroy = "sp_granule_destroy",
        init = "sp_granule_init",
        compute = "sp_granule_compute",
    },

    params = {
        mandatory = {
            {
                name = "ivoice",
                type = "SPLFLOAT",
                description = "The number of voices.",
                default = 64
            },
            {
                name = "iratio",
                type = "SPFLOAT",
                description = "playback rate control. 0.5 is half speed",
                default = 1
            },
            {
                name = "imode",
                type = "SPFLOAT",
                description = "playback mode. 1=forward,0=random,-1:backward",
                default = 1
            },
            {
                name = "ithd",
                type = "SPFLOAT",
                description = "threshold. skip samples smaller than this.",
                default = 0
            },
            {
                name = "ft",
                type = "sp_ftbl *",
                description = "ftable for sound source",
                default = "N/A"
            },
            {
                name = "ipshift",
                type = "SPFLOAT",
                description = "pitch shift control. 0=random. 1-4 sets up to 4 different random pitches.",
                default = 4
            },
            {
                name = "igskip",
                type = "SPFLOAT",
                description = "Initial skip from beginning of function table.",
                default = 0
            },
            {
                name = "igskip_os",
                type = "SPFLOAT",
                description = "Random pointer offset (s)",
                default = 0.005
            },
            {
                name = "ilength",
                type = "SPFLOAT",
                description = "length of table to be used, starting from igskip",
                default = 5
            },
            {
                name = "igap_os",
                type = "SPFLOAT",
                description = "Skip time offset randomness amount (0-100)",
                default = 50
            },
            {
                name = "igsize_os",
                type = "SPFLOAT",
                description = "Grain size random size amount (0-100)",
                default = 50
            },
            {
                name = "iatt",
                type = "SPFLOAT",
                description = "Grain attack (0-100).",
                default = 30
            },
            {
                name = "idec",
                type = "SPFLOAT",
                description = "Grain decay (0-100).",
                default = 30
            },
            {
                name = "iseed",
                type = "SPFLOAT",
                description = "Seed for RNG.",
                default = 0.39
            },
            {
                name = "ipitch1",
                type = "SPFLOAT",
                description = "Pitch shift parameter 1.",
                default = 1
            },
            {
                name = "ipitch2",
                type = "SPFLOAT",
                description = "Pitch shift parameter 2.",
                default = 1.42
            },
            {
                name = "ipitch3",
                type = "SPFLOAT",
                description = "Pitch shift parameter 3.",
                default = 0.29
            },
            {
                name = "ipitch4",
                type = "SPFLOAT",
                description = "Pitch shift parameter 4.",
                default = 2
            },
            {
                name = "ft_env",
                type = "sp_ftbl *",
                description = "Ftable envelope used for grain. Half-sine is a pretty good choice.",
                default = "N/A"
            },
        },

        optional = {
            {
                name = "xamp",
                type = "SPFLOAT",
                description = "Grain amplitude",
                default = 1
            },
            {
                name = "kgap",
                type = "SPFLOAT",
                description ="gap between grains in sec.",
                default = 50
            },
        }
    },

    modtype = "module",

    description = [[
A granular synthesizer, using an ftable as input.
]],

    ninputs = 0,
    noutputs = 1,

    inputs = {
    },

    outputs = {
        {
            name = "out",
            description = "Signal output for granule."
        },
    }

}
