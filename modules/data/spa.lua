sptbl["spa"] = {

    files = {
        module = "spa.c",
        header = "spa.h",
        example = "ex_spa.c",
    },

    func = {
        create = "sp_spa_create",
        destroy = "sp_spa_destroy",
        init = "sp_spa_init",
        compute = "sp_spa_compute",
    },

    params = {
        mandatory = {
            {
                name = "filename",
                type = "const char *",
                description = "Filename of SPA file",
                default = "N/A"
            },
        },

    },

    modtype = "module",

    description = [[Stream a Soundpipe Audio File
Similar to sp_diskin, sp_spa will stream a file in the internal soundpipe
audio format. Such a format is useful for instances where you need to read
audio files, but can't use libsndfile. 
]],

    ninputs = 0,
    noutputs = 1,

    inputs = {
    },

    outputs = {
        {
            name = "out",
            description = "Output to spa."
        },
    }

}
