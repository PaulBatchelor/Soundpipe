Soundpipe Style Guide
=====================

If you would like to contribute to Soundpipe, the code you make should conform
to these guidelines. 

# C Code Conventions

The C code in Soundpipe follows most of the [C style guidelines](http://www.suckless.org/style) found on the
suckless.org website with few exceptions. If you're ever in doubt about something not specified here, use the suckless style guide, or the [Linux Kernel style guide](https://www.kernel.org/doc/Documentation/CodingStyle).

Avoid using macros whenever possible. 

If you are creating a new module, the expectation is that all code for that
module resides in a single c and header file.

# Commenting

Comments in Soundpipe are rather sparse, unless they make up the header of a module file. 
There's a reason for this. DSP code in C is hard to read even with comments. The algorithm
used in your code should be clear after studying the code. If you are making a module and 
would like to explain what it does in depth, you should document it properly using Soundpipe's
documentation format.

If you do need to comment, use only /\* \*/ commenting conventions.

The Linux Kernel convention for commenting is preferred for multiline - block comments, 
but not necessary.

If you need to explain what your code is doing, there is probably something wrong with your code.

If you are doing something necessarily clever, make a comment about it.

If some of your code has bad hacks out of desperation, make a comment about it. It's okay,
we all have done it before, but note that this will need to be fixed eventually. Feel free to mention
that you would like some help in your pull-request.

If you are using DSP code or algorithms from someone else, keep it in the header of the .c file. 
There are several ported Csound opcodes you can use as reference (metro is a good example).



# Naming

Choose good names for your variables so your code is clear. In C, a good variable name
has the right balance of terseness and verboseness for maximum clarity and grokking. As an example, abbreviating "frquency" to "freq" is acceptable, but abbreviating "filter cutoff" to "fc" is not. 

Variables should be one word, but if they must use more than one word, 
use under\_score\_variables and not camelCase.

Soundpipe has a lot of accepted abbreviations for certain variables. These are okay names
to use for module parameters:

- freq for frequency (do not use cps)
- amp for amplitude
- mod for modulation frequency
- car for carrier frequency
- atk for attack
- dec for decay
- rel for release
- dist for distortion
- filt for filter
- bw for bandwidth
- sr for samplerate
- res for resonance
- prev for previous

If you are porting Csound code, there is often a tendency to put a, k, or i in front
of a variable to indicate audio, control, or init-rate variables. Ditch the a's and k's...
i's can be allowed.

# Tests

If you are adding a test for a module you wrote, make sure the test passes before making a pull-request. 

#Algorithm Explanations

DSP code, especially when written in C, can be difficult to read. Algorithm explanations should be kept in modules/data, and not in the source code itself. Make sure any explanations are clear and concise.  