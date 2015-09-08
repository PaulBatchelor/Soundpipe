tbl = {
	name= "osc",
	outputs= "1",
	meta= {
		{ author= "Grame" },
		{ copyright= "(c)GRAME 2009" },
		{ license= "BSD" },
		{ mathlibauthor= "GRAME" },
		{ mathlibcopyright= "GRAME" },
		{ mathliblicense= "LGPL with exception" },
		{ mathlibname= "Math Library" },
		{ mathlibversion= "1.0" },
		{ musiclibauthor= "GRAME" },
		{ musiclibcopyright= "GRAME" },
		{ musicliblicense= "LGPL with exception" },
		{ musiclibname= "Music Library" },
		{ musiclibversion= "1.0" },
		{ name= "osc" },
		{ version= "1.0" }
	},
	ui= [
		{
			type= "vgroup",
			label= "Oscillator",
			items= [
				{
					type= "hslider",
					label= "freq",
					address= "/Oscillator/freq",
					meta= [
						{ unit= "Hz" }
					],
					init= "1000",
					min= "20",
					max= "24000",
					step= "1"
				},
				{
					type= "hslider",
					label= "volume",
					address= "/Oscillator/volume",
					meta= [
						{ unit= "dB" }
					],
					init= "0",
					min= "-96",
					max= "0",
					step= "0.1"
				}
			]
		}
	]
}
