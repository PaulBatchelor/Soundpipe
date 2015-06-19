Soundpipe
=========

Soundpipe is a lightweight music DSP library written in C. It aims to provide
a set of high-quality DSP modules for composers, sound designers,
and creative coders. 

Features
---------

- A great set of high-quality modules ported directly from the Csound library
- Sample accurate timing
- Tiny codebase
- Static library
- Easily extendable
- Easily embeddable

Soundpipe is primarily desgined to generate wav files, however there are 
optional modules which allow Soundpipe to be run in realtime via JACK or
from a Raspberry Pi (ALSA). See the *compilation* section for how to enable 
these.

Compilation
-----------

By default, Soundpipe only needs libsndfile. To compile:

make

sudo make install

To build additional plugins with external library dependencies, uncomment lines 
in the file "config.mk".

To build the examples, go into the (e)xamples folder and run "make". Each 
example will generate a 5 second file called "test.wav". Examples in the "extra"
folder are for optional modules. Open up the Makefile and uncomment the
specific files you want to compile.

Future Plans
------------
- multi-channel support (only mono right now)
- dynamic documentation generation (HTML, LaTeX, manpage, etc...)
- Faust support
- Commandline utilities

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

Credits
-------

Soundpipe is created by Paul Batchelor. 

It is maintained by him and Alex Tape.
