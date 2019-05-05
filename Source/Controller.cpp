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
		*m_Processor->attack = m_Editor->attackS.getValue();
	};
	m_Editor->decayS.onValueChange = [this]
	{
		*m_Processor->decay = m_Editor->decayS.getValue();
	};
	m_Editor->sustainS.onValueChange = [this]
	{
		*m_Processor->sustain = m_Editor->sustainS.getValue();
	};
	m_Editor->releaseS.onValueChange = [this] {
		*m_Processor->release = m_Editor->releaseS.getValue();
	};
	m_Editor->volumeS.onValueChange = [this] {
		*m_Processor->volume = m_Editor->volumeS.getValue();
	};
	m_Editor->toneS.onValueChange = [this] {
		*m_Processor->tone = m_Editor->toneS.getValue();
	};
	m_Editor->ResS.onValueChange = [this] {
		*m_Processor->Res = m_Editor->ResS.getValue();
	};
	m_Editor->attackS.onDragStart = [this]
	{
		m_Editor->attackS.setTextBoxStyle(Slider::TextBoxAbove,true,60,40);
		m_Editor->attackS.setSize(100, 160);
	};
	m_Editor->attackS.onDragEnd = [this]
	{
		m_Editor->attackS.setTextBoxStyle(Slider::NoTextBox,true,NULL,NULL);
		m_Editor->attackS.setSize(100, 100);
	};
	m_Editor->decayS.onDragStart = [this]
	{
		m_Editor->decayS.setTextBoxStyle(Slider::TextBoxAbove, true, 60, 40);
		m_Editor->decayS.setSize(100, 160);
	};
	m_Editor->decayS.onDragEnd = [this]
	{
		m_Editor->decayS.setTextBoxStyle(Slider::NoTextBox, true, NULL, NULL);
		m_Editor->decayS.setSize(100, 100);
	};
	m_Editor->sustainS.onDragStart = [this]
	{
		m_Editor->sustainS.setTextBoxStyle(Slider::TextBoxAbove, true, 60, 40);
		m_Editor->sustainS.setSize(100, 160);
		
	};
	m_Editor->sustainS.onDragEnd = [this]
	{
		m_Editor->sustainS.setTextBoxStyle(Slider::NoTextBox, true, NULL, NULL);
		m_Editor->sustainS.setSize(100, 100);
	};
	m_Editor->releaseS.onDragStart = [this]
	{
		m_Editor->releaseS.setTextBoxStyle(Slider::TextBoxAbove, true, 60, 40);
		m_Editor->releaseS.setSize(100, 160);
	};
	m_Editor->releaseS.onDragEnd = [this]
	{
		m_Editor->releaseS.setTextBoxStyle(Slider::NoTextBox, true, NULL, NULL);
		m_Editor->releaseS.setSize(100, 100);
	};

}



Controller::~Controller()
{

}