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
		peram.attack = 0.01;
		peram.decay = 0.01;
		peram.sustain = 0.7;
		peram.release = 0.8;
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
		fire = 0;
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
		if (envelopeVAR.attack !=  Envelope.getParameters().attack || envelopeVAR.decay != Envelope.getParameters().decay || envelopeVAR.sustain != Envelope.getParameters().sustain || envelopeVAR.release != Envelope.getParameters().release)
		{
			Envelope.setParameters(envelopeVAR);
		}
		
		float * left = outputBuffer.getWritePointer(0);
		float * right = outputBuffer.getWritePointer(1);
		for (int i = 0; i < outputBuffer.getNumSamples(); i++)
		{
			float out{ 0 };
			if (noiseburst && (fire < tapTime)) {

				out = noise::MakeWNoise();
			}

			out += Buffer.getDelay(round(tapTime));
			out = Filter.process_samples(out);
			Buffer.writeDelay(out);
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
	void setEnvelope(ADSR::Parameters var)
	{

	}
	ADSR::Parameters envelopeVAR ;
private:
	LowPass Filter;
	Phasor Cycle;
	DelayUnit Buffer;
	ADSR Envelope;
	bool noiseburst;
	int fire;
	int tapTime = 0;

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
	void releaseResources() override {}
	void getADSR(ADSR::Parameters envelope)
	{
	
		for (int i = 0; i < 4; i++) {
			if (Voice* myVoice = dynamic_cast<Voice*> (m_Synth.getVoice(i)))
				myVoice->envelopeVAR = envelope;
		}
	}
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

