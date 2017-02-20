sptbl["clock"] = {

    files = {
        module = "clock.c",
        header = "clock.h",
        example = "ex_clock.c",
    },

    func = {
        create = "sp_clock_create",
        destroy = "sp_clock_destroy",
        init = "sp_clock_init",
        compute = "sp_clock_compute",
    },

    params = {

        optional = {
            {
                name = "bpm",
                type = "SPFLOAT",
                description = "Clock tempo, in beats per minute.",
                default = 120
            },
            {
                name = "subdiv",
                type = "SPFLOAT",
                description ="Clock subdivision. 2 = eighths, 4 = 16ths, etc.",
                default = 1
            },
        }
    },

    modtype = "module",

    description = [[Resettable clock with subdivisions
]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "trig",
            description = "When non-zero, will reset clock"
        },
    },

    outputs = {
        {
            name = "out",
            description = "Clock output."
        },
    }

}
