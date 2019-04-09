//
//  DelayUnit.h
//  PureDelay
//
//  Created by asmprog on 19/11/2018.
//  Copyright © 2018 asmprog. All rights reserved.
//

#ifndef DelayUnit_h
#define DelayUnit_h
#include <vector>
#include <math.h>

typedef std::vector<float> DelayBuffer;

class DelayUnit
{
    DelayBuffer m_buffer;
    int m_writePos, m_maxDelay;
    
public:
    ///Basic Delay Unit constructor with a default size of 128 samples
    DelayUnit(int maximumDelay = 128):
    //Initialises values in the order of declaration
    m_writePos(0),
    m_maxDelay(maximumDelay)
    {
		//m_buffer.resize(maximumDelay);
        std::cout<<"Delay Unit Constructed with max size of: "<<m_maxDelay<<std::endl;
		for (int i = 0; i < maximumDelay; i++) {
			m_buffer.push_back(0);
		}

    };
    ///Advance the write position and check that it is in bounds
    void tick()
    {
        ++m_writePos;
        
        while (m_writePos >= m_maxDelay) m_writePos -= m_maxDelay;
        while (m_writePos < 0) m_writePos += m_maxDelay;
    }
    
    ///Returns a delayed signal/value at a given Sample Time. No interpolation is used
    float getDelay(float delayTime)
    {
		float prevIndex = std::floor(m_writePos - delayTime);
		float nextIndex = std::ceil (m_writePos - delayTime);
		float remainder = delayTime - prevIndex;

		while (prevIndex >= m_maxDelay) prevIndex -= m_maxDelay;
		while (prevIndex < 0) prevIndex += m_maxDelay;
		while (nextIndex >= m_maxDelay) nextIndex -= m_maxDelay;
		while (nextIndex < 0) nextIndex += m_maxDelay;

		float v1 = m_buffer[prevIndex];
		float v2 = m_buffer[nextIndex];

		return (1-remainder)*v1 + remainder*v2;
        
    }
    
    ///Writes sample to buffer. Clips audio to range -1 to 1.
    void writeDelay(float sample, bool clip = true, bool replace = true)
    {

        if (clip) //Allows clipping functionality to be turned off
        {
            if (sample > 1) sample = 1;
            if (sample < -1) sample = -1;
        }
        if (replace)
        {
            m_buffer[m_writePos] = sample;
        }
        else
        {
            m_buffer[m_writePos] += sample;
            
            if (clip) //Allows clipping functionality to be turned off
            {
                if (m_buffer[m_writePos] > 1) m_buffer[m_writePos] = 1;
                if (m_buffer[m_writePos] < -1) m_buffer[m_writePos] = -1;
            }
        }
		tick();
        
    }
    
    
    ///Clears the buffer when delay is resumed after a pause.
    void clear()
    {
      //  m_buffer.clear();
		for (int n = 0; n < m_buffer.size(); ++n) {
			m_buffer[n] = 0;
		}
    }
};


#endif /* DelayUnit_h */
