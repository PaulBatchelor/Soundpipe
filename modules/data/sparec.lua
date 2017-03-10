sptbl["sparec"] = {

    files = {
        module = "sparec.c",
        header = "sparec.h",
        example = "ex_sparec.c",
    },

    func = {
        create = "sp_sparec_create",
        destroy = "sp_sparec_destroy",
        init = "sp_sparec_init",
        compute = "sp_sparec_compute",
        other = {
            sp_sparec_close = {
                description = "Close spa file and writes the rest of the data in the buffer.",
                args = {
                }
            }
        }
    },

    params = {
        mandatory = {
            {
                name = "filename",
                type = "const char *",
                description = "Filename to write to",
                default = "N/A"
            },
        },

    },

    modtype = "module",

    description = [[Writes signal to spa file.]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "input",
            description = "Input signal."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Copy of input signal."
        }
    }

}
