/*
  ==============================================================================

    KAPDelay.h
    Created: 23 Apr 2019 7:20:33pm
    Author:  Eric

  ==============================================================================
*/

#pragma once

#include "KAPAudioHelpers.h"

class KAPDelay
{
public:
    
    KAPDelay();
    ~KAPDelay();
    
    void setSampleRate(double inSampleRate);
    
    void reset();
    
    void process(float* inAudio,
                 float inTime,
                 float inFeedback,
                 float inWetDry,
                 float* inModulationBuffer,
                 float* outAudio,
                 int inNumSamplesToRender);
    
private:
    
    /** internal */
    double getInterpolatedSample(float inDelayTimeInSamples);
    
    double mSampleRate;
    double mCircularBuffer[maxBufferSize];
//    double mFeedbackSample;
    
    float mTimeSmoothed;
    
    int mDelayIndex;
};
