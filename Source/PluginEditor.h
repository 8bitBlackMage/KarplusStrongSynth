/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Controller.h"
//==============================================================================
/**
*/
class KarplusStrongAuproAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    KarplusStrongAuproAudioProcessorEditor (KarplusStrongAuproAudioProcessor&);
    ~KarplusStrongAuproAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
	friend class Controller;
	Controller m_controller;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it
	void SliderSetup(Slider * slider, int size);
    KarplusStrongAuproAudioProcessor& processor;
	MidiKeyboardComponent keyboardComponent;
	Slider attackS, decayS, sustainS, releaseS, volumeS;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KarplusStrongAuproAudioProcessorEditor)
};
