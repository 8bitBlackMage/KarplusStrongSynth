/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthVoice.h"
class XML_Handler;
class Controller;
//==============================================================================
/**
*/
class KarplusStrongAuproAudioProcessor  : public AudioProcessor
{
public:
	MidiKeyboardState keyboardState;
    //==============================================================================
    KarplusStrongAuproAudioProcessor();
    ~KarplusStrongAuproAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	AudioParameterFloat *attack;
	AudioParameterFloat *decay;
	AudioParameterFloat *sustain;
	AudioParameterFloat *release;
	AudioParameterFloat *tone;
	AudioParameterFloat *Res;
	AudioParameterFloat *volume;
private:
    //==============================================================================
	friend class Controller;
	SynthAudioSource m_Synth;
	//float volume = 0.9;
	ADSR::Parameters envelope;
	friend class XML_Handler;
	XML_Handler * StateManager;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KarplusStrongAuproAudioProcessor)
};
