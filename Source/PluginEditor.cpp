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
    : AudioProcessorEditor (&p), processor (p),keyboardComponent(processor.keyboardState, MidiKeyboardComponent::horizontalKeyboard)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1024, 768);
	keyboardComponent.setKeyWidth(30);
	addAndMakeVisible(keyboardComponent);
}

KarplusStrongAuproAudioProcessorEditor::~KarplusStrongAuproAudioProcessorEditor()
{
}

//==============================================================================
void KarplusStrongAuproAudioProcessorEditor::paint (Graphics& g)
{
	
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

   
	
}

void KarplusStrongAuproAudioProcessorEditor::resized()
{
	auto size1 = getLocalBounds();
	size1.removeFromTop(630);
	size1.removeFromBottom(10);
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	keyboardComponent.setBounds(size1.reduced(3));
}
