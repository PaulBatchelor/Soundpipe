sptbl["tenvx"] = {

    files = {
        module = "tenvx.c",
        header = "tenvx.h",
        example = "ex_tenvx.c",
    },

    func = {
        create = "sp_tenvx_create",
        destroy = "sp_tenvx_destroy",
        init = "sp_tenvx_init",
        compute = "sp_tenvx_compute",
    },

    params = {
        mandatory = {
            {
                name = "atk",
                type = "SPFLOAT",
                description = "Attack time, in seconds. Must be non-zero.",
                default = 0.1
            },
            {
                name = "hold",
                type = "SPFLOAT",
                description = "Hold time, in seconds.",
                default = 0.3
            },
            {
                name = "rel",
                type = "SPFLOAT",
                description = "Release time, in seconds. Must be non-zero.",
                default = 0.2
            }
        },
        optional = {
            {
                name = "sigmode",
                type = "int",
                description = "If set to non-zero value, tenvx will multiply the envelope with an internal signal instead of just returning an enveloped signal.",
                default = 0
            },
            {
                name = "input",
                type = "SPFLOAT",
                description = "Internal input signal. If sigmode variable is set, it will multiply the envelope by this variable. Most of the time, this should be updated at audiorate.",
                default = 0
            }
        }
    },

    modtype = "module",

    description = [[Trigger based exponential AHD envelope generator]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "trig",
            description = "Trigger input. When non-zero, the envelope will (re)trigger."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Signal output"
        },
    }

}
