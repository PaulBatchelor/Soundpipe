sptbl["jcrev"] = {

    files = { 
        module = "jcrev.c",
        header = "jcrev.h",
        example = "ex_jcrev.c",
    },
    
    func = {
        create = "sp_jcrev_create",
        destroy = "sp_jcrev_destroy",
        init = "sp_jcrev_init",
        compute = "sp_jcrev_compute",
    },
    
    params = {
    },
    
    modtype = "module",
    
    description = [[John Chowning reverberator. This is was built using the JC reverb 
implentation found in FAUST. According to the source code, the specifications for 
this implementation were found on an old SAIL DART backup tape.]], 
    
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
            name = "out",
            description = "Signal Output."
        },
    }

}
