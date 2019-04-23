/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
KarplusStrongAuproAudioProcessorEditor::KarplusStrongAuproAudioProcessorEditor (KarplusStrongAuproAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p),keyboardComponent(processor.keyboardState, MidiKeyboardComponent::horizontalKeyboard), m_controller(&p,this)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1024, 768);
	keyboardComponent.setKeyWidth(30);
	SliderSetup(&attackS, 100);
	SliderSetup(&decayS, 100);
	SliderSetup(&sustainS, 100);
	SliderSetup(&releaseS, 100);
	SliderSetup(&volumeS, 250);
	addAndMakeVisible(keyboardComponent);

}

KarplusStrongAuproAudioProcessorEditor::~KarplusStrongAuproAudioProcessorEditor()
{
}

//==============================================================================
void KarplusStrongAuproAudioProcessorEditor::paint (Graphics& g)
{
	g.setFont(20.0f);
	auto size1 = getLocalBounds();
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colour::fromRGB(75, 0, 130));
	g.drawText("volume", size1.removeFromRight(250).removeFromTop(250), juce::Justification::centred, false);
	g.drawText("attack", getLocalBounds().removeFromTop(690).removeFromLeft(100), juce::Justification::centred, false);
	g.drawText("decay", getLocalBounds().removeFromTop(690).removeFromLeft(300), juce::Justification::centred, true);
	g.drawText("sustian", getLocalBounds().removeFromTop(690).removeFromLeft(500), juce::Justification::centred, true);
	g.drawText("release", getLocalBounds().removeFromTop(690).removeFromLeft(700), juce::Justification::centred, true);
	
}

void KarplusStrongAuproAudioProcessorEditor::resized()
{
	auto size1 = getLocalBounds();
	auto size2 = getLocalBounds();
	auto size3 = getLocalBounds();
	size1.removeFromTop(630);
	size2.removeFromTop(300);
	size1.removeFromBottom(10);
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your edsitor..
	keyboardComponent.setBounds(size1.reduced(3));
	attackS.setBounds(size2.removeFromLeft(100));
	decayS.setBounds(size2.removeFromLeft(100));
	sustainS.setBounds(size2.removeFromLeft(100));
	releaseS.setBounds(size2.removeFromLeft(100));
	volumeS.setBounds(size3.removeFromRight(250));
}

void KarplusStrongAuproAudioProcessorEditor::SliderSetup(Slider * slider, int size)
{
	slider->setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
	slider->setColour(0x1001300, Colour::fromRGB(138, 43, 226));
	slider->setColour(0x1001311, Colour::fromRGB(153, 50, 204));
	slider->setColour(0x1001312, Colour::fromRGB(42, 13, 81));
	slider->setSize(size, size);
	slider->setRange(10, 0.1);
	slider->setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(slider);
}
