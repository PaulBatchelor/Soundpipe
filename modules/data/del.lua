sptbl["del"] = {

    files = { 
        module = "del.c",
        header = "del.h",
        example = "ex_del.c",
    },
    
    func = {
        create = "sp_del_create",
        destroy = "sp_del_destroy",
        init = "sp_del_init",
        compute = "sp_del_compute",
    },
    
    params = {
        mandatory = {
            {
                name = "maxdel",
                type = "SPFLOAT",
                description = "The maximum delay time, in seconds.",
                default = 1.0,
                irate = true
            },
        },
    
        optional = {
            {
                name = "del",
                type = "SPFLOAT",
                description = "Delay time (in seconds) that can be changed during performance. This value must not exceed the maximum delay time.",
                default = "maxdel"
            },
        }
    },
    
    modtype = "module",
    
    description = [[A delay line with cubic interpolation.]], 
    
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
            description = "Signal out."
        },
    }

}
