/*
  ==============================================================================

    XML_handler.h
    Created: 5 May 2019 1:19:44pm
    Author:  alexx

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "../Source/PluginProcessor.h"



class XML_Handler
{
public:
	XML_Handler(): TempPresetFile(File::getCurrentWorkingDirectory().getFullPathName() + "preset.xml"), presets(TempPresetFile) 
	{

	}
	~XML_Handler()
	{

	}








	void loadPreset(KarplusStrongAuproAudioProcessor* processor, std::string presetName) {
		std::unique_ptr<XmlElement>BaseElement(presets.getDocumentElement());
			forEachXmlChildElementWithTagName(*BaseElement, presetElement, "preset")
			{
					if (presetElement->compareAttribute("preset_name", presetName, false))
					{
					DBG("loaded");
					*processor->attack = (presetElement->getDoubleAttribute("attack"));
					*processor->decay = (presetElement->getDoubleAttribute("decay"));
					*processor->sustain = (presetElement->getDoubleAttribute("sustain"));
					*processor->release = (presetElement->getDoubleAttribute("release"));
					*processor->tone = (presetElement->getDoubleAttribute("tone"));
					*processor->Res = (presetElement->getDoubleAttribute("res"));
					*processor->volume = (presetElement->getDoubleAttribute("volume"));
					}

			}
			
	


	}
	void SavePreset(KarplusStrongAuproAudioProcessor* processor, std::string presetName) {
		std::unique_ptr<XmlElement>BaseElement(presets.getDocumentElement());
		//XmlElement Element = SaveToElement(processor, presetName);
		XmlElement * Element(new XmlElement("preset"));
		Element->setAttribute("Preset Name", presetName);
		Element->setAttribute("attack", *processor->attack);
		Element->setAttribute("decay", *processor->decay);
		Element->setAttribute("sustain", *processor->sustain);
		Element->setAttribute("release", *processor->release);
		Element->setAttribute("tone", *processor->tone);
		Element->setAttribute("res", *processor->Res);
		Element->setAttribute("volume", *processor->volume);



		BaseElement->addChildElement(Element);
	}

private:
	File TempPresetFile;
	XmlDocument presets;
	//XmlElement  BaseElement;
	friend class KarplusStrongAuproAudioProcessor;

};