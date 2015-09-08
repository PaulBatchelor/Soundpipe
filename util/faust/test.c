/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2009"
license: "BSD"
name: "osc"
version: "1.0"
Code generated with Faust 2.0.a37 (http://faust.grame.fr)
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__
/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------

	This is sample code. This file is provided as an example of minimal
	FAUST architecture file. Redistribution and use in source and binary
	forms, with or without modification, in part or in full are permitted.
	In particular you can create a derived work of this FAUST architecture
	and distribute that work under terms of your choice.

	This sample code is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 ************************************************************************
 ************************************************************************/

#include <math.h>
#include "CUI.h"

#define max(a,b) ((a < b) ? b : a)
#define min(a,b) ((a < b) ? a : b)

/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/


/******************************************************************************
*******************************************************************************

			ABSTRACT USER INTERFACE

*******************************************************************************
*******************************************************************************/

//----------------------------------------------------------------------------
//  FAUST generated signal processor
//----------------------------------------------------------------------------

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif  

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>

float sinf(float dummy0);

typedef struct {
	
	int iRec1[2];
	
} mydspSIG0;

static mydspSIG0* newmydspSIG0() { return (mydspSIG0*)malloc(sizeof(mydspSIG0)); }
static void deletemydspSIG0(mydspSIG0* dsp) { free(dsp); }

int getNumInputsmydspSIG0(mydspSIG0* dsp) {
	return 0;
	
}
int getNumOutputsmydspSIG0(mydspSIG0* dsp) {
	return 1;
	
}
int getInputRatemydspSIG0(mydspSIG0* dsp, int channel) {
	int rate;
	switch (channel) {
		default: {
			rate = -1;
			break;
		}
		
	}
	return rate;
	
}
int getOutputRatemydspSIG0(mydspSIG0* dsp, int channel) {
	int rate;
	switch (channel) {
		case 0: {
			rate = 0;
			break;
		}
		default: {
			rate = -1;
			break;
		}
		
	}
	return rate;
	
}

static void instanceInitmydspSIG0(mydspSIG0* dsp, int samplingFreq) {
	/* C99 loop */
	{
		int i1;
		for (i1 = 0; (i1 < 2); i1 = (i1 + 1)) {
			dsp->iRec1[i1] = 0;
			
		}
		
	}
	
}

static void fillmydspSIG0(mydspSIG0* dsp, int count, float* output) {
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->iRec1[0] = (1 + dsp->iRec1[1]);
			output[i] = sinf((9.58738e-05f * (float)(dsp->iRec1[0] - 1)));
			dsp->iRec1[1] = dsp->iRec1[0];
			
		}
		
	}
	
};


float powf(float dummy0, float dummy1);
static float ftbl0mydspSIG0[65536];
float floorf(float dummy0);

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

typedef struct {
	
	float fRec0[2];
	float fRec2[2];
	FAUSTFLOAT fHslider0;
	int fSamplingFreq;
	float fConst0;
	FAUSTFLOAT fHslider1;
	
} mydsp;

mydsp* newmydsp() { 
	mydsp* dsp = (mydsp*)malloc(sizeof(mydsp));
	return dsp;
}

void deletemydsp(mydsp* dsp) { 
	free(dsp);
}

void metadatamydsp(MetaGlue* m) { 
	m->declare(m->mInterface, "author", "Grame");
	m->declare(m->mInterface, "copyright", "(c)GRAME 2009");
	m->declare(m->mInterface, "license", "BSD");
	m->declare(m->mInterface, "math.lib/author", "GRAME");
	m->declare(m->mInterface, "math.lib/copyright", "GRAME");
	m->declare(m->mInterface, "math.lib/license", "LGPL with exception");
	m->declare(m->mInterface, "math.lib/name", "Math Library");
	m->declare(m->mInterface, "math.lib/version", "1.0");
	m->declare(m->mInterface, "music.lib/author", "GRAME");
	m->declare(m->mInterface, "music.lib/copyright", "GRAME");
	m->declare(m->mInterface, "music.lib/license", "LGPL with exception");
	m->declare(m->mInterface, "music.lib/name", "Music Library");
	m->declare(m->mInterface, "music.lib/version", "1.0");
	m->declare(m->mInterface, "name", "osc");
	m->declare(m->mInterface, "version", "1.0");
}

int getSampleRatemydsp(mydsp* dsp) { return dsp->fSamplingFreq; }

int getNumInputsmydsp(mydsp* dsp) {
	return 0;
	
}
int getNumOutputsmydsp(mydsp* dsp) {
	return 1;
	
}
int getInputRatemydsp(mydsp* dsp, int channel) {
	int rate;
	switch (channel) {
		default: {
			rate = -1;
			break;
		}
		
	}
	return rate;
	
}
int getOutputRatemydsp(mydsp* dsp, int channel) {
	int rate;
	switch (channel) {
		case 0: {
			rate = 1;
			break;
		}
		default: {
			rate = -1;
			break;
		}
		
	}
	return rate;
	
}

void classInitmydsp(int samplingFreq) {
	mydspSIG0* sig0 = newmydspSIG0();
	instanceInitmydspSIG0(sig0, samplingFreq);
	fillmydspSIG0(sig0, 65536, ftbl0mydspSIG0);
	deletemydspSIG0(sig0);
	
}

void instanceInitmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fHslider0 = (FAUSTFLOAT)0.;
	/* C99 loop */
	{
		int i0;
		for (i0 = 0; (i0 < 2); i0 = (i0 + 1)) {
			dsp->fRec0[i0] = 0.f;
			
		}
		
	}
	dsp->fConst0 = (1.f / (float)min(192000, max(1, dsp->fSamplingFreq)));
	dsp->fHslider1 = (FAUSTFLOAT)1000.;
	/* C99 loop */
	{
		int i2;
		for (i2 = 0; (i2 < 2); i2 = (i2 + 1)) {
			dsp->fRec2[i2] = 0.f;
			
		}
		
	}
	
}

void initmydsp(mydsp* dsp, int samplingFreq) {
	classInitmydsp(samplingFreq);
	instanceInitmydsp(dsp, samplingFreq);
}

void buildUserInterfacemydsp(mydsp* dsp, UIGlue* interface) {
	interface->openVerticalBox(interface->uiInterface, "Oscillator");
	interface->addHorizontalSlider(interface->uiInterface, "freq", &dsp->fHslider1, 1000.f, 20.f, 24000.f, 1.f);
	interface->addHorizontalSlider(interface->uiInterface, "volume", &dsp->fHslider0, 0.f, -96.f, 0.f, 0.1f);
	interface->closeBox(interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* output0 = outputs[0];
	float fSlow0 = (0.001f * powf(10.f, (0.05f * (float)dsp->fHslider0)));
	float fSlow1 = (dsp->fConst0 * (float)dsp->fHslider1);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->fRec0[0] = ((0.999f * dsp->fRec0[1]) + fSlow0);
			float fTemp0 = (dsp->fRec2[1] + fSlow1);
			dsp->fRec2[0] = (fTemp0 - floorf(fTemp0));
			output0[i] = (FAUSTFLOAT)(dsp->fRec0[0] * ftbl0mydspSIG0[(int)(65536.f * dsp->fRec2[0])]);
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec2[1] = dsp->fRec2[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


//int main(int argc, char *argv[])
//{
//    mydsp* dsp = newmydsp();
//    deletemydsp(dsp);
//}

#endif
