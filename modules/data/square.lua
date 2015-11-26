sptbl["square"] = {

    files = {
        module = "square.c",
        header = "square.h",
        example = "ex_square.c",
    },

    func = {
        create = "sp_square_create",
        destroy = "sp_square_destroy",
        init = "sp_square_init",
        compute = "sp_square_compute",
    },

    params = {
        optional = {
            {
                name = "freq",
                type = "SPFLOAT",
                description = "Frequency, (range 0-20000)",
                default = 440
            },
            {
                name = "amp",
                type = "SPFLOAT",
                description ="Amplitude (range 0-1).", 
		default = 1.0
            },
            {
                name = "width",
                type = "SPFLOAT",
                description ="Duty cycle width (range 0-1).", 
		default = 0.5
            },
        }
    },

    modtype = "module",

    description = [[Bandlimited square oscillator
This is a bandlimited square oscillator ported from the "squaretooth" function from the Faust 
programming language.
]],

    ninputs = 0,
    noutputs = 1,

    inputs = {
        {
            name = "dummy",
            description = "This doesn't do anything."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Signal output."
        },
    }

}
