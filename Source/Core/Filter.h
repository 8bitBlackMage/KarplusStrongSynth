/*
  ==============================================================================

	Filter.h
	Created: 22 Jan 2019 9:41:36am
	Author:  alexx

  ==============================================================================
*/

#pragma once
#include "DelayUnit.h"
#include "JuceHeader.h"
#include <math.h>
#include <vector>
class Biquad //public Filter
//https://gist.github.com/long-march/a99907e0ca4e9aa969c383451bca26e9
//thanks Dom
{
public:
	Biquad(float cutoff = 20000, float res = 10, float samplerate = 44100, float dbgain = 1.0):M_Cutoff(cutoff),M_Res(res), M_samplerate(samplerate),M_DBGain(dbgain)
	{
		Calculate_intermediates(M_Cutoff, M_Res, M_samplerate, M_DBGain);

	}
	void resetsamplerate(int samplerate)
	{
		M_samplerate = samplerate;
		Calculate_intermediates(M_Cutoff, M_Res, M_samplerate, M_DBGain);
	}
	void ChangeFreq(int CutoffFreq) {
		M_Cutoff = CutoffFreq;
		Calculate_intermediates(M_Cutoff, M_Res, M_samplerate, M_DBGain);
	}
	void changeRes(float Res) {
		M_Res = Res;
		Calculate_intermediates(M_Cutoff, M_Res, M_samplerate, M_DBGain);
	}
	void changeGain(int gain) {
		M_DBGain = gain;
		Calculate_intermediates(M_Cutoff, M_Res, M_samplerate, M_DBGain);
	}
	float process_samples(float sample) {
		float processed = ((b[0] * sample) + (b[1] * xi1) + (b[2] * xi2) - (a[1] * yi1) - (a[2] * yi2)) * a[0];
		xi2 = xi1;
		xi1 = sample;
		yi2 = yi1;
		yi1 = processed;
	//	DBG(processed);
		return processed;
	}

	float getCuttof() {
		return M_Cutoff;
	}
	float getRes() {
		return M_Res;
	}
private:
	float A;
	int M_samplerate;
	float M_Cutoff;
	float M_Res;
	float M_DBGain;
	void Calculate_intermediates(float Cutoff, float Res, float SampleRate, float DbGain)
	{
		A = pow(10, DbGain / 20);
		omega = juce::MathConstants<float>::twoPi * (Cutoff / SampleRate);
		alpha = sin(omega) / (2 * Res);
	}
protected:
	double xi1 = 0;
	double xi2 = 0;
	double yi1 = 0;
	double yi2 = 0;

	//std::array<double, 3> a;
	double a[3];
	double b[3];
	//std::array<double, 3> b;
	double alpha = 0;
	double omega = 0;
};

class LowPass : public Biquad
{
public:
	 
	LowPass(float cutoff, float res, float samplerate, float dbgain) :Biquad(cutoff, res, samplerate, dbgain) {

		b[0] = (1 - cos(omega)) / 2;
		b[1] = 1 - cos(omega);
		b[2] = (1 - cos(omega)) / 2;

		a[0] = 1 / (1 + alpha);
		a[1] = -2 * cos(omega);
		a[2] = 1 - alpha;
	}
	void changeVal() {
		b[0] = (1 - cos(omega)) / 2;
		b[1] = 1 - cos(omega);
		b[2] = (1 - cos(omega)) / 2;

		a[0] = 1 / (1 + alpha);
		a[1] = -2 * cos(omega);
		a[2] = 1 - alpha;
		xi1 = 0;
		xi2 = 0;
		yi1 = 0;
		yi2 = 0;
	}

};

class HighPass : public Biquad
{
public:
	HighPass() {}
	HighPass(float cutoff, float res, float samplerate, float dbgain) :Biquad(cutoff, res, samplerate, dbgain) {
		b[0] = (1 + cos(omega)) / 2;
		b[1] = -(1 + cos(omega));
		b[2] = (1 + cos(omega)) / 2;

		a[0] = 1 / (1 + alpha);
		a[1] = 2 * cos(omega);
		a[2] = 1 - alpha;
	}
	void changeVal() {
		b[0] = (1 + cos(omega)) / 2;
		b[1] = -(1 + cos(omega));
		b[2] = (1 + cos(omega)) / 2;

		a[0] = 1 / (1 + alpha);
		a[1] = 2 * cos(omega);
		a[2] = 1 - alpha;
		xi1 = 0;
		xi2 = 0;
		yi1 = 0;
		yi2 = 0;

	}



};
