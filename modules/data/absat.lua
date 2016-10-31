sptbl["absat"] = {

    files = {
        module = "absat.c",
        header = "absat.h",
        example = "ex_absat.c",
    },

    func = {
        create = "sp_absat_create",
        destroy = "sp_absat_destroy",
        init = "sp_absat_init",
        compute = "sp_absat_compute",
    },

    params = {
        optional = {
            {
                name = "dcOffset",
                type = "SPFLOAT",
                description = "Constant linear offset applied to the signal. A small offset will introduce odd harmonics into the distoration spectrum, whereas a zero offset will have only even harmonics.",
                default = 0.0
            },
            {
                name = "drive",
                type = "SPFLOAT",
                description ="Input gain into the distortion section, in decibels. Controls overall amount of distortion.",
                default = 1.0
            },
        }
    },

    modtype = "module",

    description = [[Soft clip saturating distortion, based on examples from Abel/Berners' Music 424 course at Stanford.]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "in",
            description = "input."
        },
    },

    outputs = {
        {
            name = "out",
            description = "output."
        },
    }

}
