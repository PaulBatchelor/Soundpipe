sptbl["count"] = {

    files = {
        module = "count.c",
        header = "count.h",
        example = "ex_count.c",
    },

    func = {
        create = "sp_count_create",
        destroy = "sp_count_destroy",
        init = "sp_count_init",
        compute = "sp_count_compute",
    },

    params = {
        optional = {
            {
                name = "count",
                type = "SPFLOAT",
                description = "Number to count up to (count - 1). Decimal points will be truncated.",
                default = 4
            },
        },
    },

    modtype = "module",

    description = [[Trigger-based fixed counter. The signal output will count from 0 to [N-1], and then
repeat itself. ]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "trig",
            description = "When non-zero, will increment. When the output value is N - 1, it will loop back to zero."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Signal output."
        },
    }

}
