/*
  ==============================================================================

    NoiseGenerator.h
    Created: 8 Apr 2019 10:58:13pm
    Author:  alexx

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
struct noise {

	
	static float MakeWNoise()
	{
		Random rand;
		return rand.nextFloat() * 0.25f - 0.125f;
	}

};