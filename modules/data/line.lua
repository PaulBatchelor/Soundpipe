sptbl["line"] = {

    files = {
        module = "line.c",
        header = "line.h",
        example = "ex_line.c",
    },

    func = {
        create = "sp_line_create",
        destroy = "sp_line_destroy",
        init = "sp_line_init",
        compute = "sp_line_compute",
    },

    params = {
        mandatory = {
            {
                name = "ia",
                type = "sp_ftbl *",
                description = "Inital point.",
                default = 1.0
            },
            {
                name = "idur",
                type = "SPFLOAT",
                description = "Duration (in seconds)",
                default = 1.0
            },
            {
                name = "ib",
                type = "SPFLOAT",
                description = "End point",
                default = 1.0
            }
        },

    },

    modtype = "module",

    description = [[Produce a line segment with linear slope
This will generate a line from value A to value B in given amount of time. 
When it reaches it's target, it will stay at that value. 
]],

    ninputs = 0,
    noutputs = 1,

    inputs = {
        {
            name = "dummy",
            description = ""
        },
    },

    outputs = {
        {
            name = "out",
            description = "Signal output."
        },
    }

}
