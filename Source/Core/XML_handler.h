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
	XML_Handler()
	{
		File TempPresetFile(File::getCurrentWorkingDirectory().getFullPathName() + "preset.xml");
		if (TempPresetFile.existsAsFile()) {
			presets = new XmlDocument(TempPresetFile);
			BaseElement = new XmlElement(*presets->getDocumentElement());
		}
		else {
			DialogWindow error("error", Colour::fromRGB(1, 1, 1), true, false);
			DBG("creating new file");
			TempPresetFile.create();
		}

	}
	~XML_Handler() {
//		delete presets;
//		delete BaseElement;
	}
	void loadPreset(KarplusStrongAuproAudioProcessor* processor, std::string presetName) {
		if (BaseElement->getTagName() == String("preset")) {
			forEachXmlChildElementWithTagName(*BaseElement, presetElement, "preset")
			{
				if (presetElement->compareAttribute("Preset Name", presetName, true)) {
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


	}
	void SavePreset(KarplusStrongAuproAudioProcessor* processor, std::string presetName) {
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
	XmlDocument * presets;
	XmlElement * BaseElement;


};