/*
  ==============================================================================

    KAPGain.cpp
    Created: 23 Apr 2019 7:20:26pm
    Author:  Eric

  ==============================================================================
*/

#include "KAPGain.h"
#include "KAPAudioHelpers.h"

KAPGain::KAPGain()
:   mOutputSmoothed(0.0f)
{
}

KAPGain::~KAPGain()
{
}

void KAPGain::process(float* inAudio,
                      float inGain,
                      float* outAudio,
                      int inNumSamplesToRender)
{
    float gainMapped = jmap(inGain, 0.0f, 1.0f, -24.0f, 24.0f);
    gainMapped = Decibels::decibelsToGain(gainMapped, -24.0f);
    
    for (int i = 0; i < inNumSamplesToRender; i++)
    {
        outAudio[i] = inAudio[i] * gainMapped;
    }
    
    float absValue = fabs(outAudio[0]);
    mOutputSmoothed = meterSmoothingCoeff * (mOutputSmoothed - absValue) + absValue;
}

float KAPGain::getMeterLeve()
{
    return mOutputSmoothed;
}
