/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
KarplusStrongAuproAudioProcessor::KarplusStrongAuproAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", AudioChannelSet::stereo(), true)
#endif
	), m_Synth(keyboardState, 48000) 
#endif
{
	attack = new AudioParameterFloat("Attack", "Attack", 0, 10, 5);
	decay = new AudioParameterFloat("Decay", "Decay", 0, 10, 5);
	sustain = new AudioParameterFloat("Sustain", "Sustain", 0, 1, 0.1f);
	release = new AudioParameterFloat("Release", "Release", 0, 100, 1);
	tone = new AudioParameterFloat("Tone", "Tone", 5000, 20000, 10000);
	Res = new AudioParameterFloat("Res", "Res", 0, 1, 0.5f);
	volume = new AudioParameterFloat("Volume", "Volume", 0, 1, 0.5f);

	addParameter(attack);
	addParameter(decay);
	addParameter(sustain);
	addParameter(release);
	addParameter(tone);
	addParameter(volume);
	addParameter(Res);
}

KarplusStrongAuproAudioProcessor::~KarplusStrongAuproAudioProcessor()
{
}

//==============================================================================
const String KarplusStrongAuproAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool KarplusStrongAuproAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool KarplusStrongAuproAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool KarplusStrongAuproAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double KarplusStrongAuproAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int KarplusStrongAuproAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int KarplusStrongAuproAudioProcessor::getCurrentProgram()
{
    return 0;
}

void KarplusStrongAuproAudioProcessor::setCurrentProgram (int index)
{
}

const String KarplusStrongAuproAudioProcessor::getProgramName (int index)
{
    return {};
}

void KarplusStrongAuproAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void KarplusStrongAuproAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
	m_Synth.prepareToPlay(samplesPerBlock, sampleRate);

}

void KarplusStrongAuproAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
	m_Synth.releaseResources();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool KarplusStrongAuproAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void KarplusStrongAuproAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();
	envelope.attack = *attack;
	envelope.decay = *decay;
	envelope.sustain = *sustain;
	envelope.release = *release;
	// In case we have more outputs than inputs, this code clears any output
	// channels that didn't contain input data, (because these aren't
	// guaranteed to be empty - they may contain garbage).
	// This is here to avoid people getting screaming feedback
	// when they first compile a plugin, but obviously you don't need to keep
	// this code if your algorithm always overwrites all the output channels.
	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());	
	AudioSourceChannelInfo bufferwrapper(&buffer, 0, buffer.getNumSamples());
	keyboardState.processNextMidiBuffer(midiMessages, bufferwrapper.startSample, bufferwrapper.numSamples, true);
	m_Synth.addMidi(midiMessages);
	m_Synth.getADSR(envelope);
	m_Synth.setFreq(*tone);
	m_Synth.setVolume(*volume);
	m_Synth.setRes(*Res);
	m_Synth.getNextAudioBlock(bufferwrapper);


}

//==============================================================================
bool KarplusStrongAuproAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* KarplusStrongAuproAudioProcessor::createEditor()
{
    return new KarplusStrongAuproAudioProcessorEditor (*this);
}

//==============================================================================
void KarplusStrongAuproAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
//	Statehandler.SavePreset(this, "State");






}

void KarplusStrongAuproAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
//	Statehandler.loadPreset(this, "State");


}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new KarplusStrongAuproAudioProcessor();
}
