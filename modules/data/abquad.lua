sptbl["abquad"] = {

    files = {
        module = "abquad.c",
        header = "abquad.h",
        --example = "ex_abquad.c",
    },

    func = {
        create = "sp_abquad_create",
        destroy = "sp_abquad_destroy",
        init = "sp_abquad_init",
        compute = "sp_abquad_compute",
        other = {
            sp_abquad_set = {
                description = "set coefs at once.",
                args = {
				            {
  		  		            name = "b0",
    		  		          type = "SPFLOAT",
      		  		        description = "biquad coefficient.",
  		        		      default = 0
  		          		},
    		        		{
       		         		name = "b1",
          		      		type = "SPFLOAT",
              		  		description = "biquad coefficient.",
                				default = 0
		            		},
    		        		{
        		        		name = "b2",
            		    		type = "SPFLOAT",
                				description = "biquad coefficient.",
                				default = 0
		            		},
    		        		{
        		        		name = "a1",
            		    		type = "SPFLOAT",
                				description = "biquad coefficient.",
                				default = 0
		            		},
    		        		{
        		        		name = "a2",
            		    		type = "SPFLOAT",
                				description = "biquad coefficient.",
                				default = 0
		            		}
                }
            }
        }

    },

    params = {
        optional = {
            {
                name = "b0",
                type = "SPFLOAT",
                description = "biquad coefficient.",
                default = 0
            },
            {
                name = "b1",
                type = "SPFLOAT",
                description = "biquad coefficient.",
                default = 0
            },
            {
                name = "b2",
                type = "SPFLOAT",
                description = "biquad coefficient.",
                default = 0
            },
            {
                name = "a1",
                type = "SPFLOAT",
                description = "biquad coefficient.",
                default = 0
            },
            {
                name = "a2",
                type = "SPFLOAT",
                description = "biquad coefficient.",
                default = 0
            }
            {
                name = "z1",
                type = "SPFLOAT",
                description = "biquad coefficient.",
                default = 0
            },
            {
                name = "z2",
                type = "SPFLOAT",
                description = "biquad coefficient.",
                default = 0
            },
        }
    },

    modtype = "module",

    description = [[A sweepable biquadratic general purpose filter

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
            name = "out",
            description = "Signal output."
        },
    }

}
