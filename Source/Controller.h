/*
  ==============================================================================

    Controller.h
    Created: 19 Apr 2019 9:10:19pm
    Author:  alexx

  ==============================================================================
*/

#pragma once
class KarplusStrongAuproAudioProcessor;
class KarplusStrongAuproAudioProcessorEditor;

class Controller
{
public:
	Controller(KarplusStrongAuproAudioProcessor* Processor, KarplusStrongAuproAudioProcessorEditor * Editor);
	~Controller();
private:
	KarplusStrongAuproAudioProcessor * m_Processor;
	KarplusStrongAuproAudioProcessorEditor * m_Editor;


};