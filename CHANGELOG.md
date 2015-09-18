# Change log

0.4 
---
    - License change: GPL to MIT
    - sp_progress CLI progress bar
    - New modules: scale, butbr, pan2, pareq, tenv2, jcrev, barmodel
    - Modules can now be made with Faust!
    - Testing utility and framework (libsptest) created. See test folder
    - Improved docgen
    - Bug fixes

0.3 "Automation"
----------------
    - New modules:
        - eqfil
        - atone
        - butbr
        - foo (dummy module)
        - pluck
        - delay (static delay with feedback)
        - random
        - diskin
        - in
        - nsmp
        - switch
        - dmetro
        - samphold
    - Module boostrapper with documentation
    - renamed delay to vdelaya
    - Documented gen routines
    - Style guide written

0.2.2: "Tables"
---------------
    - New gen routines: gen_line, gen_xline, gen_gauss
    - New Modules: vco, reson, allpass, phasor, comb, tabread
    - Docgen support for gen routines
    - A standardized layout for gen routines
    - Bug fixes relating to docgen, maxdel, and libsndfile valgrind errors
    - Musical example 5 (byte beats!)

0.2.1: "Mo Modules"
-------------------
    - New modules: dist, gbuzz fosc, butbp, drip, clip,
    balance, rms, jitter, lpf18
    - Updated: mode, jack, rpi, tenv
    - 2 new musical examples
    - updated html docgen to work with Lynx better
    - amalgamation of soundpipe sources possible
    - sp_param/sp_set
0.2.0
-----
    - html documentation generator
    - metadata for current modules created in modules/data 
    - improved build instructions for OSX
    - example cleanup
    - module variable cleanup
    - Port of Csound GEN07 (gen_line)
    - Multi-channel and Multi-mono file support
    - Revsc module is now stereo
    - This changelog exists

0.1.0
-----

    initial release
