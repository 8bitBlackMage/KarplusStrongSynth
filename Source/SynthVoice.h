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
#include "Core/NoiseGenerator.h"
struct SynthSound : public SynthesiserSound
{
	SynthSound() {}
	bool appliesToNote(int) override { return true; }
	bool appliesToChannel(int) override { return true; }


};
class Voice: public SynthesiserVoice {
public:
	Voice():Filter(500,1,44100,1),Buffer(550)
	{
		

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
		Envelope.noteOn();	
		noiseburst = true;
	}

	void stopNote(float /*velocity*/, bool allowTailOff) override {
		Envelope.noteOff();
		noiseburst = false;
	}

	void pitchWheelMoved(int) override {

	}

	void controllerMoved(int, int) override
	{

	}

	void renderNextBlock(AudioSampleBuffer& outputBuffer, int startsample, int numsamples)override
	{
		float filtered, out;
		int fire;
		float * left = outputBuffer.getWritePointer(0);
		float * right = outputBuffer.getWritePointer(1);
		for (int i = 0; i < outputBuffer.getNumSamples(); i++)
		{

			if (noiseburst == true && fire < 54 * 44.1) {
				out = noise::MakeWNoise();
			}


			filtered += Filter.process_samples(out);
			Buffer.writeDelay(out * 0.97);
			out = Buffer.getDelay(200);
			left[i] = out;
			right[i] = out;


			fire++;

		}
		Envelope.applyEnvelopeToBuffer(outputBuffer, startsample, numsamples);
;
	}
	

private:
	LowPass Filter;
	Phasor Cycle;
	DelayUnit Buffer;
	ADSR Envelope;
	bool noiseburst;
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

	void releaseResources() override {}

	
private:
	MidiKeyboardState& m_Keystate;
	Synthesiser m_Synth;
};

