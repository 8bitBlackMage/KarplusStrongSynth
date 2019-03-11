/*
  ==============================================================================

    SynthVoice.h
    Created: 10 Mar 2019 3:36:03pm
    Author:  alexx

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

class Voice {
public:
	Voice(MidiKeyboardState & state, int Voices): m_KeyState(state), m_Voicenum(Voices)
	{

	}
	~Voice() {}
private:
	MidiKeyboardState& m_KeyState;
	Synthesiser m_Synth;
	int m_Voicenum;

};


class SynthSound : public SynthesiserSound {

};