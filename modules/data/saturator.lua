sptbl["saturator"] = {

    files = {
        module = "saturator.c",
        header = "saturator.h",
        example = "ex_saturator.c",
    },

    func = {
        create = "sp_saturator_create",
        destroy = "sp_saturator_destroy",
        init = "sp_saturator_init",
        compute = "sp_saturator_compute",
    },

    params = {
        optional = {
            {
                name = "drive",
                type = "SPFLOAT",
                description ="Input gain into the distortion section, in decibels. Controls overall amount of distortion.",
                default = 1.0
            },
            {
                name = "dcoffset",
                type = "SPFLOAT",
                description = "Constant linear offset applied to the signal. A small offset will introduce odd harmonics into the distoration spectrum, whereas a zero offset will have only even harmonics.",
                default = 0.0
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
