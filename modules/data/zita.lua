sptbl["zita"] = {

    files = {
        module = "zita.c",
        header = "zita.h",
        example = "ex_zita.c",
    },

    func = {
        create = "sp_zita_create",
        destroy = "sp_zita_destroy",
        init = "sp_zita_init",
        compute = "sp_zita_compute",
    },

    params = {
        optional = {
            {
                name = "in_delay",
                type = "SPFLOAT",
                description = "Delay in ms before reverberation begins.",
                default = 60
            },
            {
                name = "lf_x",
                type = "SPFLOAT",
                description ="Crossover frequency separating low and middle frequencies (Hz).",
                default = 200
            },
            {
                name = "rt60_low",
                type = "SPFLOAT",
                description ="Time (in seconds) to decay 60db in low-frequency band.",
                default = 3.0
            },
            {
                name = "rt60_mid",
                type = "SPFLOAT",
                description ="Time (in seconds) to decay 60db in mid-frequency band.",
                default = 2.0
            },
            {
                name = "hf_damping",
                type = "SPFLOAT",
                description ="Frequency (Hz) at which the high-frequency T60 is half the middle-band's T60.",
                default = 6000.0
            },
            {
                name = "eq1_freq",
                type = "SPFLOAT",
                description ="Center frequency of second-order Regalia Mitra peaking equalizer section 1.",
                default = 315.0
            },
            {
                name = "eq1_level",
                type = "SPFLOAT",
                description ="Peak level in dB of second-order Regalia-Mitra peaking equalizer section 1",
                default = 0
            },
            {
                name = "eq2_freq",
                type = "SPFLOAT",
                description ="Center frequency of second-order Regalia Mitra peaking equalizer section 2.",
                default = 1500.0
            },
            {
                name = "eq2_level",
                type = "SPFLOAT",
                description ="Peak level in dB of second-order Regalia-Mitra peaking equalizer section 2",
                default = 0 
            },
            {
                name = "mix",
                type = "SPFLOAT",
                description ="-1 = all dry, 1 = all wet",
                default = 0
            },
            {
                name = "level",
                type = "SPFLOAT",
                description ="Output scale factor (in dB).",
                default = -20
            }
        }
    },

    modtype = "module",

    description = [[8 FDN stereo zita-reverb algorithm, imported from Faust.]],

    ninputs = 2,
    noutputs = 2,

    inputs = {
        {
            name = "input_1",
            description = "First input."
        },
        {
            name = "input_2",
            description = "Second input."
        },
    },

    outputs = {
        {
            name = "out_1",
            description = "Channel 1 output. Most likely for the left channel."
        },
        {
            name = "out_2",
            description = "Channel 2 output. Mose likely for the right channel."
        },
    }

}
