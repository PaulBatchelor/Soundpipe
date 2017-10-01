sptbl["talkbox"] = {

    files = {
        module = "talkbox.c",
        header = "talkbox.h",
        example = "ex_talkbox.c",
    },

    func = {
        create = "sp_talkbox_create",
        destroy = "sp_talkbox_destroy",
        init = "sp_talkbox_init",
        compute = "sp_talkbox_compute",
    },

    params = {
        optional = {
            {
                name = "quality",
                type = "SPFLOAT",
                description = "Quality of the talkbox sound. 0=lowest fidelity. 1=highest fidelity",
                default = 1
            },
        }
    },

    modtype = "module",

    description = [[A high talkbox emulation, simular to a vocoder.
This is the talkbox plugin ported from the MDA plugin suite. In many ways,
this Talkbox functions like a vocoder: it takes in a source signal (usually
speech), which then excites an excitation signal 
(usually a harmonically rich signal like a saw wave). This particular algorithm
uses linear-predictive coding (LPC), making speech intelligibility better 
than most vocoder implementations.
]],

    ninputs = 2,
    noutputs = 1,

    inputs = {
        {
            name = "source",
            description = "Input signal that shapes the excitation. Also known as the modulator."
        },
        {
            name = "excitation",
            description = "The signal to be excited. Also known as the carrier."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Talkbox signal output."
        },
    }

}
