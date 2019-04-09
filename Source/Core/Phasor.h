/*
  ==============================================================================

    Phasor.h
    Created: 25 Mar 2019 4:43:16pm
    Author:  alexx

  ==============================================================================
*/

#pragma once
#include <iostream>
class Phasor
{
	double m_sampleRate, m_freq, m_phase, m_phaseInc;


public:

	Phasor(double sampleRate = 44100, double freq = 1) :
		m_sampleRate(sampleRate),
		m_freq(freq),
		m_phase(0)
	{
		m_phaseInc = m_freq / m_sampleRate;
		std::cout << "Phasor Constructed" << std::endl;
	}

	void setFreq(double freq)
	{
		m_freq = freq;
		m_phaseInc = m_freq / m_sampleRate;
	}

	void setSampleRate(double sampleRate)
	{
		m_sampleRate = sampleRate;
		setFreq(m_freq);
	}

	double getPhase()
	{
		return m_phase;
	}

	void tick()
	{
		m_phase += m_phaseInc;

		while (m_phase >= 1)
		{
			m_phase -= 1;
		}
	}

};