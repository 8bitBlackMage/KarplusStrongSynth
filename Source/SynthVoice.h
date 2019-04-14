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
	Voice(int sampleRate = 48000):Filter(10000,(1/sqrt(2)),sampleRate,1),Buffer(sampleRate*50)
	{
		ADSR::Parameters peram;
		peram.attack = 0;
		peram.decay = 5;
		peram.sustain = 50;
		peram.release = 5;
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
		tapTime = (1/CyclesPerSecond) * getSampleRate();
		DBG(tapTime);
		Envelope.noteOn();	
		noiseburst = true;
	}

	void stopNote(float /*velocity*/, bool allowTailOff) override {
		Envelope.noteOff();
		noiseburst = false;
		fire = 0;
		
	}

	void pitchWheelMoved(int) override {

	}

	void controllerMoved(int, int) override
	{

	}
	void renderNextBlock(AudioSampleBuffer& outputBuffer, int startsample, int numsamples)override
	{
		if (!Envelope.isActive()) return;
		
		float * left = outputBuffer.getWritePointer(0);
		float * right = outputBuffer.getWritePointer(1);
		for (int i = 0; i < outputBuffer.getNumSamples(); i++)
		{
			float out{ 0 };
			if (noiseburst && (fire < (500))) {

				out = noise::MakeWNoise();
			}

			out += Buffer.getDelay(round(tapTime));
			out = Filter.process_samples(out);
			Buffer.writeDelay(out * 0.97);
			float env = Envelope.getNextSample();
			left[i] += out * env;
			right[i] += out * env;
			if (!Envelope.isActive()) {
				clearCurrentNote();
				tapTime = 0;
			}
			fire++;

		}
		//Envelope.applyEnvelopeToBuffer(outputBuffer, startsample, numsamples);
;
	}
	
	void setCurrentPlaybackSampleRate(double samplerate) override {
		Filter.resetsamplerate((int)samplerate);
	}
private:
	LowPass Filter;
	Phasor Cycle;
	DelayUnit Buffer;
	ADSR Envelope;
	bool noiseburst;
	int fire;
	float tapTime = 0;

};
class SynthAudioSource : public AudioSource
{
public:
	SynthAudioSource(MidiKeyboardState& keystate, int sampleRate): m_Keystate(keystate) {
		for (int i = 0; i < 4; i++) 
			m_Synth.addVoice(new Voice(44100));


			m_Synth.addSound(new SynthSound());

	}

	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override {
		for (int i = 0; i < m_Synth.getNumVoices(); i++)
		{
			m_Synth.getVoice(i)->setCurrentPlaybackSampleRate(sampleRate);
		}
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

