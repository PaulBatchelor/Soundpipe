#include <stdlib.h>
#include <math.h>
#include "CUI.h"
#include "soundpipe.h"

#define max(a,b) ((a < b) ? b : a)
#define min(a,b) ((a < b) ? a : b)

#ifndef FAUSTFLOAT
#define FAUSTFLOAT SPFLOAT
#endif  


float tanf(float dummy0);
static float faustpower2_f(float value) {
	return (value * value);
	
}

float fabsf(float dummy0);
float expf(float dummy0);

typedef struct {
	
	float fRec0[3];
	float fRec3[3];
	float fRec4[3];
	float fRec7[3];
	float fRec8[3];
	float fRec11[3];
	float fRec12[3];
	float fRec15[3];
	float fRec16[3];
	float fRec19[3];
	float fRec20[3];
	float fRec23[3];
	float fRec24[3];
	float fRec27[3];
	float fRec28[3];
	float fRec31[3];
	float fRec32[3];
	float fRec35[3];
	float fRec36[3];
	float fRec39[3];
	float fRec40[3];
	float fRec43[3];
	float fRec44[3];
	float fRec47[3];
	float fRec48[3];
	float fRec51[3];
	float fRec52[3];
	float fRec55[3];
	float fRec56[3];
	float fRec59[3];
	float fRec60[3];
	float fRec63[3];
	float fRec64[3];
	float fRec67[3];
	float fRec68[3];
	float fRec71[3];
	float fRec72[3];
	float fRec75[3];
	float fRec76[3];
	float fRec79[3];
	float fRec80[3];
	float fRec83[3];
	float fRec84[3];
	float fRec87[3];
	float fRec88[3];
	float fRec91[3];
	float fRec92[3];
	float fRec95[3];
	float fRec96[3];
	float fRec99[3];
	float fRec100[3];
	float fRec103[3];
	float fRec104[3];
	float fRec107[3];
	float fRec108[3];
	float fRec111[3];
	float fRec112[3];
	float fRec115[3];
	float fRec116[3];
	float fRec119[3];
	float fRec120[3];
	float fRec123[3];
	float fRec124[3];
	float fRec127[3];
	float fRec2[2];
	float fRec1[2];
	float fRec6[2];
	float fRec5[2];
	float fRec10[2];
	float fRec9[2];
	float fRec14[2];
	float fRec13[2];
	float fRec18[2];
	float fRec17[2];
	float fRec22[2];
	float fRec21[2];
	float fRec26[2];
	float fRec25[2];
	float fRec30[2];
	float fRec29[2];
	float fRec34[2];
	float fRec33[2];
	float fRec38[2];
	float fRec37[2];
	float fRec42[2];
	float fRec41[2];
	float fRec46[2];
	float fRec45[2];
	float fRec50[2];
	float fRec49[2];
	float fRec54[2];
	float fRec53[2];
	float fRec58[2];
	float fRec57[2];
	float fRec62[2];
	float fRec61[2];
	float fRec66[2];
	float fRec65[2];
	float fRec70[2];
	float fRec69[2];
	float fRec74[2];
	float fRec73[2];
	float fRec78[2];
	float fRec77[2];
	float fRec82[2];
	float fRec81[2];
	float fRec86[2];
	float fRec85[2];
	float fRec90[2];
	float fRec89[2];
	float fRec94[2];
	float fRec93[2];
	float fRec98[2];
	float fRec97[2];
	float fRec102[2];
	float fRec101[2];
	float fRec106[2];
	float fRec105[2];
	float fRec110[2];
	float fRec109[2];
	float fRec114[2];
	float fRec113[2];
	float fRec118[2];
	float fRec117[2];
	float fRec122[2];
	float fRec121[2];
	float fRec126[2];
	float fRec125[2];
	int fSamplingFreq;
	int iConst0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fHslider0;
	float fConst3;
	float fConst4;
	float fConst5;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	float fConst6;
	float fConst7;
	float fConst8;
	float fConst9;
	float fConst10;
	float fConst11;
	float fConst12;
	float fConst13;
	float fConst14;
	float fConst15;
	float fConst16;
	float fConst17;
	float fConst18;
	float fConst19;
	float fConst20;
	float fConst21;
	float fConst22;
	float fConst23;
	float fConst24;
	float fConst25;
	float fConst26;
	float fConst27;
	float fConst28;
	float fConst29;
	float fConst30;
	float fConst31;
	float fConst32;
	float fConst33;
	float fConst34;
	float fConst35;
	float fConst36;
	float fConst37;
	float fConst38;
	float fConst39;
	float fConst40;
	float fConst41;
	float fConst42;
	float fConst43;
	float fConst44;
	float fConst45;
	float fConst46;
	float fConst47;
	float fConst48;
	float fConst49;
	float fConst50;
	float fConst51;
	float fConst52;
	float fConst53;
	float fConst54;
	float fConst55;
	float fConst56;
	float fConst57;
	float fConst58;
	float fConst59;
	float fConst60;
	float fConst61;
	float fConst62;
	float fConst63;
	float fConst64;
	float fConst65;
	float fConst66;
	float fConst67;
	float fConst68;
	float fConst69;
	float fConst70;
	float fConst71;
	float fConst72;
	float fConst73;
	float fConst74;
	float fConst75;
	float fConst76;
	float fConst77;
	float fConst78;
	float fConst79;
	float fConst80;
	float fConst81;
	float fConst82;
	float fConst83;
	float fConst84;
	float fConst85;
	float fConst86;
	float fConst87;
	float fConst88;
	float fConst89;
	float fConst90;
	float fConst91;
	float fConst92;
	float fConst93;
	float fConst94;
	float fConst95;
	float fConst96;
	float fConst97;
	float fConst98;
	float fConst99;
	float fConst100;
	float fConst101;
	float fConst102;
	float fConst103;
	float fConst104;
	float fConst105;
	float fConst106;
	float fConst107;
	float fConst108;
	float fConst109;
	float fConst110;
	float fConst111;
	float fConst112;
	float fConst113;
	float fConst114;
	float fConst115;
	float fConst116;
	float fConst117;
	float fConst118;
	float fConst119;
	float fConst120;
	float fConst121;
	float fConst122;
	float fConst123;
	float fConst124;
	float fConst125;
	float fConst126;
	float fConst127;
	float fConst128;
	float fConst129;
	
} vocoder;

static vocoder* newvocoder() { 
	vocoder* dsp = (vocoder*)malloc(sizeof(vocoder));
	return dsp;
}

static void deletevocoder(vocoder* dsp) { 
	free(dsp);
}

