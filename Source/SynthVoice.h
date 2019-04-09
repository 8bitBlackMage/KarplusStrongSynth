/*
  ==============================================================================

    SynthVoice.h
    Created: 10 Mar 2019 3:36:03pm
    Author:  alexx

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "Core/DelayUnit.h"
#include "Core/Filter.h"
#include "Core/Phasor.h"
#include "Core/WaveTable.h"
struct SynthSound : public SynthesiserSound
{
	SynthSound() {}
	bool appliesToNote(int) override { return true; }
	bool appliesToChannel(int) override { return true; }


};
class Voice: public SynthesiserVoice {
public:
	Voice():NoiseSource(10,44100),Filter(500,1,44100,1),Buffer(550)
	{
		NoiseSource.fillBlockWnoise();

	}
	~Voice() {}


	bool canPlaySound(SynthesiserSound* sound) override
	{
		return dynamic_cast<SynthesiserSound*> (sound) != nullptr;
	}

	void startNote(int midiNoteNumber, float velocity,
		SynthesiserSound*, int /*currentPitchWheelPosition*/) override {

		auto CyclesPerSecond = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
		auto CyclesPerSample = CyclesPerSecond / getSampleRate();


	}

	void stopNote(float /*velocity*/, bool allowTailOff) override {

	}

	void pitchWheelMoved(int) override {

	}

	void controllerMoved(int, int) override
	{

	}

	void renderNextBlock(AudioSampleBuffer& outputBuffer, int startsample, int numsamples)override
	{
		//for (int i = 0; i < 5; i++)
		//	Buffer.writeDelay[i];

		//for (int i = 0; i < numsamples; i++) {
		//	Filter.process_samples(Buffer.getDelay(i));

		//}
	}

private:
	wavetable NoiseSource;
	LowPass Filter;
	Phasor Cycle;
	DelayUnit Buffer;

};
class SynthAudioSource : public AudioSource
{
public:
	SynthAudioSource(MidiKeyboardState& keystate): m_Keystate(keystate) {
		for (int i = 0; i < 4; i++) {
			m_Synth.addVoice(new Voice());


			m_Synth.addSound(new SynthSound()); 
			
		}
	}

	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override {
		m_Synth.setCurrentPlaybackSampleRate(sampleRate);
	}
	void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override {
		bufferToFill.clearActiveBufferRegion();

		MidiBuffer incomingMidi;

		m_Keystate.processNextMidiBuffer(incomingMidi, bufferToFill.startSample, bufferToFill.numSamples, true);

		m_Synth.renderNextBlock(*bufferToFill.buffer, incomingMidi, bufferToFill.startSample, bufferToFill.numSamples);


	}
private:
	MidiKeyboardState& m_Keystate;
	Synthesiser m_Synth;
};

