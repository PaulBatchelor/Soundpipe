sptbl["trem"] = {

    files = {
        module = "trem.c",
        header = "trem.h",
        example = "ex_trem.c",
    },

    func = {
        create = "sp_trem_create",
        destroy = "sp_trem_destroy",
        init = "sp_trem_init",
        compute = "sp_trem_compute",
    },

    params = {
        mandatory = {
            {
                name = "tbl",
                type = "sp_ftbl *",
                description = "Wavetable to read from. Note: the size of this table must be a power of 2.",
                default = "N/A"
            },
        },
        optional = {
            {
                name = "freq",
                type = "SPFLOAT",
                description = "Frequency (in Hz)",
                default = 440
            },
        }
    },

    modtype = "module",

    description = [[ Table-lookup tremolo with linear interpolation]],

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
