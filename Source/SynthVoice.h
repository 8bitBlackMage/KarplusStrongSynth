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
	Voice(int sampleRate = 44100 ):Filter(10000,1,sampleRate,1),Buffer(sampleRate*5)
	{
		ADSR::Parameters peram;
		peram.attack = 5;
		peram.decay = 3;
		peram.sustain = 3;
		peram.release = 2;
		Envelope.setParameters(peram);

	}
	~Voice() {}


	bool canPlaySound(SynthesiserSound* sound) override
	{
		return dynamic_cast<SynthSound*> (sound) != nullptr;
	}

	void startNote(int midiNoteNumber, float velocity,
		SynthesiserSound*, int /*currentPitchWheelPosition*/) override {

		auto CyclesPerSecond = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
		auto CyclesPerSample = CyclesPerSecond / getSampleRate();
		Envelope.noteOn();	
		noiseburst = true;
		
	}
	
	void stopNote(float /*velocity*/, bool allowTailOff = true) override {
		if (allowTailOff)
		{
			if (tailOff < 0.005)
				tailOff = 1.0;
		}
		
		noiseburst = false;
		tailOff -= 0.005;
	}

	void pitchWheelMoved(int) override {

	}

	void controllerMoved(int, int) override
	{

	}

	void renderNextBlock(AudioSampleBuffer& outputBuffer, int startsample, int numsamples)override
	{
		float filtered, out;
		float * left = outputBuffer.getWritePointer(0);
		float * right = outputBuffer.getWritePointer(1);
		

			for (int i = 0; i < outputBuffer.getNumSamples(); i++)
			{

				if ((noiseburst) && (fire < (5000 * 44.1))) {
				
				out =  rand.nextFloat() * 0.25f - 0.125f;
					//out = noise::MakeWNoise();
					//Envelope.noteOff();
					
				}
				else {
				out = Buffer.getDelay(500);
				filtered = Filter.process_samples(out);
				Buffer.writeDelay(filtered * 0.97);
				}
				left[i] += out;
				right[i] += out;

				if (!Envelope.isActive())
					clearCurrentNote();

				fire++;
				tailOff *= 0.99;

				if (tailOff < 0.05) {
					Envelope.noteOff();
					clearCurrentNote();
				}
			}
			Envelope.applyEnvelopeToBuffer(outputBuffer, startsample, numsamples);
			

	}

private:
	LowPass Filter;
	Phasor Cycle;
	DelayUnit Buffer;
	ADSR Envelope;
	bool noiseburst;
	int fire = 0;
	int offcount;
	float tailOff = 1.0;
	Random rand;
};
class SynthAudioSource : public AudioSource
{
public:
	SynthAudioSource(MidiKeyboardState& keystate, int sampleRate): m_Keystate(keystate) {
		for (int i = 0; i < 4; i++) {
			m_Synth.addVoice(new Voice(sampleRate));


			m_Synth.addSound(new SynthSound()); 
			
		}
	}

	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override {
		m_Synth.setCurrentPlaybackSampleRate(sampleRate);
		midiCollector.reset(sampleRate);
	}
	void addMidi(MidiBuffer & buffer) {
		incomingMidi = buffer;
	}
	void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override {
		bufferToFill.clearActiveBufferRegion();

		
		//midiCollector.removeNextBlockOfMessages(incomingMidi, bufferToFill.numSamples);
		
		//m_Keystate.processNextMidiBuffer(incomingMidi, bufferToFill.startSample, bufferToFill.numSamples, true);

		m_Synth.renderNextBlock(*bufferToFill.buffer, incomingMidi, bufferToFill.startSample, bufferToFill.numSamples);


	}
	//void 
	void releaseResources() override {}

	MidiMessageCollector* getMidiCollector()
	{
		return &midiCollector;
	}
	
private:
	MidiBuffer incomingMidi;
	MidiKeyboardState& m_Keystate;
	MidiMessageCollector midiCollector;
	Synthesiser m_Synth;
};

