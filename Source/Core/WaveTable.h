/*
  ==============================================================================

    WaveTable.h
    Created: 11 Mar 2019 10:25:25pm
    Author:  alexx

  ==============================================================================
*/

#pragma once
#include <vector>
class wavetable
{
public:
	wavetable() {}
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
private:
	std::vector<double>Samples;

};