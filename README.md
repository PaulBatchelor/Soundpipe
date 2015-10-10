Soundpipe
=========

Soundpipe is a lightweight music DSP library written in C. It aims to provide
a set of high-quality DSP modules for composers, sound designers,
and creative coders.

Features
---------

- A great set of high-quality modules ported directly from the Csound library
- Sample accurate timing
- Small codebase
- Static library
- Easily extendable
- Easily embeddable

Soundpipe is primarily desgined to generate wav files, however there are
optional modules which allow Soundpipe to be run in realtime via JACK or
from a Raspberry Pi (ALSA). See the *compilation* section for how to enable
these.

Compilation
-----------

By default, Soundpipe needs libsndfile, and a standard build environment. 
Other modules that use other external libraries will need to be explicitly compiled
by modififying config.mk.

If you are using a Mac, clone and build from the libsndfile repository here 
located here: https://github.com/erikd/libsndfile/

On Linux, the libsndfile-dev package will need to be installed.

To compile:

make

sudo make install

To build additional plugins with external library dependencies, uncomment lines
in the file "config.mk".

To build the examples, go into the examples folder and run "make", which will create
files with a .bin extention. When an example is run, it will generate a 
5 second file called "test.wav". Examples in the "extra"
folder are for optional modules that require third-party libraries. 
To compile these examples, uncomment the appropriate lines in "config.mk".

The Soundpipe Model
-------------------

Soundpipe is callback driven. Every time Soundpipe needs a frame, it will
call upon a single function specified by the user. Soundpipe modules are
designed to process a signal, one sample at a time.  Every module follows the
same life cycle:

1. Create: Memory is allocated for the data struct.
2. Initialize: Buffers are allocated, and initial variables and constants
are set.
3. Compute: the module takes in inputs (if applicable), and generates a
single sample of output.
4. Destroy: All memory allocated is freed.

Documentation
-------------
If you have lua installed on your computer, you can generate the current html
documentation for soundpipe by running "make docs". A folder called "docs"
will be created. The top page for the documentation is docs/index.html.



Contributors of Soundpipe:
--------------------------
Paul Batchelor

Alex Tape

Daniel Friedman

Nick Arner

Aurelius Prochazka 


Contributing
--------------------------
We welcome all contributions! If you find a bug, please feel free to make a bug report or
a pull-request. 

Additionally, if you'd like to contribute bys adding more modules to Soundpipe, please 
see the Style Guide (util/style\_guide.md) and the Module How-To Guide (util/module\_howto.md).



