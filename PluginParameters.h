#pragma once
#include "PluginParametersIDs.h"
#include <memory>

class PluginParameters
{
public:
	PluginParameters(juce::AudioProcessor* processorToConnectTo) :
		_parameters(*processorToConnectTo, nullptr, "Parameters", createParameters())
	{
	}

	virtual ~PluginParameters() = default;

protected:
	juce::AudioProcessorValueTreeState _parameters;

	virtual juce::AudioProcessorValueTreeState::ParameterLayout createParameters()
	{
		std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;

		// This is where i define parameters and their ranges and default values
		parameters.push_back(std::make_unique<juce::AudioParameterFloat>(PARAMETER_IDS[ParamFloat], PARAMETER_NAMES[ParamFloat],juce::NormalisableRange<float>(0.f, 1.f), 0.1f, "%"));
		parameters.push_back(std::make_unique<juce::AudioParameterInt>(PARAMETER_IDS[ParamInt], PARAMETER_NAMES[ParamInt], 1, 6, 2));
		return { parameters.begin(), parameters.end() };
	}


	void getStateXml(juce::MemoryBlock& destData, const char* xmlID)
	{
		std::unique_ptr<juce::XmlElement> xml(new juce::XmlElement(xmlID));

		for (int i = 0; i < NumPluginParameters; ++i)
			xml->setAttribute(juce::Identifier(PARAMETER_IDS[i]), (double)(*_parameters.getRawParameterValue(PARAMETER_IDS[i])));	// normalized value
		juce::AudioProcessor::copyXmlToBinary(*xml, destData);
	}

	void setStateFromXml(const void* data, int sizeInBytes, const char* xmlID)
	{
		std::unique_ptr<juce::XmlElement> xmlState(juce::AudioProcessor::getXmlFromBinary(data, sizeInBytes));

		if (xmlState.get() != nullptr)
		{
			if (xmlState->hasTagName(xmlID))
			{
				for (int i = 0; i < NumPluginParameters; ++i)
				{
					// Tree state saves actual values of parameters - not normalized. But setValue() only takes normalized - 0..1. Everything, that's range is different than 0..1 need to call convertTo0to1()
					auto par = _parameters.getParameter(PARAMETER_IDS[i]);
					par->setValue(par->convertTo0to1((float)xmlState->getDoubleAttribute(PARAMETER_IDS[i])));
				}
			}
		}
	}
};

