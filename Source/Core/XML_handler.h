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
#include "../Source/PluginEditor.h"



class XML_Handler
{
public:
	XML_Handler() 
	{
		
		TempPresetFile = File::getSpecialLocation(File::userDocumentsDirectory).getFullPathName()  +( "preset.xml");
		if (TempPresetFile.existsAsFile()) {
			presets = new XmlDocument(TempPresetFile);
		}
		else
		{
			TempPresetFile.create();	

			XmlElement Document("Document");
			XmlElement* preset = new XmlElement("preset");
			std::string PresetName = "Default";
			preset->setAttribute("PresetName",PresetName);
			preset->setAttribute("attack", 0);
			preset->setAttribute("decay", 5);
			preset->setAttribute("sustain", 2);
			preset->setAttribute("release", 5);
			preset->setAttribute("tone", 500);
			preset->setAttribute("res", 0.5);
			preset->setAttribute("volume", 10);




			Document.addChildElement(preset);

			Document.writeToFile(TempPresetFile, *new StringRef(""));
			presets = new XmlDocument(TempPresetFile);
		}




	}
	~XML_Handler()
	{
		delete presets;
	}

	XmlElement SaveToElement(KarplusStrongAuproAudioProcessor * processor, std::string presetName) {

		std::shared_ptr<XmlElement> Element(new XmlElement("preset"));
		Element->setAttribute("PresetName", presetName);
		Element->setAttribute("attack", *processor->attack);
		Element->setAttribute("decay", *processor->decay);
		Element->setAttribute("sustain", *processor->sustain);
		Element->setAttribute("release", *processor->release);
		Element->setAttribute("tone", *processor->tone);
		Element->setAttribute("res", *processor->Res);
		Element->setAttribute("volume", *processor->volume);
		return *Element;
	}
	void LoadFromElement(KarplusStrongAuproAudioProcessor * processor,std::string presetName, XmlElement  data) {
		
		
			if (data.compareAttribute("preset_name", presetName, false))
			{
				DBG("loaded");
				*processor->attack = (data.getDoubleAttribute("attack"));
				*processor->decay = (data.getDoubleAttribute("decay"));
				*processor->sustain = (data.getDoubleAttribute("sustain"));
				*processor->release = (data.getDoubleAttribute("release"));
				*processor->tone = (data.getDoubleAttribute("tone"));
				*processor->Res = (data.getDoubleAttribute("res"));
				*processor->volume = (data.getDoubleAttribute("volume"));
			}

		




	}


	void generatePresetList(ComboBox * list)
	{
		int Id = 1;
		std::unique_ptr<XmlElement>BaseElement(presets->getDocumentElement());
		forEachXmlChildElementWithTagName(*BaseElement, presetElement, "preset")
		{
			String PresetName = presetElement->getStringAttribute("PresetName");
			DBG(PresetName);
			if (PresetName.isNotEmpty()) {

				list->addItem(PresetName, Id);
				Id++;
			}
		}

	}


	void loadPreset(KarplusStrongAuproAudioProcessor* processor,KarplusStrongAuproAudioProcessorEditor* editor, std::string presetName) {
		std::unique_ptr<XmlElement>BaseElement(presets->getDocumentElement());
			forEachXmlChildElementWithTagName(*BaseElement, presetElement, "preset")
			{
					if (presetElement->compareAttribute("PresetName", presetName, false))
					{
					DBG("loaded ", presetName);
					*processor->attack = (presetElement->getDoubleAttribute("attack"));
					*processor->decay = (presetElement->getDoubleAttribute("decay"));
					*processor->sustain = (presetElement->getDoubleAttribute("sustain"));
					*processor->release = (presetElement->getDoubleAttribute("release"));
					*processor->tone = (presetElement->getDoubleAttribute("tone"));
					*processor->Res = (presetElement->getDoubleAttribute("res"));
					*processor->volume = (presetElement->getDoubleAttribute("volume"));
					editor->attackS.setValue(*processor->attack);
					editor->decayS.setValue(*processor->decay);
					editor->sustainS.setValue(*processor->sustain);
					editor->releaseS.setValue(*processor->release);
					editor->toneS.setValue(*processor->tone);
					editor->ResS.setValue(*processor->Res);
					editor->volumeS.setValue(*processor->volume);
					}

			}
			
	


	}
	void SavePreset(KarplusStrongAuproAudioProcessor* processor, std::string presetName) {
		std::unique_ptr<XmlElement>BaseElement(presets->getDocumentElement());
		XmlElement Element = SaveToElement(processor, presetName);




		BaseElement->addChildElement(&Element);
	}

private:
	File TempPresetFile;
	XmlDocument * presets;
	//XmlElement  BaseElement;
	friend class KarplusStrongAuproAudioProcessor;

};