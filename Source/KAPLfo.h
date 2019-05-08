/*
  ==============================================================================

    KAPLfo.h
    Created: 23 Apr 2019 7:20:17pm
    Author:  Eric

  ==============================================================================
*/

#pragma once

#include "KAPAudioHelpers.h"

class KAPLfo
{
public:
    KAPLfo();
    ~KAPLfo();
    
    void reset();
    
    void setSampleRate(double inSampleRate);
    
    void process(float inRate, float inDepth, int inNumSamples);
    
    float* getBuffer();
    
private:
    double mSampleRate;
    float mPhase;
    float mBuffer[maxBufferSize];
};
