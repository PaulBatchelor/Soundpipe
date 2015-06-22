sptbl["rpt"] = {

    files = { 
        module = "rpt.c",
        header = "rpt.h",
        example = "ex_rpt.c",
    },
    
    func = {
        create = "sp_rpt_create",
        destroy = "sp_rpt_destroy",
        init = "sp_rpt_init",
        compute = "sp_rpt_compute",
        other = { 
            sp_rpt_set = {
                description = "Set the repeat amount in tempo-based subdivisions",
                args = { 
                    {
                        name = "bpm",
                        type = "SPFLOAT",
                        description = "Desired tempo.",
                        default = 120
                    },
                    {
                        name = "div",
                        type = "int",
                        description = "Divider amount. 2 = eigth, 4 = 16th, 3 = triplet, etc. This must be a whole number integer",
                        default = 4
                    },
                    {
                        name = "rep",
                        type = "int",
                        description = "Number of times to repeat. This must be a whole number integer.",
                        default = 4
                    }
                }
            }
        }
    },
    
    params = {
        mandatory = {
            {
                name = "maxdur",
                type = "SPFLOAT",
                description = "Maximum delay duration in seconds. This will set the buffer size.",
                default = "0.7"
            }
        }
    },
    
    modtype = "module",
    
    description = [["rpt" is a trigger based beat-repeat stuttering effect. When the input is a non-zero value, rpt will load up the buffer and loop a certain number of times. Speed and repeat amounts can be set with the sp_rpt_set function.]], 
    
    ninputs = 1,
    noutputs = 1,
    
    inputs = { 
        {
            name = "trig",
            description = "When this value is non-zero, it will start the repeater."
        },
        {
            name = "input",
            description = "The signal to be repeated."
        },
    },
    
    outputs = {
        {
            name = "out",
            description = "Signal out. This is passive unless explicity triggered in the input."
        },
    }

}
