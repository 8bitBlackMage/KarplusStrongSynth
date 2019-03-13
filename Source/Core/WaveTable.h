/*
  ==============================================================================

    WaveTable.h
    Created: 11 Mar 2019 10:25:25pm
    Author:  alexx

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include <vector>

class wavetable
{
public:
	wavetable(int Size, int SampleRate) 
	{
		for (int i = 0; i < Size; i++)
		{
			Samples.push_back(0);
		}
	
	
	}
	~wavetable() {}


	double getSample(int pos) {
		if(pos <= Samples.size()){ return Samples.at(pos); }
		if (pos > Samples.size()) {
			int retpos = pos - Samples.size();
			return Samples.at(retpos);
		}
	}
	void fillSample(double sample, int pos)
	{
		if (pos <= Samples.size()) { Samples.at(pos) = sample; }
		if (pos > Samples.size()) {
			int retpos = pos - Samples.size();
			Samples.at(retpos) = sample;
		}
	}
	void fillBlock(std::vector<double>*Buffer)
	{
		Samples.clear();
		for (int i = 0; i < Buffer->size(); i++)
		{
			Samples.push_back(Buffer->at(i));
		}
	}
	void fillBlockWnoise()
	//fills entire block with white noise
	{
		for (int i = 0; i < BufferSize; i++)
		{
			Random rand(Time::currentTimeMillis());
			double ret = rand.nextDouble();
			Samples.at(i) = ret;
		}
	}
	void fillBlockSine(int freq)
	{
		float phase;
		double ret;
		for (int i = 0; i < BufferSize; i++) 
		{
			ret = sin((juce::MathConstants<float>::twoPi * freq * phase) / 44100);
			phase++;
			Samples.at(i) = ret;
		}

	}
private:
	std::vector<double>Samples;
	int BufferSize, samplerate;
};