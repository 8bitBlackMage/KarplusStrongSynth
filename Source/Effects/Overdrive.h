/*
  ==============================================================================

    Overdrive.h
    Created: 21 Jan 2019 10:09:15pm
    Author:  alexx

  ==============================================================================
*/

#pragma once
#include <math.h>

class Overdrive {
public:

	Overdrive()
	{
	}
	~Overdrive()
	{
	}
	static float clip(float sample, float gain = 0, float level=1)
	{
		return (tanh(gain * sample)*level);

	}

};




