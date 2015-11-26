import("oscillator.lib");

freq = hslider("[0]freq", 440, 0, 20000, 0.0001);
amp = hslider("[1]amp", 1, 0, 1, 0.00001);
width = hslider("[2]width", 0.5, 0, 1, 0.0000);

process = pulsetrainN(4, freq, width) * amp;
