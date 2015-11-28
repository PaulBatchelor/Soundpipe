sptbl["saw"] = {

    files = {
        module = "saw.c",
        header = "saw.h",
        example = "ex_saw.c",
    },

    func = {
        create = "sp_saw_create",
        destroy = "sp_saw_destroy",
        init = "sp_saw_init",
        compute = "sp_saw_compute",
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
        }
    },

    modtype = "module",

    description = [[Bandlimited sawtooth oscillator
This is a bandlimited sawtooth oscillator ported from the "sawtooth" function from the Faust 
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
