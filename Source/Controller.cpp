/*
  ==============================================================================

    Controller.cpp
    Created: 19 Apr 2019 9:10:19pm
    Author:  alexx

  ==============================================================================
*/

#include "Controller.h"
#include "PluginEditor.h"
#include "PluginProcessor.h"

Controller::Controller(KarplusStrongAuproAudioProcessor* Processor, KarplusStrongAuproAudioProcessorEditor * Editor):m_Processor(Processor), m_Editor(Editor)
{
	m_Editor->attackS.onValueChange = [this] 
	{
		DBG(String(m_Editor->attackS.getValue()));
	};

}


Controller::~Controller()
{

}