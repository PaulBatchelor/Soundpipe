sptbl["diode"] = {

    files = {
        module = "diode.c",
        header = "diode.h",
        example = "ex_diode.c",
    },

    func = {
        create = "sp_diode_create",
        destroy = "sp_diode_destroy",
        init = "sp_diode_init",
        compute = "sp_diode_compute",
    },

    params = {
        optional = {
            {
                name = "freq",
                type = "SPFLOAT",
                description = "",
                default = 1000
            },
            {
                name = "res",
                type = "SPFLOAT",
                description ="",
                default = 0
            },
        }
    },

    modtype = "module",

    description = [[Diode-ladder virtual analogue low-pass filter
This is a diode-ladder filter designed by Will Pirkle. 
More information can be found in this paper here: 
http://www.willpirkle.com/Downloads/AN-6DiodeLadderFilter.pdf
]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "input",
            description = "Signal input."
        },
    },

    outputs = {
        {
            name = "out_left",
            description = "Stereo left output for diode."
        },
        {
            name = "out_right",
            description = "Stereo right output for diode."
        },
    }

}
