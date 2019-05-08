/*
  ==============================================================================

    KAPGain.h
    Created: 23 Apr 2019 7:20:26pm
    Author:  Eric

  ==============================================================================
*/

#pragma once

class KAPGain
{
public:
    KAPGain();
    ~KAPGain();

    void process(float* inAudio,
                 float inGain,
                 float* outAudio,
                 int inNumSamplesToRender);
    
    float getMeterLeve();
    
private:
    float mOutputSmoothed;
};