static void instanceInitvocoder(vocoder* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->iConst0 = min(192000, max(1, dsp->fSamplingFreq));
	dsp->fConst1 = tanf((95.4453f / (float)dsp->iConst0));
	dsp->fConst2 = (1.f / dsp->fConst1);
	dsp->fHslider0 = (FAUSTFLOAT)0.5;
	dsp->fConst3 = (2.f * (1.f - (1.f / faustpower2_f(dsp->fConst1))));
	/* C99 loop */
	{
		int i0;
		for (i0 = 0; (i0 < 3); i0 = (i0 + 1)) {
			dsp->fRec0[i0] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i1;
		for (i1 = 0; (i1 < 3); i1 = (i1 + 1)) {
			dsp->fRec3[i1] = 0.f;
			
		}
		
	}
	dsp->fConst4 = (0.f - dsp->fConst2);
	dsp->fConst5 = (1.f / (float)dsp->iConst0);
	dsp->fHslider1 = (FAUSTFLOAT)0.01;
	dsp->fHslider2 = (FAUSTFLOAT)0.01;
	/* C99 loop */
	{
		int i2;
		for (i2 = 0; (i2 < 2); i2 = (i2 + 1)) {
			dsp->fRec2[i2] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i3;
		for (i3 = 0; (i3 < 2); i3 = (i3 + 1)) {
			dsp->fRec1[i3] = 0.f;
			
		}
		
	}
	dsp->fConst6 = tanf((115.99f / (float)dsp->iConst0));
	dsp->fConst7 = (1.f / dsp->fConst6);
	dsp->fConst8 = (2.f * (1.f - (1.f / faustpower2_f(dsp->fConst6))));
	/* C99 loop */
	{
		int i4;
		for (i4 = 0; (i4 < 3); i4 = (i4 + 1)) {
			dsp->fRec4[i4] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i5;
		for (i5 = 0; (i5 < 3); i5 = (i5 + 1)) {
			dsp->fRec7[i5] = 0.f;
			
		}
		
	}
	dsp->fConst9 = (0.f - dsp->fConst7);
	/* C99 loop */
	{
		int i6;
		for (i6 = 0; (i6 < 2); i6 = (i6 + 1)) {
			dsp->fRec6[i6] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i7;
		for (i7 = 0; (i7 < 2); i7 = (i7 + 1)) {
			dsp->fRec5[i7] = 0.f;
			
		}
		
	}
	dsp->fConst10 = tanf((140.956f / (float)dsp->iConst0));
	dsp->fConst11 = (1.f / dsp->fConst10);
	dsp->fConst12 = (2.f * (1.f - (1.f / faustpower2_f(dsp->fConst10))));
	/* C99 loop */
	{
		int i8;
		for (i8 = 0; (i8 < 3); i8 = (i8 + 1)) {
			dsp->fRec8[i8] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i9;
		for (i9 = 0; (i9 < 3); i9 = (i9 + 1)) {
			dsp->fRec11[i9] = 0.f;
			
		}
		
	}
	dsp->fConst13 = (0.f - dsp->fConst11);
	/* C99 loop */
	{
		int i10;
		for (i10 = 0; (i10 < 2); i10 = (i10 + 1)) {
			dsp->fRec10[i10] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i11;
		for (i11 = 0; (i11 < 2); i11 = (i11 + 1)) {
			dsp->fRec9[i11] = 0.f;
			
		}
		
	}
	dsp->fConst14 = tanf((171.297f / (float)dsp->iConst0));
	dsp->fConst15 = (1.f / dsp->fConst14);
	dsp->fConst16 = (2.f * (1.f - (1.f / faustpower2_f(dsp->fConst14))));
	/* C99 loop */
	{
		int i12;
		for (i12 = 0; (i12 < 3); i12 = (i12 + 1)) {
			dsp->fRec12[i12] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i13;
		for (i13 = 0; (i13 < 3); i13 = (i13 + 1)) {
			dsp->fRec15[i13] = 0.f;
			
		}
		
	}
	dsp->fConst17 = (0.f - dsp->fConst15);
	/* C99 loop */
	{
		int i14;
		for (i14 = 0; (i14 < 2); i14 = (i14 + 1)) {
			dsp->fRec14[i14] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i15;
		for (i15 = 0; (i15 < 2); i15 = (i15 + 1)) {
			dsp->fRec13[i15] = 0.f;
			
		}
		
	}
	dsp->fConst18 = tanf((208.168f / (float)dsp->iConst0));
	dsp->fConst19 = (1.f / dsp->fConst18);
	dsp->fConst20 = (2.f * (1.f - (1.f / faustpower2_f(dsp->fConst18))));
	/* C99 loop */
	{
		int i16;
		for (i16 = 0; (i16 < 3); i16 = (i16 + 1)) {
			dsp->fRec16[i16] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i17;
		for (i17 = 0; (i17 < 3); i17 = (i17 + 1)) {
			dsp->fRec19[i17] = 0.f;
			
		}
		
	}
	dsp->fConst21 = (0.f - dsp->fConst19);
	/* C99 loop */
	{
		int i18;
		for (i18 = 0; (i18 < 2); i18 = (i18 + 1)) {
			dsp->fRec18[i18] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i19;
		for (i19 = 0; (i19 < 2); i19 = (i19 + 1)) {
			dsp->fRec17[i19] = 0.f;
			
		}
		
	}
	dsp->fConst22 = tanf((252.975f / (float)dsp->iConst0));
	dsp->fConst23 = (1.f / dsp->fConst22);
	dsp->fConst24 = (2.f * (1.f - (1.f / faustpower2_f(dsp->fConst22))));
	/* C99 loop */
	{
		int i20;
		for (i20 = 0; (i20 < 3); i20 = (i20 + 1)) {
			dsp->fRec20[i20] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i21;
		for (i21 = 0; (i21 < 3); i21 = (i21 + 1)) {
			dsp->fRec23[i21] = 0.f;
			
		}
		
	}
	dsp->fConst25 = (0.f - dsp->fConst23);
	/* C99 loop */
	{
		int i22;
		for (i22 = 0; (i22 < 2); i22 = (i22 + 1)) {
			dsp->fRec22[i22] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i23;
		for (i23 = 0; (i23 < 2); i23 = (i23 + 1)) {
			dsp->fRec21[i23] = 0.f;
			
		}
		
	}
	dsp->fConst26 = tanf((307.427f / (float)dsp->iConst0));
	dsp->fConst27 = (1.f / dsp->fConst26);
	dsp->fConst28 = (2.f * (1.f - (1.f / faustpower2_f(dsp->fConst26))));
	/* C99 loop */
	{
		int i24;
		for (i24 = 0; (i24 < 3); i24 = (i24 + 1)) {
			dsp->fRec24[i24] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i25;
		for (i25 = 0; (i25 < 3); i25 = (i25 + 1)) {
			dsp->fRec27[i25] = 0.f;
			
		}
		
	}
	dsp->fConst29 = (0.f - dsp->fConst27);
	/* C99 loop */
	{
		int i26;
		for (i26 = 0; (i26 < 2); i26 = (i26 + 1)) {
			dsp->fRec26[i26] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i27;
		for (i27 = 0; (i27 < 2); i27 = (i27 + 1)) {
			dsp->fRec25[i27] = 0.f;
			
		}
		
	}
	dsp->fConst30 = tanf((373.6f / (float)dsp->iConst0));
	dsp->fConst31 = (1.f / dsp->fConst30);
	dsp->fConst32 = (2.f * (1.f - (1.f / faustpower2_f(dsp->fConst30))));
	/* C99 loop */
	{
		int i28;
		for (i28 = 0; (i28 < 3); i28 = (i28 + 1)) {
			dsp->fRec28[i28] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i29;
		for (i29 = 0; (i29 < 3); i29 = (i29 + 1)) {
			dsp->fRec31[i29] = 0.f;
			
		}
		
	}
	dsp->fConst33 = (0.f - dsp->fConst31);
	/* C99 loop */
	{
		int i30;
		for (i30 = 0; (i30 < 2); i30 = (i30 + 1)) {
			dsp->fRec30[i30] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i31;
		for (i31 = 0; (i31 < 2); i31 = (i31 + 1)) {
			dsp->fRec29[i31] = 0.f;
			
		}
		
	}
	dsp->fConst34 = tanf((454.017f / (float)dsp->iConst0));
	dsp->fConst35 = (1.f / dsp->fConst34);
	dsp->fConst36 = (2.f * (1.f - (1.f / faustpower2_f(dsp->fConst34))));
	/* C99 loop */
	{
		int i32;
		for (i32 = 0; (i32 < 3); i32 = (i32 + 1)) {
			dsp->fRec32[i32] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i33;
		for (i33 = 0; (i33 < 3); i33 = (i33 + 1)) {
			dsp->fRec35[i33] = 0.f;
			
		}
		
	}
	dsp->fConst37 = (0.f - dsp->fConst35);
	/* C99 loop */
	{
		int i34;
		for (i34 = 0; (i34 < 2); i34 = (i34 + 1)) {
			dsp->fRec34[i34] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i35;
		for (i35 = 0; (i35 < 2); i35 = (i35 + 1)) {
			dsp->fRec33[i35] = 0.f;
			
		}
		
	}
	dsp->fConst38 = tanf((551.743f / (float)dsp->iConst0));
	dsp->fConst39 = (1.f / dsp->fConst38);
	dsp->fConst40 = (2.f * (1.f - (1.f / faustpower2_f(dsp->fConst38))));
	/* C99 loop */
	{
		int i36;
		for (i36 = 0; (i36 < 3); i36 = (i36 + 1)) {
			dsp->fRec36[i36] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i37;
		for (i37 = 0; (i37 < 3); i37 = (i37 + 1)) {
			dsp->fRec39[i37] = 0.f;
			
		}
		
	}
	dsp->fConst41 = (0.f - dsp->fConst39);
	/* C99 loop */
	{
		int i38;
		for (i38 = 0; (i38 < 2); i38 = (i38 + 1)) {
			dsp->fRec38[i38] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i39;
		for (i39 = 0; (i39 < 2); i39 = (i39 + 1)) {
			dsp->fRec37[i39] = 0.f;
			
		}
		
	}
	dsp->fConst42 = tanf((670.504f / (float)dsp->iConst0));
	dsp->fConst43 = (1.f / dsp->fConst42);
	dsp->fConst44 = (2.f * (1.f - (1.f / faustpower2_f(dsp->fConst42))));
	/* C99 loop */
	{
		int i40;
		for (i40 = 0; (i40 < 3); i40 = (i40 + 1)) {
			dsp->fRec40[i40] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i41;
		for (i41 = 0; (i41 < 3); i41 = (i41 + 1)) {
			dsp->fRec43[i41] = 0.f;
			
		}
		
	}
	dsp->fConst45 = (0.f - dsp->fConst43);
	/* C99 loop */
	{
		int i42;
		for (i42 = 0; (i42 < 2); i42 = (i42 + 1)) {
			dsp->fRec42[i42] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i43;
		for (i43 = 0; (i43 < 2); i43 = (i43 + 1)) {
			dsp->fRec41[i43] = 0.f;
			
		}
		
	}
	dsp->fConst46 = tanf((814.828f / (float)dsp->iConst0));
	dsp->fConst47 = (1.f / dsp->fConst46);
	dsp->fConst48 = (2.f * (1.f - (1.f / faustpower2_f(dsp->fConst46))));
	/* C99 loop */
	{
		int i44;
		for (i44 = 0; (i44 < 3); i44 = (i44 + 1)) {
			dsp->fRec44[i44] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i45;
		for (i45 = 0; (i45 < 3); i45 = (i45 + 1)) {
			dsp->fRec47[i45] = 0.f;
			
		}
		
	}
	dsp->fConst49 = (0.f - dsp->fConst47);
	/* C99 loop */
	{
		int i46;
		for (i46 = 0; (i46 < 2); i46 = (i46 + 1)) {
			dsp->fRec46[i46] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i47;
		for (i47 = 0; (i47 < 2); i47 = (i47 + 1)) {
			dsp->fRec45[i47] = 0.f;
			
		}
		
	}
	dsp->fConst50 = tanf((990.218f / (float)dsp->iConst0));
	dsp->fConst51 = (1.f / dsp->fConst50);
	dsp->fConst52 = (2.f * (1.f - (1.f / faustpower2_f(dsp->fConst50))));
	/* C99 loop */
	{
		int i48;
		for (i48 = 0; (i48 < 3); i48 = (i48 + 1)) {
			dsp->fRec48[i48] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i49;
		for (i49 = 0; (i49 < 3); i49 = (i49 + 1)) {
			dsp->fRec51[i49] = 0.f;
			
		}
		
	}
	dsp->fConst53 = (0.f - dsp->fConst51);
	/* C99 loop */
	{
		int i50;
		for (i50 = 0; (i50 < 2); i50 = (i50 + 1)) {
			dsp->fRec50[i50] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i51;
		for (i51 = 0; (i51 < 2); i51 = (i51 + 1)) {
			dsp->fRec49[i51] = 0.f;
			
		}
		
	}
	dsp->fConst54 = tanf((1203.36f / (float)dsp->iConst0));
	dsp->fConst55 = (1.f / dsp->fConst54);
	dsp->fConst56 = (2.f * (1.f - (1.f / faustpower2_f(dsp->fConst54))));
	/* C99 loop */
	{
		int i52;
		for (i52 = 0; (i52 < 3); i52 = (i52 + 1)) {
			dsp->fRec52[i52] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i53;
		for (i53 = 0; (i53 < 3); i53 = (i53 + 1)) {
			dsp->fRec55[i53] = 0.f;
			
		}
		
	}
	dsp->fConst57 = (0.f - dsp->fConst55);
	/* C99 loop */
	{
		int i54;
		for (i54 = 0; (i54 < 2); i54 = (i54 + 1)) {
			dsp->fRec54[i54] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i55;
		for (i55 = 0; (i55 < 2); i55 = (i55 + 1)) {
			dsp->fRec53[i55] = 0.f;
			
		}
		
	}
	dsp->fConst58 = tanf((1462.38f / (float)dsp->iConst0));
	dsp->fConst59 = (1.f / dsp->fConst58);
	dsp->fConst60 = (2.f * (1.f - (1.f / faustpower2_f(dsp->fConst58))));
	/* C99 loop */
	{
		int i56;
		for (i56 = 0; (i56 < 3); i56 = (i56 + 1)) {
			dsp->fRec56[i56] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i57;
		for (i57 = 0; (i57 < 3); i57 = (i57 + 1)) {
			dsp->fRec59[i57] = 0.f;
			
		}
		
	}
	dsp->fConst61 = (0.f - dsp->fConst59);
	/* C99 loop */
	{
		int i58;
		for (i58 = 0; (i58 < 2); i58 = (i58 + 1)) {
			dsp->fRec58[i58] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i59;
		for (i59 = 0; (i59 < 2); i59 = (i59 + 1)) {
			dsp->fRec57[i59] = 0.f;
			
		}
		
	}
	dsp->fConst62 = tanf((1777.15f / (float)dsp->iConst0));
	dsp->fConst63 = (1.f / dsp->fConst62);
	dsp->fConst64 = (2.f * (1.f - (1.f / faustpower2_f(dsp->fConst62))));
	/* C99 loop */
	{
		int i60;
		for (i60 = 0; (i60 < 3); i60 = (i60 + 1)) {
			dsp->fRec60[i60] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i61;
		for (i61 = 0; (i61 < 3); i61 = (i61 + 1)) {
			dsp->fRec63[i61] = 0.f;
			
		}
		
	}
	dsp->fConst65 = (0.f - dsp->fConst63);
	/* C99 loop */
	{
		int i62;
		for (i62 = 0; (i62 < 2); i62 = (i62 + 1)) {
			dsp->fRec62[i62] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i63;
		for (i63 = 0; (i63 < 2); i63 = (i63 + 1)) {
			dsp->fRec61[i63] = 0.f;
			
		}
		
	}
	dsp->fConst66 = tanf((2159.68f / (float)dsp->iConst0));
	dsp->fConst67 = (1.f / dsp->fConst66);
	dsp->fConst68 = (2.f * (1.f - (1.f / faustpower2_f(dsp->fConst66))));
	/* C99 loop */
	{
		int i64;
		for (i64 = 0; (i64 < 3); i64 = (i64 + 1)) {
			dsp->fRec64[i64] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i65;
		for (i65 = 0; (i65 < 3); i65 = (i65 + 1)) {
			dsp->fRec67[i65] = 0.f;
			
		}
		
	}
	dsp->fConst69 = (0.f - dsp->fConst67);
	/* C99 loop */
	{
		int i66;
		for (i66 = 0; (i66 < 2); i66 = (i66 + 1)) {
			dsp->fRec66[i66] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i67;
		for (i67 = 0; (i67 < 2); i67 = (i67 + 1)) {
			dsp->fRec65[i67] = 0.f;
			
		}
		
	}
	dsp->fConst70 = tanf((2624.55f / (float)dsp->iConst0));
	dsp->fConst71 = (1.f / dsp->fConst70);
	dsp->fConst72 = (2.f * (1.f - (1.f / faustpower2_f(dsp->fConst70))));
	/* C99 loop */
	{
		int i68;
		for (i68 = 0; (i68 < 3); i68 = (i68 + 1)) {
			dsp->fRec68[i68] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i69;
		for (i69 = 0; (i69 < 3); i69 = (i69 + 1)) {
			dsp->fRec71[i69] = 0.f;
			
		}
		
	}
	dsp->fConst73 = (0.f - dsp->fConst71);
	/* C99 loop */
	{
		int i70;
		for (i70 = 0; (i70 < 2); i70 = (i70 + 1)) {
			dsp->fRec70[i70] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i71;
		for (i71 = 0; (i71 < 2); i71 = (i71 + 1)) {
			dsp->fRec69[i71] = 0.f;
			
		}
		
	}
	dsp->fConst74 = tanf((3189.47f / (float)dsp->iConst0));
	dsp->fConst75 = (1.f / dsp->fConst74);
	dsp->fConst76 = (2.f * (1.f - (1.f / faustpower2_f(dsp->fConst74))));
	/* C99 loop */
	{
		int i72;
		for (i72 = 0; (i72 < 3); i72 = (i72 + 1)) {
			dsp->fRec72[i72] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i73;
		for (i73 = 0; (i73 < 3); i73 = (i73 + 1)) {
			dsp->fRec75[i73] = 0.f;
			
		}
		
	}
	dsp->fConst77 = (0.f - dsp->fConst75);
	/* C99 loop */
	{
		int i74;
		for (i74 = 0; (i74 < 2); i74 = (i74 + 1)) {
			dsp->fRec74[i74] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i75;
		for (i75 = 0; (i75 < 2); i75 = (i75 + 1)) {
			dsp->fRec73[i75] = 0.f;
			
		}
		
	}
	dsp->fConst78 = tanf((3876.f / (float)dsp->iConst0));
	dsp->fConst79 = (1.f / dsp->fConst78);
	dsp->fConst80 = (2.f * (1.f - (1.f / faustpower2_f(dsp->fConst78))));
	/* C99 loop */
	{
		int i76;
		for (i76 = 0; (i76 < 3); i76 = (i76 + 1)) {
			dsp->fRec76[i76] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i77;
		for (i77 = 0; (i77 < 3); i77 = (i77 + 1)) {
			dsp->fRec79[i77] = 0.f;
			
		}
		
	}
	dsp->fConst81 = (0.f - dsp->fConst79);
	/* C99 loop */
	{
		int i78;
		for (i78 = 0; (i78 < 2); i78 = (i78 + 1)) {
			dsp->fRec78[i78] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i79;
		for (i79 = 0; (i79 < 2); i79 = (i79 + 1)) {
			dsp->fRec77[i79] = 0.f;
			
		}
		
	}
	dsp->fConst82 = tanf((4710.3f / (float)dsp->iConst0));
	dsp->fConst83 = (1.f / dsp->fConst82);
	dsp->fConst84 = (2.f * (1.f - (1.f / faustpower2_f(dsp->fConst82))));
	/* C99 loop */
	{
		int i80;
		for (i80 = 0; (i80 < 3); i80 = (i80 + 1)) {
			dsp->fRec80[i80] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i81;
		for (i81 = 0; (i81 < 3); i81 = (i81 + 1)) {
			dsp->fRec83[i81] = 0.f;
			
		}
		
	}
	dsp->fConst85 = (0.f - dsp->fConst83);
	/* C99 loop */
	{
		int i82;
		for (i82 = 0; (i82 < 2); i82 = (i82 + 1)) {
			dsp->fRec82[i82] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i83;
		for (i83 = 0; (i83 < 2); i83 = (i83 + 1)) {
			dsp->fRec81[i83] = 0.f;
			
		}
		
	}
	dsp->fConst86 = tanf((5724.18f / (float)dsp->iConst0));
	dsp->fConst87 = (1.f / dsp->fConst86);
	dsp->fConst88 = (2.f * (1.f - (1.f / faustpower2_f(dsp->fConst86))));
	/* C99 loop */
	{
		int i84;
		for (i84 = 0; (i84 < 3); i84 = (i84 + 1)) {
			dsp->fRec84[i84] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i85;
		for (i85 = 0; (i85 < 3); i85 = (i85 + 1)) {
			dsp->fRec87[i85] = 0.f;
			
		}
		
	}
	dsp->fConst89 = (0.f - dsp->fConst87);
	/* C99 loop */
	{
		int i86;
		for (i86 = 0; (i86 < 2); i86 = (i86 + 1)) {
			dsp->fRec86[i86] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i87;
		for (i87 = 0; (i87 < 2); i87 = (i87 + 1)) {
			dsp->fRec85[i87] = 0.f;
			
		}
		
	}
	dsp->fConst90 = tanf((6956.29f / (float)dsp->iConst0));
	dsp->fConst91 = (1.f / dsp->fConst90);
	dsp->fConst92 = (2.f * (1.f - (1.f / faustpower2_f(dsp->fConst90))));
	/* C99 loop */
	{
		int i88;
		for (i88 = 0; (i88 < 3); i88 = (i88 + 1)) {
			dsp->fRec88[i88] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i89;
		for (i89 = 0; (i89 < 3); i89 = (i89 + 1)) {
			dsp->fRec91[i89] = 0.f;
			
		}
		
	}
	dsp->fConst93 = (0.f - dsp->fConst91);
	/* C99 loop */
	{
		int i90;
		for (i90 = 0; (i90 < 2); i90 = (i90 + 1)) {
			dsp->fRec90[i90] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i91;
		for (i91 = 0; (i91 < 2); i91 = (i91 + 1)) {
			dsp->fRec89[i91] = 0.f;
			
		}
		
	}
	dsp->fConst94 = tanf((8453.61f / (float)dsp->iConst0));
	dsp->fConst95 = (1.f / dsp->fConst94);
	dsp->fConst96 = (2.f * (1.f - (1.f / faustpower2_f(dsp->fConst94))));
	/* C99 loop */
	{
		int i92;
		for (i92 = 0; (i92 < 3); i92 = (i92 + 1)) {
			dsp->fRec92[i92] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i93;
		for (i93 = 0; (i93 < 3); i93 = (i93 + 1)) {
			dsp->fRec95[i93] = 0.f;
			
		}
		
	}
	dsp->fConst97 = (0.f - dsp->fConst95);
	/* C99 loop */
	{
		int i94;
		for (i94 = 0; (i94 < 2); i94 = (i94 + 1)) {
			dsp->fRec94[i94] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i95;
		for (i95 = 0; (i95 < 2); i95 = (i95 + 1)) {
			dsp->fRec93[i95] = 0.f;
			
		}
		
	}
	dsp->fConst98 = tanf((10273.2f / (float)dsp->iConst0));
	dsp->fConst99 = (1.f / dsp->fConst98);
	dsp->fConst100 = (2.f * (1.f - (1.f / faustpower2_f(dsp->fConst98))));
	/* C99 loop */
	{
		int i96;
		for (i96 = 0; (i96 < 3); i96 = (i96 + 1)) {
			dsp->fRec96[i96] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i97;
		for (i97 = 0; (i97 < 3); i97 = (i97 + 1)) {
			dsp->fRec99[i97] = 0.f;
			
		}
		
	}
	dsp->fConst101 = (0.f - dsp->fConst99);
	/* C99 loop */
	{
		int i98;
		for (i98 = 0; (i98 < 2); i98 = (i98 + 1)) {
			dsp->fRec98[i98] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i99;
		for (i99 = 0; (i99 < 2); i99 = (i99 + 1)) {
			dsp->fRec97[i99] = 0.f;
			
		}
		
	}
	dsp->fConst102 = tanf((12484.5f / (float)dsp->iConst0));
	dsp->fConst103 = (1.f / dsp->fConst102);
	dsp->fConst104 = (2.f * (1.f - (1.f / faustpower2_f(dsp->fConst102))));
	/* C99 loop */
	{
		int i100;
		for (i100 = 0; (i100 < 3); i100 = (i100 + 1)) {
			dsp->fRec100[i100] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i101;
		for (i101 = 0; (i101 < 3); i101 = (i101 + 1)) {
			dsp->fRec103[i101] = 0.f;
			
		}
		
	}
	dsp->fConst105 = (0.f - dsp->fConst103);
	/* C99 loop */
	{
		int i102;
		for (i102 = 0; (i102 < 2); i102 = (i102 + 1)) {
			dsp->fRec102[i102] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i103;
		for (i103 = 0; (i103 < 2); i103 = (i103 + 1)) {
			dsp->fRec101[i103] = 0.f;
			
		}
		
	}
	dsp->fConst106 = tanf((15171.8f / (float)dsp->iConst0));
	dsp->fConst107 = (1.f / dsp->fConst106);
	dsp->fConst108 = (2.f * (1.f - (1.f / faustpower2_f(dsp->fConst106))));
	/* C99 loop */
	{
		int i104;
		for (i104 = 0; (i104 < 3); i104 = (i104 + 1)) {
			dsp->fRec104[i104] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i105;
		for (i105 = 0; (i105 < 3); i105 = (i105 + 1)) {
			dsp->fRec107[i105] = 0.f;
			
		}
		
	}
	dsp->fConst109 = (0.f - dsp->fConst107);
	/* C99 loop */
	{
		int i106;
		for (i106 = 0; (i106 < 2); i106 = (i106 + 1)) {
			dsp->fRec106[i106] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i107;
		for (i107 = 0; (i107 < 2); i107 = (i107 + 1)) {
			dsp->fRec105[i107] = 0.f;
			
		}
		
	}
	dsp->fConst110 = tanf((18437.5f / (float)dsp->iConst0));
	dsp->fConst111 = (1.f / dsp->fConst110);
	dsp->fConst112 = (2.f * (1.f - (1.f / faustpower2_f(dsp->fConst110))));
	/* C99 loop */
	{
		int i108;
		for (i108 = 0; (i108 < 3); i108 = (i108 + 1)) {
			dsp->fRec108[i108] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i109;
		for (i109 = 0; (i109 < 3); i109 = (i109 + 1)) {
			dsp->fRec111[i109] = 0.f;
			
		}
		
	}
	dsp->fConst113 = (0.f - dsp->fConst111);
	/* C99 loop */
	{
		int i110;
		for (i110 = 0; (i110 < 2); i110 = (i110 + 1)) {
			dsp->fRec110[i110] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i111;
		for (i111 = 0; (i111 < 2); i111 = (i111 + 1)) {
			dsp->fRec109[i111] = 0.f;
			
		}
		
	}
	dsp->fConst114 = tanf((22406.1f / (float)dsp->iConst0));
	dsp->fConst115 = (1.f / dsp->fConst114);
	dsp->fConst116 = (2.f * (1.f - (1.f / faustpower2_f(dsp->fConst114))));
	/* C99 loop */
	{
		int i112;
		for (i112 = 0; (i112 < 3); i112 = (i112 + 1)) {
			dsp->fRec112[i112] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i113;
		for (i113 = 0; (i113 < 3); i113 = (i113 + 1)) {
			dsp->fRec115[i113] = 0.f;
			
		}
		
	}
	dsp->fConst117 = (0.f - dsp->fConst115);
	/* C99 loop */
	{
		int i114;
		for (i114 = 0; (i114 < 2); i114 = (i114 + 1)) {
			dsp->fRec114[i114] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i115;
		for (i115 = 0; (i115 < 2); i115 = (i115 + 1)) {
			dsp->fRec113[i115] = 0.f;
			
		}
		
	}
	dsp->fConst118 = tanf((27228.9f / (float)dsp->iConst0));
	dsp->fConst119 = (1.f / dsp->fConst118);
	dsp->fConst120 = (2.f * (1.f - (1.f / faustpower2_f(dsp->fConst118))));
	/* C99 loop */
	{
		int i116;
		for (i116 = 0; (i116 < 3); i116 = (i116 + 1)) {
			dsp->fRec116[i116] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i117;
		for (i117 = 0; (i117 < 3); i117 = (i117 + 1)) {
			dsp->fRec119[i117] = 0.f;
			
		}
		
	}
	dsp->fConst121 = (0.f - dsp->fConst119);
	/* C99 loop */
	{
		int i118;
		for (i118 = 0; (i118 < 2); i118 = (i118 + 1)) {
			dsp->fRec118[i118] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i119;
		for (i119 = 0; (i119 < 2); i119 = (i119 + 1)) {
			dsp->fRec117[i119] = 0.f;
			
		}
		
	}
	dsp->fConst122 = tanf((33089.9f / (float)dsp->iConst0));
	dsp->fConst123 = (1.f / dsp->fConst122);
	dsp->fConst124 = (2.f * (1.f - (1.f / faustpower2_f(dsp->fConst122))));
	/* C99 loop */
	{
		int i120;
		for (i120 = 0; (i120 < 3); i120 = (i120 + 1)) {
			dsp->fRec120[i120] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i121;
		for (i121 = 0; (i121 < 3); i121 = (i121 + 1)) {
			dsp->fRec123[i121] = 0.f;
			
		}
		
	}
	dsp->fConst125 = (0.f - dsp->fConst123);
	/* C99 loop */
	{
		int i122;
		for (i122 = 0; (i122 < 2); i122 = (i122 + 1)) {
			dsp->fRec122[i122] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i123;
		for (i123 = 0; (i123 < 2); i123 = (i123 + 1)) {
			dsp->fRec121[i123] = 0.f;
			
		}
		
	}
	dsp->fConst126 = tanf((40212.4f / (float)dsp->iConst0));
	dsp->fConst127 = (1.f / dsp->fConst126);
	dsp->fConst128 = (2.f * (1.f - (1.f / faustpower2_f(dsp->fConst126))));
	/* C99 loop */
	{
		int i124;
		for (i124 = 0; (i124 < 3); i124 = (i124 + 1)) {
			dsp->fRec124[i124] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i125;
		for (i125 = 0; (i125 < 3); i125 = (i125 + 1)) {
			dsp->fRec127[i125] = 0.f;
			
		}
		
	}
	dsp->fConst129 = (0.f - dsp->fConst127);
	/* C99 loop */
	{
		int i126;
		for (i126 = 0; (i126 < 2); i126 = (i126 + 1)) {
			dsp->fRec126[i126] = 0.f;
			
		}
		
	}
	/* C99 loop */
	{
		int i127;
		for (i127 = 0; (i127 < 2); i127 = (i127 + 1)) {
			dsp->fRec125[i127] = 0.f;
			
		}
		
	}
	
}

static void initvocoder(vocoder* dsp, int samplingFreq) {
	instanceInitvocoder(dsp, samplingFreq);
}

static void buildUserInterfacevocoder(vocoder* dsp, UIGlue* interface) {
	interface->addHorizontalSlider(interface->uiInterface, "atk", &dsp->fHslider1, 0.01f, 0.0001f, 0.5f, 1e-05f);
	interface->addHorizontalSlider(interface->uiInterface, "rel", &dsp->fHslider2, 0.01f, 0.0001f, 0.5f, 1e-05f);
	interface->addHorizontalSlider(interface->uiInterface, "bwratio", &dsp->fHslider0, 0.5f, 0.1f, 2.f, 0.001f);
	
}

static void computevocoder(vocoder* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* input0 = inputs[0];
	FAUSTFLOAT* input1 = inputs[1];
	FAUSTFLOAT* output0 = outputs[0];
	float fSlow0 = (float)dsp->fHslider0;
	float fSlow1 = (0.354245f * fSlow0);
	float fSlow2 = (1.f / (1.f + (dsp->fConst2 * (fSlow1 + dsp->fConst2))));
	float fSlow3 = (1.f + (dsp->fConst2 * (dsp->fConst2 - fSlow1)));
	float fSlow4 = expf((0.f - (dsp->fConst5 / (float)dsp->fHslider1)));
	float fSlow5 = expf((0.f - (dsp->fConst5 / (float)dsp->fHslider2)));
	float fSlow6 = (0.354245f * fSlow0);
	float fSlow7 = (1.f / (1.f + (dsp->fConst7 * (fSlow6 + dsp->fConst7))));
	float fSlow8 = (1.f + (dsp->fConst7 * (dsp->fConst7 - fSlow6)));
	float fSlow9 = (1.f / (1.f + (dsp->fConst11 * (fSlow1 + dsp->fConst11))));
	float fSlow10 = (1.f + (dsp->fConst11 * (dsp->fConst11 - fSlow1)));
	float fSlow11 = (0.354245f * fSlow0);
	float fSlow12 = (1.f / (1.f + (dsp->fConst15 * (fSlow11 + dsp->fConst15))));
	float fSlow13 = (1.f + (dsp->fConst15 * (dsp->fConst15 - fSlow11)));
	float fSlow14 = (0.354245f * fSlow0);
	float fSlow15 = (1.f / (1.f + (dsp->fConst19 * (fSlow14 + dsp->fConst19))));
	float fSlow16 = (1.f + (dsp->fConst19 * (dsp->fConst19 - fSlow14)));
	float fSlow17 = (0.354245f * fSlow0);
	float fSlow18 = (1.f / (1.f + (dsp->fConst23 * (fSlow17 + dsp->fConst23))));
	float fSlow19 = (1.f + (dsp->fConst23 * (dsp->fConst23 - fSlow17)));
	float fSlow20 = (0.354245f * fSlow0);
	float fSlow21 = (1.f / (1.f + (dsp->fConst27 * (fSlow20 + dsp->fConst27))));
	float fSlow22 = (1.f + (dsp->fConst27 * (dsp->fConst27 - fSlow20)));
	float fSlow23 = (1.f / (1.f + (dsp->fConst31 * (fSlow1 + dsp->fConst31))));
	float fSlow24 = (1.f + (dsp->fConst31 * (dsp->fConst31 - fSlow1)));
	float fSlow25 = (1.f / (1.f + (dsp->fConst35 * (fSlow14 + dsp->fConst35))));
	float fSlow26 = (1.f + (dsp->fConst35 * (dsp->fConst35 - fSlow14)));
	float fSlow27 = (1.f / (1.f + (dsp->fConst39 * (fSlow6 + dsp->fConst39))));
	float fSlow28 = (1.f + (dsp->fConst39 * (dsp->fConst39 - fSlow6)));
	float fSlow29 = (0.354245f * fSlow0);
	float fSlow30 = (1.f / (1.f + (dsp->fConst43 * (fSlow29 + dsp->fConst43))));
	float fSlow31 = (1.f + (dsp->fConst43 * (dsp->fConst43 - fSlow29)));
	float fSlow32 = (0.354245f * fSlow0);
	float fSlow33 = (1.f / (1.f + (dsp->fConst47 * (fSlow32 + dsp->fConst47))));
	float fSlow34 = (1.f + (dsp->fConst47 * (dsp->fConst47 - fSlow32)));
	float fSlow35 = (1.f / (1.f + (dsp->fConst51 * (fSlow29 + dsp->fConst51))));
	float fSlow36 = (1.f + (dsp->fConst51 * (dsp->fConst51 - fSlow29)));
	float fSlow37 = (0.354245f * fSlow0);
	float fSlow38 = (1.f / (1.f + (dsp->fConst55 * (fSlow37 + dsp->fConst55))));
	float fSlow39 = (1.f + (dsp->fConst55 * (dsp->fConst55 - fSlow37)));
	float fSlow40 = (1.f / (1.f + (dsp->fConst59 * (fSlow11 + dsp->fConst59))));
	float fSlow41 = (1.f + (dsp->fConst59 * (dsp->fConst59 - fSlow11)));
	float fSlow42 = (1.f / (1.f + (dsp->fConst63 * (fSlow11 + dsp->fConst63))));
	float fSlow43 = (1.f + (dsp->fConst63 * (dsp->fConst63 - fSlow11)));
	float fSlow44 = (1.f / (1.f + (dsp->fConst67 * (fSlow6 + dsp->fConst67))));
	float fSlow45 = (1.f + (dsp->fConst67 * (dsp->fConst67 - fSlow6)));
	float fSlow46 = (0.354245f * fSlow0);
	float fSlow47 = (1.f / (1.f + (dsp->fConst71 * (fSlow46 + dsp->fConst71))));
	float fSlow48 = (1.f + (dsp->fConst71 * (dsp->fConst71 - fSlow46)));
	float fSlow49 = (1.f / (1.f + (dsp->fConst75 * (fSlow14 + dsp->fConst75))));
	float fSlow50 = (1.f + (dsp->fConst75 * (dsp->fConst75 - fSlow14)));
	float fSlow51 = (1.f / (1.f + (dsp->fConst79 * (fSlow37 + dsp->fConst79))));
	float fSlow52 = (1.f + (dsp->fConst79 * (dsp->fConst79 - fSlow37)));
	float fSlow53 = (1.f / (1.f + (dsp->fConst83 * (fSlow20 + dsp->fConst83))));
	float fSlow54 = (1.f + (dsp->fConst83 * (dsp->fConst83 - fSlow20)));
	float fSlow55 = (1.f / (1.f + (dsp->fConst87 * (fSlow37 + dsp->fConst87))));
	float fSlow56 = (1.f + (dsp->fConst87 * (dsp->fConst87 - fSlow37)));
	float fSlow57 = (1.f / (1.f + (dsp->fConst91 * (fSlow20 + dsp->fConst91))));
	float fSlow58 = (1.f + (dsp->fConst91 * (dsp->fConst91 - fSlow20)));
	float fSlow59 = (0.354245f * fSlow0);
	float fSlow60 = (1.f / (1.f + (dsp->fConst95 * (fSlow59 + dsp->fConst95))));
	float fSlow61 = (1.f + (dsp->fConst95 * (dsp->fConst95 - fSlow59)));
	float fSlow62 = (1.f / (1.f + (dsp->fConst99 * (fSlow11 + dsp->fConst99))));
	float fSlow63 = (1.f + (dsp->fConst99 * (dsp->fConst99 - fSlow11)));
	float fSlow64 = (1.f / (1.f + (dsp->fConst103 * (fSlow1 + dsp->fConst103))));
	float fSlow65 = (1.f + (dsp->fConst103 * (dsp->fConst103 - fSlow1)));
	float fSlow66 = (1.f / (1.f + (dsp->fConst107 * (fSlow29 + dsp->fConst107))));
	float fSlow67 = (1.f + (dsp->fConst107 * (dsp->fConst107 - fSlow29)));
	float fSlow68 = (0.354245f * fSlow0);
	float fSlow69 = (1.f / (1.f + (dsp->fConst111 * (fSlow68 + dsp->fConst111))));
	float fSlow70 = (1.f + (dsp->fConst111 * (dsp->fConst111 - fSlow68)));
	float fSlow71 = (1.f / (1.f + (dsp->fConst115 * (fSlow1 + dsp->fConst115))));
	float fSlow72 = (1.f + (dsp->fConst115 * (dsp->fConst115 - fSlow1)));
	float fSlow73 = (1.f / (1.f + (dsp->fConst119 * (fSlow37 + dsp->fConst119))));
	float fSlow74 = (1.f + (dsp->fConst119 * (dsp->fConst119 - fSlow37)));
	float fSlow75 = (0.354245f * fSlow0);
	float fSlow76 = (1.f / (1.f + (dsp->fConst123 * (fSlow75 + dsp->fConst123))));
	float fSlow77 = (1.f + (dsp->fConst123 * (dsp->fConst123 - fSlow75)));
	float fSlow78 = (1.f / (1.f + (dsp->fConst127 * (fSlow59 + dsp->fConst127))));
	float fSlow79 = (1.f + (dsp->fConst127 * (dsp->fConst127 - fSlow59)));
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = (float)input1[i];
			dsp->fRec0[0] = (fTemp0 - (fSlow2 * ((fSlow3 * dsp->fRec0[2]) + (dsp->fConst3 * dsp->fRec0[1]))));
			float fTemp1 = (float)input0[i];
			dsp->fRec3[0] = (fTemp1 - (fSlow2 * ((fSlow3 * dsp->fRec3[2]) + (dsp->fConst3 * dsp->fRec3[1]))));
			float fTemp2 = fabsf((fSlow2 * ((dsp->fConst2 * dsp->fRec3[0]) + (dsp->fConst4 * dsp->fRec3[2]))));
			float fTemp3 = ((dsp->fRec1[1] > fTemp2)?fSlow5:fSlow4);
			dsp->fRec2[0] = ((dsp->fRec2[1] * fTemp3) + (fTemp2 * (1.f - fTemp3)));
			dsp->fRec1[0] = dsp->fRec2[0];
			dsp->fRec4[0] = (fTemp0 - (fSlow7 * ((fSlow8 * dsp->fRec4[2]) + (dsp->fConst8 * dsp->fRec4[1]))));
			dsp->fRec7[0] = (fTemp1 - (fSlow7 * ((fSlow8 * dsp->fRec7[2]) + (dsp->fConst8 * dsp->fRec7[1]))));
			float fTemp4 = fabsf((fSlow7 * ((dsp->fConst7 * dsp->fRec7[0]) + (dsp->fConst9 * dsp->fRec7[2]))));
			float fTemp5 = ((dsp->fRec5[1] > fTemp4)?fSlow5:fSlow4);
			dsp->fRec6[0] = ((dsp->fRec6[1] * fTemp5) + (fTemp4 * (1.f - fTemp5)));
			dsp->fRec5[0] = dsp->fRec6[0];
			dsp->fRec8[0] = (fTemp0 - (fSlow9 * ((fSlow10 * dsp->fRec8[2]) + (dsp->fConst12 * dsp->fRec8[1]))));
			dsp->fRec11[0] = (fTemp1 - (fSlow9 * ((fSlow10 * dsp->fRec11[2]) + (dsp->fConst12 * dsp->fRec11[1]))));
			float fTemp6 = fabsf((fSlow9 * ((dsp->fConst11 * dsp->fRec11[0]) + (dsp->fConst13 * dsp->fRec11[2]))));
			float fTemp7 = ((dsp->fRec9[1] > fTemp6)?fSlow5:fSlow4);
			dsp->fRec10[0] = ((dsp->fRec10[1] * fTemp7) + (fTemp6 * (1.f - fTemp7)));
			dsp->fRec9[0] = dsp->fRec10[0];
			dsp->fRec12[0] = (fTemp0 - (fSlow12 * ((fSlow13 * dsp->fRec12[2]) + (dsp->fConst16 * dsp->fRec12[1]))));
			dsp->fRec15[0] = (fTemp1 - (fSlow12 * ((fSlow13 * dsp->fRec15[2]) + (dsp->fConst16 * dsp->fRec15[1]))));
			float fTemp8 = fabsf((fSlow12 * ((dsp->fConst15 * dsp->fRec15[0]) + (dsp->fConst17 * dsp->fRec15[2]))));
			float fTemp9 = ((dsp->fRec13[1] > fTemp8)?fSlow5:fSlow4);
			dsp->fRec14[0] = ((dsp->fRec14[1] * fTemp9) + (fTemp8 * (1.f - fTemp9)));
			dsp->fRec13[0] = dsp->fRec14[0];
			dsp->fRec16[0] = (fTemp0 - (fSlow15 * ((fSlow16 * dsp->fRec16[2]) + (dsp->fConst20 * dsp->fRec16[1]))));
			dsp->fRec19[0] = (fTemp1 - (fSlow15 * ((fSlow16 * dsp->fRec19[2]) + (dsp->fConst20 * dsp->fRec19[1]))));
			float fTemp10 = fabsf((fSlow15 * ((dsp->fConst19 * dsp->fRec19[0]) + (dsp->fConst21 * dsp->fRec19[2]))));
			float fTemp11 = ((dsp->fRec17[1] > fTemp10)?fSlow5:fSlow4);
			dsp->fRec18[0] = ((dsp->fRec18[1] * fTemp11) + (fTemp10 * (1.f - fTemp11)));
			dsp->fRec17[0] = dsp->fRec18[0];
			dsp->fRec20[0] = (fTemp0 - (fSlow18 * ((fSlow19 * dsp->fRec20[2]) + (dsp->fConst24 * dsp->fRec20[1]))));
			dsp->fRec23[0] = (fTemp1 - (fSlow18 * ((fSlow19 * dsp->fRec23[2]) + (dsp->fConst24 * dsp->fRec23[1]))));
			float fTemp12 = fabsf((fSlow18 * ((dsp->fConst23 * dsp->fRec23[0]) + (dsp->fConst25 * dsp->fRec23[2]))));
			float fTemp13 = ((dsp->fRec21[1] > fTemp12)?fSlow5:fSlow4);
			dsp->fRec22[0] = ((dsp->fRec22[1] * fTemp13) + (fTemp12 * (1.f - fTemp13)));
			dsp->fRec21[0] = dsp->fRec22[0];
			dsp->fRec24[0] = (fTemp0 - (fSlow21 * ((fSlow22 * dsp->fRec24[2]) + (dsp->fConst28 * dsp->fRec24[1]))));
			dsp->fRec27[0] = (fTemp1 - (fSlow21 * ((fSlow22 * dsp->fRec27[2]) + (dsp->fConst28 * dsp->fRec27[1]))));
			float fTemp14 = fabsf((fSlow21 * ((dsp->fConst27 * dsp->fRec27[0]) + (dsp->fConst29 * dsp->fRec27[2]))));
			float fTemp15 = ((dsp->fRec25[1] > fTemp14)?fSlow5:fSlow4);
			dsp->fRec26[0] = ((dsp->fRec26[1] * fTemp15) + (fTemp14 * (1.f - fTemp15)));
			dsp->fRec25[0] = dsp->fRec26[0];
			dsp->fRec28[0] = (fTemp0 - (fSlow23 * ((fSlow24 * dsp->fRec28[2]) + (dsp->fConst32 * dsp->fRec28[1]))));
			dsp->fRec31[0] = (fTemp1 - (fSlow23 * ((fSlow24 * dsp->fRec31[2]) + (dsp->fConst32 * dsp->fRec31[1]))));
			float fTemp16 = fabsf((fSlow23 * ((dsp->fConst31 * dsp->fRec31[0]) + (dsp->fConst33 * dsp->fRec31[2]))));
			float fTemp17 = ((dsp->fRec29[1] > fTemp16)?fSlow5:fSlow4);
			dsp->fRec30[0] = ((dsp->fRec30[1] * fTemp17) + (fTemp16 * (1.f - fTemp17)));
			dsp->fRec29[0] = dsp->fRec30[0];
			dsp->fRec32[0] = (fTemp0 - (fSlow25 * ((fSlow26 * dsp->fRec32[2]) + (dsp->fConst36 * dsp->fRec32[1]))));
			dsp->fRec35[0] = (fTemp1 - (fSlow25 * ((fSlow26 * dsp->fRec35[2]) + (dsp->fConst36 * dsp->fRec35[1]))));
			float fTemp18 = fabsf((fSlow25 * ((dsp->fConst35 * dsp->fRec35[0]) + (dsp->fConst37 * dsp->fRec35[2]))));
			float fTemp19 = ((dsp->fRec33[1] > fTemp18)?fSlow5:fSlow4);
			dsp->fRec34[0] = ((dsp->fRec34[1] * fTemp19) + (fTemp18 * (1.f - fTemp19)));
			dsp->fRec33[0] = dsp->fRec34[0];
			dsp->fRec36[0] = (fTemp0 - (fSlow27 * ((fSlow28 * dsp->fRec36[2]) + (dsp->fConst40 * dsp->fRec36[1]))));
			dsp->fRec39[0] = (fTemp1 - (fSlow27 * ((fSlow28 * dsp->fRec39[2]) + (dsp->fConst40 * dsp->fRec39[1]))));
			float fTemp20 = fabsf((fSlow27 * ((dsp->fConst39 * dsp->fRec39[0]) + (dsp->fConst41 * dsp->fRec39[2]))));
			float fTemp21 = ((dsp->fRec37[1] > fTemp20)?fSlow5:fSlow4);
			dsp->fRec38[0] = ((dsp->fRec38[1] * fTemp21) + (fTemp20 * (1.f - fTemp21)));
			dsp->fRec37[0] = dsp->fRec38[0];
			dsp->fRec40[0] = (fTemp0 - (fSlow30 * ((fSlow31 * dsp->fRec40[2]) + (dsp->fConst44 * dsp->fRec40[1]))));
			dsp->fRec43[0] = (fTemp1 - (fSlow30 * ((fSlow31 * dsp->fRec43[2]) + (dsp->fConst44 * dsp->fRec43[1]))));
			float fTemp22 = fabsf((fSlow30 * ((dsp->fConst43 * dsp->fRec43[0]) + (dsp->fConst45 * dsp->fRec43[2]))));
			float fTemp23 = ((dsp->fRec41[1] > fTemp22)?fSlow5:fSlow4);
			dsp->fRec42[0] = ((dsp->fRec42[1] * fTemp23) + (fTemp22 * (1.f - fTemp23)));
			dsp->fRec41[0] = dsp->fRec42[0];
			dsp->fRec44[0] = (fTemp0 - (fSlow33 * ((fSlow34 * dsp->fRec44[2]) + (dsp->fConst48 * dsp->fRec44[1]))));
			dsp->fRec47[0] = (fTemp1 - (fSlow33 * ((fSlow34 * dsp->fRec47[2]) + (dsp->fConst48 * dsp->fRec47[1]))));
			float fTemp24 = fabsf((fSlow33 * ((dsp->fConst47 * dsp->fRec47[0]) + (dsp->fConst49 * dsp->fRec47[2]))));
			float fTemp25 = ((dsp->fRec45[1] > fTemp24)?fSlow5:fSlow4);
			dsp->fRec46[0] = ((dsp->fRec46[1] * fTemp25) + (fTemp24 * (1.f - fTemp25)));
			dsp->fRec45[0] = dsp->fRec46[0];
			dsp->fRec48[0] = (fTemp0 - (fSlow35 * ((fSlow36 * dsp->fRec48[2]) + (dsp->fConst52 * dsp->fRec48[1]))));
			dsp->fRec51[0] = (fTemp1 - (fSlow35 * ((fSlow36 * dsp->fRec51[2]) + (dsp->fConst52 * dsp->fRec51[1]))));
			float fTemp26 = fabsf((fSlow35 * ((dsp->fConst51 * dsp->fRec51[0]) + (dsp->fConst53 * dsp->fRec51[2]))));
			float fTemp27 = ((dsp->fRec49[1] > fTemp26)?fSlow5:fSlow4);
			dsp->fRec50[0] = ((dsp->fRec50[1] * fTemp27) + (fTemp26 * (1.f - fTemp27)));
			dsp->fRec49[0] = dsp->fRec50[0];
			dsp->fRec52[0] = (fTemp0 - (fSlow38 * ((fSlow39 * dsp->fRec52[2]) + (dsp->fConst56 * dsp->fRec52[1]))));
			dsp->fRec55[0] = (fTemp1 - (fSlow38 * ((fSlow39 * dsp->fRec55[2]) + (dsp->fConst56 * dsp->fRec55[1]))));
			float fTemp28 = fabsf((fSlow38 * ((dsp->fConst55 * dsp->fRec55[0]) + (dsp->fConst57 * dsp->fRec55[2]))));
			float fTemp29 = ((dsp->fRec53[1] > fTemp28)?fSlow5:fSlow4);
			dsp->fRec54[0] = ((dsp->fRec54[1] * fTemp29) + (fTemp28 * (1.f - fTemp29)));
			dsp->fRec53[0] = dsp->fRec54[0];
			dsp->fRec56[0] = (fTemp0 - (fSlow40 * ((fSlow41 * dsp->fRec56[2]) + (dsp->fConst60 * dsp->fRec56[1]))));
			dsp->fRec59[0] = (fTemp1 - (fSlow40 * ((fSlow41 * dsp->fRec59[2]) + (dsp->fConst60 * dsp->fRec59[1]))));
			float fTemp30 = fabsf((fSlow40 * ((dsp->fConst59 * dsp->fRec59[0]) + (dsp->fConst61 * dsp->fRec59[2]))));
			float fTemp31 = ((dsp->fRec57[1] > fTemp30)?fSlow5:fSlow4);
			dsp->fRec58[0] = ((dsp->fRec58[1] * fTemp31) + (fTemp30 * (1.f - fTemp31)));
			dsp->fRec57[0] = dsp->fRec58[0];
			dsp->fRec60[0] = (fTemp0 - (fSlow42 * ((fSlow43 * dsp->fRec60[2]) + (dsp->fConst64 * dsp->fRec60[1]))));
			dsp->fRec63[0] = (fTemp1 - (fSlow42 * ((fSlow43 * dsp->fRec63[2]) + (dsp->fConst64 * dsp->fRec63[1]))));
			float fTemp32 = fabsf((fSlow42 * ((dsp->fConst63 * dsp->fRec63[0]) + (dsp->fConst65 * dsp->fRec63[2]))));
			float fTemp33 = ((dsp->fRec61[1] > fTemp32)?fSlow5:fSlow4);
			dsp->fRec62[0] = ((dsp->fRec62[1] * fTemp33) + (fTemp32 * (1.f - fTemp33)));
			dsp->fRec61[0] = dsp->fRec62[0];
			dsp->fRec64[0] = (fTemp0 - (fSlow44 * ((fSlow45 * dsp->fRec64[2]) + (dsp->fConst68 * dsp->fRec64[1]))));
			dsp->fRec67[0] = (fTemp1 - (fSlow44 * ((fSlow45 * dsp->fRec67[2]) + (dsp->fConst68 * dsp->fRec67[1]))));
			float fTemp34 = fabsf((fSlow44 * ((dsp->fConst67 * dsp->fRec67[0]) + (dsp->fConst69 * dsp->fRec67[2]))));
			float fTemp35 = ((dsp->fRec65[1] > fTemp34)?fSlow5:fSlow4);
			dsp->fRec66[0] = ((dsp->fRec66[1] * fTemp35) + (fTemp34 * (1.f - fTemp35)));
			dsp->fRec65[0] = dsp->fRec66[0];
			dsp->fRec68[0] = (fTemp0 - (fSlow47 * ((fSlow48 * dsp->fRec68[2]) + (dsp->fConst72 * dsp->fRec68[1]))));
			dsp->fRec71[0] = (fTemp1 - (fSlow47 * ((fSlow48 * dsp->fRec71[2]) + (dsp->fConst72 * dsp->fRec71[1]))));
			float fTemp36 = fabsf((fSlow47 * ((dsp->fConst71 * dsp->fRec71[0]) + (dsp->fConst73 * dsp->fRec71[2]))));
			float fTemp37 = ((dsp->fRec69[1] > fTemp36)?fSlow5:fSlow4);
			dsp->fRec70[0] = ((dsp->fRec70[1] * fTemp37) + (fTemp36 * (1.f - fTemp37)));
			dsp->fRec69[0] = dsp->fRec70[0];
			dsp->fRec72[0] = (fTemp0 - (fSlow49 * ((fSlow50 * dsp->fRec72[2]) + (dsp->fConst76 * dsp->fRec72[1]))));
			dsp->fRec75[0] = (fTemp1 - (fSlow49 * ((fSlow50 * dsp->fRec75[2]) + (dsp->fConst76 * dsp->fRec75[1]))));
			float fTemp38 = fabsf((fSlow49 * ((dsp->fConst75 * dsp->fRec75[0]) + (dsp->fConst77 * dsp->fRec75[2]))));
			float fTemp39 = ((dsp->fRec73[1] > fTemp38)?fSlow5:fSlow4);
			dsp->fRec74[0] = ((dsp->fRec74[1] * fTemp39) + (fTemp38 * (1.f - fTemp39)));
			dsp->fRec73[0] = dsp->fRec74[0];
			dsp->fRec76[0] = (fTemp0 - (fSlow51 * ((fSlow52 * dsp->fRec76[2]) + (dsp->fConst80 * dsp->fRec76[1]))));
			dsp->fRec79[0] = (fTemp1 - (fSlow51 * ((fSlow52 * dsp->fRec79[2]) + (dsp->fConst80 * dsp->fRec79[1]))));
			float fTemp40 = fabsf((fSlow51 * ((dsp->fConst79 * dsp->fRec79[0]) + (dsp->fConst81 * dsp->fRec79[2]))));
			float fTemp41 = ((dsp->fRec77[1] > fTemp40)?fSlow5:fSlow4);
			dsp->fRec78[0] = ((dsp->fRec78[1] * fTemp41) + (fTemp40 * (1.f - fTemp41)));
			dsp->fRec77[0] = dsp->fRec78[0];
			dsp->fRec80[0] = (fTemp0 - (fSlow53 * ((fSlow54 * dsp->fRec80[2]) + (dsp->fConst84 * dsp->fRec80[1]))));
			dsp->fRec83[0] = (fTemp1 - (fSlow53 * ((fSlow54 * dsp->fRec83[2]) + (dsp->fConst84 * dsp->fRec83[1]))));
			float fTemp42 = fabsf((fSlow53 * ((dsp->fConst83 * dsp->fRec83[0]) + (dsp->fConst85 * dsp->fRec83[2]))));
			float fTemp43 = ((dsp->fRec81[1] > fTemp42)?fSlow5:fSlow4);
			dsp->fRec82[0] = ((dsp->fRec82[1] * fTemp43) + (fTemp42 * (1.f - fTemp43)));
			dsp->fRec81[0] = dsp->fRec82[0];
			dsp->fRec84[0] = (fTemp0 - (fSlow55 * ((fSlow56 * dsp->fRec84[2]) + (dsp->fConst88 * dsp->fRec84[1]))));
			dsp->fRec87[0] = (fTemp1 - (fSlow55 * ((fSlow56 * dsp->fRec87[2]) + (dsp->fConst88 * dsp->fRec87[1]))));
			float fTemp44 = fabsf((fSlow55 * ((dsp->fConst87 * dsp->fRec87[0]) + (dsp->fConst89 * dsp->fRec87[2]))));
			float fTemp45 = ((dsp->fRec85[1] > fTemp44)?fSlow5:fSlow4);
			dsp->fRec86[0] = ((dsp->fRec86[1] * fTemp45) + (fTemp44 * (1.f - fTemp45)));
			dsp->fRec85[0] = dsp->fRec86[0];
			dsp->fRec88[0] = (fTemp0 - (fSlow57 * ((fSlow58 * dsp->fRec88[2]) + (dsp->fConst92 * dsp->fRec88[1]))));
			dsp->fRec91[0] = (fTemp1 - (fSlow57 * ((fSlow58 * dsp->fRec91[2]) + (dsp->fConst92 * dsp->fRec91[1]))));
			float fTemp46 = fabsf((fSlow57 * ((dsp->fConst91 * dsp->fRec91[0]) + (dsp->fConst93 * dsp->fRec91[2]))));
			float fTemp47 = ((dsp->fRec89[1] > fTemp46)?fSlow5:fSlow4);
			dsp->fRec90[0] = ((dsp->fRec90[1] * fTemp47) + (fTemp46 * (1.f - fTemp47)));
			dsp->fRec89[0] = dsp->fRec90[0];
			dsp->fRec92[0] = (fTemp0 - (fSlow60 * ((fSlow61 * dsp->fRec92[2]) + (dsp->fConst96 * dsp->fRec92[1]))));
			dsp->fRec95[0] = (fTemp1 - (fSlow60 * ((fSlow61 * dsp->fRec95[2]) + (dsp->fConst96 * dsp->fRec95[1]))));
			float fTemp48 = fabsf((fSlow60 * ((dsp->fConst95 * dsp->fRec95[0]) + (dsp->fConst97 * dsp->fRec95[2]))));
			float fTemp49 = ((dsp->fRec93[1] > fTemp48)?fSlow5:fSlow4);
			dsp->fRec94[0] = ((dsp->fRec94[1] * fTemp49) + (fTemp48 * (1.f - fTemp49)));
			dsp->fRec93[0] = dsp->fRec94[0];
			dsp->fRec96[0] = (fTemp0 - (fSlow62 * ((fSlow63 * dsp->fRec96[2]) + (dsp->fConst100 * dsp->fRec96[1]))));
			dsp->fRec99[0] = (fTemp1 - (fSlow62 * ((fSlow63 * dsp->fRec99[2]) + (dsp->fConst100 * dsp->fRec99[1]))));
			float fTemp50 = fabsf((fSlow62 * ((dsp->fConst99 * dsp->fRec99[0]) + (dsp->fConst101 * dsp->fRec99[2]))));
			float fTemp51 = ((dsp->fRec97[1] > fTemp50)?fSlow5:fSlow4);
			dsp->fRec98[0] = ((dsp->fRec98[1] * fTemp51) + (fTemp50 * (1.f - fTemp51)));
			dsp->fRec97[0] = dsp->fRec98[0];
			dsp->fRec100[0] = (fTemp0 - (fSlow64 * ((fSlow65 * dsp->fRec100[2]) + (dsp->fConst104 * dsp->fRec100[1]))));
			dsp->fRec103[0] = (fTemp1 - (fSlow64 * ((fSlow65 * dsp->fRec103[2]) + (dsp->fConst104 * dsp->fRec103[1]))));
			float fTemp52 = fabsf((fSlow64 * ((dsp->fConst103 * dsp->fRec103[0]) + (dsp->fConst105 * dsp->fRec103[2]))));
			float fTemp53 = ((dsp->fRec101[1] > fTemp52)?fSlow5:fSlow4);
			dsp->fRec102[0] = ((dsp->fRec102[1] * fTemp53) + (fTemp52 * (1.f - fTemp53)));
			dsp->fRec101[0] = dsp->fRec102[0];
			dsp->fRec104[0] = (fTemp0 - (fSlow66 * ((fSlow67 * dsp->fRec104[2]) + (dsp->fConst108 * dsp->fRec104[1]))));
			dsp->fRec107[0] = (fTemp1 - (fSlow66 * ((fSlow67 * dsp->fRec107[2]) + (dsp->fConst108 * dsp->fRec107[1]))));
			float fTemp54 = fabsf((fSlow66 * ((dsp->fConst107 * dsp->fRec107[0]) + (dsp->fConst109 * dsp->fRec107[2]))));
			float fTemp55 = ((dsp->fRec105[1] > fTemp54)?fSlow5:fSlow4);
			dsp->fRec106[0] = ((fTemp55 * dsp->fRec106[1]) + (fTemp54 * (1.f - fTemp55)));
			dsp->fRec105[0] = dsp->fRec106[0];
			dsp->fRec108[0] = (fTemp0 - (fSlow69 * ((fSlow70 * dsp->fRec108[2]) + (dsp->fConst112 * dsp->fRec108[1]))));
			dsp->fRec111[0] = (fTemp1 - (fSlow69 * ((fSlow70 * dsp->fRec111[2]) + (dsp->fConst112 * dsp->fRec111[1]))));
			float fTemp56 = fabsf((fSlow69 * ((dsp->fConst111 * dsp->fRec111[0]) + (dsp->fConst113 * dsp->fRec111[2]))));
			float fTemp57 = ((dsp->fRec109[1] > fTemp56)?fSlow5:fSlow4);
			dsp->fRec110[0] = ((dsp->fRec110[1] * fTemp57) + (fTemp56 * (1.f - fTemp57)));
			dsp->fRec109[0] = dsp->fRec110[0];
			dsp->fRec112[0] = (fTemp0 - (fSlow71 * ((fSlow72 * dsp->fRec112[2]) + (dsp->fConst116 * dsp->fRec112[1]))));
			dsp->fRec115[0] = (fTemp1 - (fSlow71 * ((fSlow72 * dsp->fRec115[2]) + (dsp->fConst116 * dsp->fRec115[1]))));
			float fTemp58 = fabsf((fSlow71 * ((dsp->fConst115 * dsp->fRec115[0]) + (dsp->fConst117 * dsp->fRec115[2]))));
			float fTemp59 = ((dsp->fRec113[1] > fTemp58)?fSlow5:fSlow4);
			dsp->fRec114[0] = ((dsp->fRec114[1] * fTemp59) + (fTemp58 * (1.f - fTemp59)));
			dsp->fRec113[0] = dsp->fRec114[0];
			dsp->fRec116[0] = (fTemp0 - (fSlow73 * ((fSlow74 * dsp->fRec116[2]) + (dsp->fConst120 * dsp->fRec116[1]))));
			dsp->fRec119[0] = (fTemp1 - (fSlow73 * ((fSlow74 * dsp->fRec119[2]) + (dsp->fConst120 * dsp->fRec119[1]))));
			float fTemp60 = fabsf((fSlow73 * ((dsp->fConst119 * dsp->fRec119[0]) + (dsp->fConst121 * dsp->fRec119[2]))));
			float fTemp61 = ((dsp->fRec117[1] > fTemp60)?fSlow5:fSlow4);
			dsp->fRec118[0] = ((dsp->fRec118[1] * fTemp61) + (fTemp60 * (1.f - fTemp61)));
			dsp->fRec117[0] = dsp->fRec118[0];
			dsp->fRec120[0] = (fTemp0 - (fSlow76 * ((fSlow77 * dsp->fRec120[2]) + (dsp->fConst124 * dsp->fRec120[1]))));
			dsp->fRec123[0] = (fTemp1 - (fSlow76 * ((fSlow77 * dsp->fRec123[2]) + (dsp->fConst124 * dsp->fRec123[1]))));
			float fTemp62 = fabsf((fSlow76 * ((dsp->fConst123 * dsp->fRec123[0]) + (dsp->fConst125 * dsp->fRec123[2]))));
			float fTemp63 = ((dsp->fRec121[1] > fTemp62)?fSlow5:fSlow4);
			dsp->fRec122[0] = ((dsp->fRec122[1] * fTemp63) + (fTemp62 * (1.f - fTemp63)));
			dsp->fRec121[0] = dsp->fRec122[0];
			dsp->fRec124[0] = (fTemp0 - (fSlow78 * ((fSlow79 * dsp->fRec124[2]) + (dsp->fConst128 * dsp->fRec124[1]))));
			dsp->fRec127[0] = (fTemp1 - (fSlow78 * ((fSlow79 * dsp->fRec127[2]) + (dsp->fConst128 * dsp->fRec127[1]))));
			float fTemp64 = fabsf((fSlow78 * ((dsp->fConst127 * dsp->fRec127[0]) + (dsp->fConst129 * dsp->fRec127[2]))));
			float fTemp65 = ((dsp->fRec125[1] > fTemp64)?fSlow5:fSlow4);
			dsp->fRec126[0] = ((dsp->fRec126[1] * fTemp65) + (fTemp64 * (1.f - fTemp65)));
			dsp->fRec125[0] = dsp->fRec126[0];
			output0[i] = (FAUSTFLOAT)((((((((((((((((((((((((((((((((fSlow2 * ((dsp->fRec0[2] * (0.f - (dsp->fConst2 * dsp->fRec1[0]))) + (dsp->fConst2 * (dsp->fRec0[0] * dsp->fRec1[0])))) + (fSlow7 * ((dsp->fRec4[2] * (0.f - (dsp->fConst7 * dsp->fRec5[0]))) + (dsp->fConst7 * (dsp->fRec4[0] * dsp->fRec5[0]))))) + (fSlow9 * ((dsp->fRec8[2] * (0.f - (dsp->fConst11 * dsp->fRec9[0]))) + (dsp->fConst11 * (dsp->fRec8[0] * dsp->fRec9[0]))))) + (fSlow12 * ((dsp->fRec12[2] * (0.f - (dsp->fConst15 * dsp->fRec13[0]))) + (dsp->fConst15 * (dsp->fRec12[0] * dsp->fRec13[0]))))) + (fSlow15 * ((dsp->fRec16[2] * (0.f - (dsp->fConst19 * dsp->fRec17[0]))) + (dsp->fConst19 * (dsp->fRec16[0] * dsp->fRec17[0]))))) + (fSlow18 * ((dsp->fRec20[2] * (0.f - (dsp->fConst23 * dsp->fRec21[0]))) + (dsp->fConst23 * (dsp->fRec20[0] * dsp->fRec21[0]))))) + (fSlow21 * ((dsp->fRec24[2] * (0.f - (dsp->fConst27 * dsp->fRec25[0]))) + (dsp->fConst27 * (dsp->fRec24[0] * dsp->fRec25[0]))))) + (fSlow23 * ((dsp->fRec28[2] * (0.f - (dsp->fConst31 * dsp->fRec29[0]))) + (dsp->fConst31 * (dsp->fRec28[0] * dsp->fRec29[0]))))) + (fSlow25 * ((dsp->fRec32[2] * (0.f - (dsp->fConst35 * dsp->fRec33[0]))) + (dsp->fConst35 * (dsp->fRec32[0] * dsp->fRec33[0]))))) + (fSlow27 * ((dsp->fRec36[2] * (0.f - (dsp->fConst39 * dsp->fRec37[0]))) + (dsp->fConst39 * (dsp->fRec36[0] * dsp->fRec37[0]))))) + (fSlow30 * ((dsp->fRec40[2] * (0.f - (dsp->fConst43 * dsp->fRec41[0]))) + (dsp->fConst43 * (dsp->fRec40[0] * dsp->fRec41[0]))))) + (fSlow33 * ((dsp->fRec44[2] * (0.f - (dsp->fConst47 * dsp->fRec45[0]))) + (dsp->fConst47 * (dsp->fRec44[0] * dsp->fRec45[0]))))) + (fSlow35 * ((dsp->fRec48[2] * (0.f - (dsp->fConst51 * dsp->fRec49[0]))) + (dsp->fConst51 * (dsp->fRec48[0] * dsp->fRec49[0]))))) + (fSlow38 * ((dsp->fRec52[2] * (0.f - (dsp->fConst55 * dsp->fRec53[0]))) + (dsp->fConst55 * (dsp->fRec52[0] * dsp->fRec53[0]))))) + (fSlow40 * ((dsp->fRec56[2] * (0.f - (dsp->fConst59 * dsp->fRec57[0]))) + (dsp->fConst59 * (dsp->fRec56[0] * dsp->fRec57[0]))))) + (fSlow42 * ((dsp->fRec60[2] * (0.f - (dsp->fConst63 * dsp->fRec61[0]))) + (dsp->fConst63 * (dsp->fRec60[0] * dsp->fRec61[0]))))) + (fSlow44 * ((dsp->fRec64[2] * (0.f - (dsp->fConst67 * dsp->fRec65[0]))) + (dsp->fConst67 * (dsp->fRec64[0] * dsp->fRec65[0]))))) + (fSlow47 * ((dsp->fRec68[2] * (0.f - (dsp->fConst71 * dsp->fRec69[0]))) + (dsp->fConst71 * (dsp->fRec68[0] * dsp->fRec69[0]))))) + (fSlow49 * ((dsp->fRec72[2] * (0.f - (dsp->fConst75 * dsp->fRec73[0]))) + (dsp->fConst75 * (dsp->fRec72[0] * dsp->fRec73[0]))))) + (fSlow51 * ((dsp->fRec76[2] * (0.f - (dsp->fConst79 * dsp->fRec77[0]))) + (dsp->fConst79 * (dsp->fRec76[0] * dsp->fRec77[0]))))) + (fSlow53 * ((dsp->fRec80[2] * (0.f - (dsp->fConst83 * dsp->fRec81[0]))) + (dsp->fConst83 * (dsp->fRec80[0] * dsp->fRec81[0]))))) + (fSlow55 * ((dsp->fRec84[2] * (0.f - (dsp->fConst87 * dsp->fRec85[0]))) + (dsp->fConst87 * (dsp->fRec84[0] * dsp->fRec85[0]))))) + (fSlow57 * ((dsp->fRec88[2] * (0.f - (dsp->fConst91 * dsp->fRec89[0]))) + (dsp->fConst91 * (dsp->fRec88[0] * dsp->fRec89[0]))))) + (fSlow60 * ((dsp->fRec92[2] * (0.f - (dsp->fConst95 * dsp->fRec93[0]))) + (dsp->fConst95 * (dsp->fRec92[0] * dsp->fRec93[0]))))) + (fSlow62 * ((dsp->fRec96[2] * (0.f - (dsp->fConst99 * dsp->fRec97[0]))) + (dsp->fConst99 * (dsp->fRec96[0] * dsp->fRec97[0]))))) + (fSlow64 * ((dsp->fRec100[2] * (0.f - (dsp->fConst103 * dsp->fRec101[0]))) + (dsp->fConst103 * (dsp->fRec100[0] * dsp->fRec101[0]))))) + (fSlow66 * ((dsp->fRec104[2] * (0.f - (dsp->fConst107 * dsp->fRec105[0]))) + (dsp->fConst107 * (dsp->fRec104[0] * dsp->fRec105[0]))))) + (fSlow69 * ((dsp->fRec108[2] * (0.f - (dsp->fConst111 * dsp->fRec109[0]))) + (dsp->fConst111 * (dsp->fRec108[0] * dsp->fRec109[0]))))) + (fSlow71 * ((dsp->fRec112[2] * (0.f - (dsp->fConst115 * dsp->fRec113[0]))) + (dsp->fConst115 * (dsp->fRec112[0] * dsp->fRec113[0]))))) + (fSlow73 * ((dsp->fRec116[2] * (0.f - (dsp->fConst119 * dsp->fRec117[0]))) + (dsp->fConst119 * (dsp->fRec116[0] * dsp->fRec117[0]))))) + (fSlow76 * ((dsp->fRec120[2] * (0.f - (dsp->fConst123 * dsp->fRec121[0]))) + (dsp->fConst123 * (dsp->fRec120[0] * dsp->fRec121[0]))))) + (fSlow78 * ((dsp->fRec124[2] * (0.f - (dsp->fConst127 * dsp->fRec125[0]))) + (dsp->fConst127 * (dsp->fRec124[0] * dsp->fRec125[0])))));
			dsp->fRec0[2] = dsp->fRec0[1];
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec3[2] = dsp->fRec3[1];
			dsp->fRec3[1] = dsp->fRec3[0];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fRec4[2] = dsp->fRec4[1];
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fRec7[2] = dsp->fRec7[1];
			dsp->fRec7[1] = dsp->fRec7[0];
			dsp->fRec6[1] = dsp->fRec6[0];
			dsp->fRec5[1] = dsp->fRec5[0];
			dsp->fRec8[2] = dsp->fRec8[1];
			dsp->fRec8[1] = dsp->fRec8[0];
			dsp->fRec11[2] = dsp->fRec11[1];
			dsp->fRec11[1] = dsp->fRec11[0];
			dsp->fRec10[1] = dsp->fRec10[0];
			dsp->fRec9[1] = dsp->fRec9[0];
			dsp->fRec12[2] = dsp->fRec12[1];
			dsp->fRec12[1] = dsp->fRec12[0];
			dsp->fRec15[2] = dsp->fRec15[1];
			dsp->fRec15[1] = dsp->fRec15[0];
			dsp->fRec14[1] = dsp->fRec14[0];
			dsp->fRec13[1] = dsp->fRec13[0];
			dsp->fRec16[2] = dsp->fRec16[1];
			dsp->fRec16[1] = dsp->fRec16[0];
			dsp->fRec19[2] = dsp->fRec19[1];
			dsp->fRec19[1] = dsp->fRec19[0];
			dsp->fRec18[1] = dsp->fRec18[0];
			dsp->fRec17[1] = dsp->fRec17[0];
			dsp->fRec20[2] = dsp->fRec20[1];
			dsp->fRec20[1] = dsp->fRec20[0];
			dsp->fRec23[2] = dsp->fRec23[1];
			dsp->fRec23[1] = dsp->fRec23[0];
			dsp->fRec22[1] = dsp->fRec22[0];
			dsp->fRec21[1] = dsp->fRec21[0];
			dsp->fRec24[2] = dsp->fRec24[1];
			dsp->fRec24[1] = dsp->fRec24[0];
			dsp->fRec27[2] = dsp->fRec27[1];
			dsp->fRec27[1] = dsp->fRec27[0];
			dsp->fRec26[1] = dsp->fRec26[0];
			dsp->fRec25[1] = dsp->fRec25[0];
			dsp->fRec28[2] = dsp->fRec28[1];
			dsp->fRec28[1] = dsp->fRec28[0];
			dsp->fRec31[2] = dsp->fRec31[1];
			dsp->fRec31[1] = dsp->fRec31[0];
			dsp->fRec30[1] = dsp->fRec30[0];
			dsp->fRec29[1] = dsp->fRec29[0];
			dsp->fRec32[2] = dsp->fRec32[1];
			dsp->fRec32[1] = dsp->fRec32[0];
			dsp->fRec35[2] = dsp->fRec35[1];
			dsp->fRec35[1] = dsp->fRec35[0];
			dsp->fRec34[1] = dsp->fRec34[0];
			dsp->fRec33[1] = dsp->fRec33[0];
			dsp->fRec36[2] = dsp->fRec36[1];
			dsp->fRec36[1] = dsp->fRec36[0];
			dsp->fRec39[2] = dsp->fRec39[1];
			dsp->fRec39[1] = dsp->fRec39[0];
			dsp->fRec38[1] = dsp->fRec38[0];
			dsp->fRec37[1] = dsp->fRec37[0];
			dsp->fRec40[2] = dsp->fRec40[1];
			dsp->fRec40[1] = dsp->fRec40[0];
			dsp->fRec43[2] = dsp->fRec43[1];
			dsp->fRec43[1] = dsp->fRec43[0];
			dsp->fRec42[1] = dsp->fRec42[0];
			dsp->fRec41[1] = dsp->fRec41[0];
			dsp->fRec44[2] = dsp->fRec44[1];
			dsp->fRec44[1] = dsp->fRec44[0];
			dsp->fRec47[2] = dsp->fRec47[1];
			dsp->fRec47[1] = dsp->fRec47[0];
			dsp->fRec46[1] = dsp->fRec46[0];
			dsp->fRec45[1] = dsp->fRec45[0];
			dsp->fRec48[2] = dsp->fRec48[1];
			dsp->fRec48[1] = dsp->fRec48[0];
			dsp->fRec51[2] = dsp->fRec51[1];
			dsp->fRec51[1] = dsp->fRec51[0];
			dsp->fRec50[1] = dsp->fRec50[0];
			dsp->fRec49[1] = dsp->fRec49[0];
			dsp->fRec52[2] = dsp->fRec52[1];
			dsp->fRec52[1] = dsp->fRec52[0];
			dsp->fRec55[2] = dsp->fRec55[1];
			dsp->fRec55[1] = dsp->fRec55[0];
			dsp->fRec54[1] = dsp->fRec54[0];
			dsp->fRec53[1] = dsp->fRec53[0];
			dsp->fRec56[2] = dsp->fRec56[1];
			dsp->fRec56[1] = dsp->fRec56[0];
			dsp->fRec59[2] = dsp->fRec59[1];
			dsp->fRec59[1] = dsp->fRec59[0];
			dsp->fRec58[1] = dsp->fRec58[0];
			dsp->fRec57[1] = dsp->fRec57[0];
			dsp->fRec60[2] = dsp->fRec60[1];
			dsp->fRec60[1] = dsp->fRec60[0];
			dsp->fRec63[2] = dsp->fRec63[1];
			dsp->fRec63[1] = dsp->fRec63[0];
			dsp->fRec62[1] = dsp->fRec62[0];
			dsp->fRec61[1] = dsp->fRec61[0];
			dsp->fRec64[2] = dsp->fRec64[1];
			dsp->fRec64[1] = dsp->fRec64[0];
			dsp->fRec67[2] = dsp->fRec67[1];
			dsp->fRec67[1] = dsp->fRec67[0];
			dsp->fRec66[1] = dsp->fRec66[0];
			dsp->fRec65[1] = dsp->fRec65[0];
			dsp->fRec68[2] = dsp->fRec68[1];
			dsp->fRec68[1] = dsp->fRec68[0];
			dsp->fRec71[2] = dsp->fRec71[1];
			dsp->fRec71[1] = dsp->fRec71[0];
			dsp->fRec70[1] = dsp->fRec70[0];
			dsp->fRec69[1] = dsp->fRec69[0];
			dsp->fRec72[2] = dsp->fRec72[1];
			dsp->fRec72[1] = dsp->fRec72[0];
			dsp->fRec75[2] = dsp->fRec75[1];
			dsp->fRec75[1] = dsp->fRec75[0];
			dsp->fRec74[1] = dsp->fRec74[0];
			dsp->fRec73[1] = dsp->fRec73[0];
			dsp->fRec76[2] = dsp->fRec76[1];
			dsp->fRec76[1] = dsp->fRec76[0];
			dsp->fRec79[2] = dsp->fRec79[1];
			dsp->fRec79[1] = dsp->fRec79[0];
			dsp->fRec78[1] = dsp->fRec78[0];
			dsp->fRec77[1] = dsp->fRec77[0];
			dsp->fRec80[2] = dsp->fRec80[1];
			dsp->fRec80[1] = dsp->fRec80[0];
			dsp->fRec83[2] = dsp->fRec83[1];
			dsp->fRec83[1] = dsp->fRec83[0];
			dsp->fRec82[1] = dsp->fRec82[0];
			dsp->fRec81[1] = dsp->fRec81[0];
			dsp->fRec84[2] = dsp->fRec84[1];
			dsp->fRec84[1] = dsp->fRec84[0];
			dsp->fRec87[2] = dsp->fRec87[1];
			dsp->fRec87[1] = dsp->fRec87[0];
			dsp->fRec86[1] = dsp->fRec86[0];
			dsp->fRec85[1] = dsp->fRec85[0];
			dsp->fRec88[2] = dsp->fRec88[1];
			dsp->fRec88[1] = dsp->fRec88[0];
			dsp->fRec91[2] = dsp->fRec91[1];
			dsp->fRec91[1] = dsp->fRec91[0];
			dsp->fRec90[1] = dsp->fRec90[0];
			dsp->fRec89[1] = dsp->fRec89[0];
			dsp->fRec92[2] = dsp->fRec92[1];
			dsp->fRec92[1] = dsp->fRec92[0];
			dsp->fRec95[2] = dsp->fRec95[1];
			dsp->fRec95[1] = dsp->fRec95[0];
			dsp->fRec94[1] = dsp->fRec94[0];
			dsp->fRec93[1] = dsp->fRec93[0];
			dsp->fRec96[2] = dsp->fRec96[1];
			dsp->fRec96[1] = dsp->fRec96[0];
			dsp->fRec99[2] = dsp->fRec99[1];
			dsp->fRec99[1] = dsp->fRec99[0];
			dsp->fRec98[1] = dsp->fRec98[0];
			dsp->fRec97[1] = dsp->fRec97[0];
			dsp->fRec100[2] = dsp->fRec100[1];
			dsp->fRec100[1] = dsp->fRec100[0];
			dsp->fRec103[2] = dsp->fRec103[1];
			dsp->fRec103[1] = dsp->fRec103[0];
			dsp->fRec102[1] = dsp->fRec102[0];
			dsp->fRec101[1] = dsp->fRec101[0];
			dsp->fRec104[2] = dsp->fRec104[1];
			dsp->fRec104[1] = dsp->fRec104[0];
			dsp->fRec107[2] = dsp->fRec107[1];
			dsp->fRec107[1] = dsp->fRec107[0];
			dsp->fRec106[1] = dsp->fRec106[0];
			dsp->fRec105[1] = dsp->fRec105[0];
			dsp->fRec108[2] = dsp->fRec108[1];
			dsp->fRec108[1] = dsp->fRec108[0];
			dsp->fRec111[2] = dsp->fRec111[1];
			dsp->fRec111[1] = dsp->fRec111[0];
			dsp->fRec110[1] = dsp->fRec110[0];
			dsp->fRec109[1] = dsp->fRec109[0];
			dsp->fRec112[2] = dsp->fRec112[1];
			dsp->fRec112[1] = dsp->fRec112[0];
			dsp->fRec115[2] = dsp->fRec115[1];
			dsp->fRec115[1] = dsp->fRec115[0];
			dsp->fRec114[1] = dsp->fRec114[0];
			dsp->fRec113[1] = dsp->fRec113[0];
			dsp->fRec116[2] = dsp->fRec116[1];
			dsp->fRec116[1] = dsp->fRec116[0];
			dsp->fRec119[2] = dsp->fRec119[1];
			dsp->fRec119[1] = dsp->fRec119[0];
			dsp->fRec118[1] = dsp->fRec118[0];
			dsp->fRec117[1] = dsp->fRec117[0];
			dsp->fRec120[2] = dsp->fRec120[1];
			dsp->fRec120[1] = dsp->fRec120[0];
			dsp->fRec123[2] = dsp->fRec123[1];
			dsp->fRec123[1] = dsp->fRec123[0];
			dsp->fRec122[1] = dsp->fRec122[0];
			dsp->fRec121[1] = dsp->fRec121[0];
			dsp->fRec124[2] = dsp->fRec124[1];
			dsp->fRec124[1] = dsp->fRec124[0];
			dsp->fRec127[2] = dsp->fRec127[1];
			dsp->fRec127[1] = dsp->fRec127[0];
			dsp->fRec126[1] = dsp->fRec126[0];
			dsp->fRec125[1] = dsp->fRec125[0];
			
		}
		
	}
	
}

static void addHorizontalSlider(void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
    sp_vocoder *p = ui_interface;
    p->args[p->argpos] = zone;
    p->argpos++;
}

int sp_vocoder_create(sp_vocoder **p)
{
    *p = malloc(sizeof(sp_vocoder));
    return SP_OK;
}

int sp_vocoder_destroy(sp_vocoder **p)
{
    sp_vocoder *pp = *p;
    vocoder *dsp = pp->faust;
    deletevocoder (dsp);
    free(*p);
    return SP_OK;
}

int sp_vocoder_init(sp_data *sp, sp_vocoder *p)
{
    vocoder *dsp = newvocoder(); 
    UIGlue UI;
    p->argpos = 0;
    UI.addHorizontalSlider= addHorizontalSlider;
    UI.uiInterface = p;
    buildUserInterfacevocoder(dsp, &UI);
    initvocoder(dsp, sp->sr);

     
    p->atk = p->args[0]; 
    p->rel = p->args[1]; 
    p->bwratio = p->args[2];

    p->faust = dsp;
    return SP_OK;
}

int sp_vocoder_compute(sp_data *sp, sp_vocoder *p, SPFLOAT *source, SPFLOAT *excite, SPFLOAT *out)
{

    vocoder *dsp = p->faust;
    SPFLOAT *faust_out[] = {out};
    SPFLOAT *faust_in[] = {source, excite};
    computevocoder(dsp, 1, faust_in, faust_out);
    return SP_OK;
}
