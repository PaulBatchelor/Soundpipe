sptbl["autowah"] = {

    files = {
        module = "autowah.c",
        header = "autowah.h",
        example = "ex_autowah.c",
    },

    func = {
        create = "sp_autowah_create",
        destroy = "sp_autowah_destroy",
        init = "sp_autowah_init",
        compute = "sp_autowah_compute",
        other = {
            sp_autowah_set = {
                description = "autowah_set description goes here.",
                args = {
                    {
                        name = "var1",
                        type = "SPFLOAT",
                        description = "This is the first parameter",
                        default = 1.5
                    },
                    {
                        name = "var2",
                        type = "SPFLOAT",
                        description = "This is the second parameter",
                        default = 1.5
                    }
                }
            }
        }
    },

    params = {
        optional = {
            {
                name = "level",
                type = "SPFLOAT",
                description = "Overall level (between 0 and 1)",
                default = 0.1
            },
            {
                name = "wah",
                type = "SPFLOAT",
                description ="wah amount",
                default = 0
            },
            {
                name = "mix",
                type = "SPFLOAT",
                description ="Wet/dry amount (100 = wet, 0 = dry)",
                default = 100
            },
        }
    },

    modtype = "module",

    description = [[Automatic wah pedal
	An automatic wah effect, ported from Guitarix via Faust. 
]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "input",
            description = "Audio input"
        },
    },
    
    outputs = {
        {
            name = "output",
            description = "Audio output."
        },
    }

}
