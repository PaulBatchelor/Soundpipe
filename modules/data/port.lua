sptbl["port"] = {

    files = {
        module = "port.c",
        header = "port.h",
        example = "ex_port.c",
    },

    func = {
        create = "sp_port_create",
        destroy = "sp_port_destroy",
        init = "sp_port_init",
        compute = "sp_port_compute",
        other = {
            sp_port_reset = {
                description = "Resets internal buffers, snapping to input value instead of ramping to it.",
                args = {
                    {
                        name = "input",
                        type = "SPFLOAT *",
                        description = "input value to snap to.",
                        default = 0.0
                    },
                }
            }
        }
    },

    params = {
        mandatory = {
            {
                name = "htime",
                type = "SPFLOAT",
                description = "",
                default = 0.02
            },
        },
        optional = {
            {
                name = "htime",
                type = "SPFLOAT",
                description = "",
                default = 0.02
            },
        },
    },

    modtype = "module",

    description = [[ Portamento-style control signal smoothing

    Useful for smoothing out low-resolution signals and applying glissando to filters.]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "in",
            description = "Signal input."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Signal output."
        },
    }

}
