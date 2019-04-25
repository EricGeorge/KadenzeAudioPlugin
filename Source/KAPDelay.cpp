/*
  ==============================================================================

    KAPDelay.cpp
    Created: 23 Apr 2019 7:20:33pm
    Author:  Eric

  ==============================================================================
*/

#include "KAPDelay.h"
#include "KAPAudioHelpers.h"

#include "JuceHeader.h"

KAPDelay::KAPDelay()
:   mSampleRate(-1),
    mFeedbackSample(0.0),
    mTimeSmoothed(0.0),
    mDelayIndex(0)
{
    
}

KAPDelay::~KAPDelay()
{
    
}

void KAPDelay::setSampleRate(double inSampleRate)
{
    mSampleRate = inSampleRate;
}

void KAPDelay::reset()
{
    mTimeSmoothed = 0.0f;
    zeromem(mBuffer, sizeof(double) * maxBufferSize);
}

void KAPDelay::process(float* inAudio,
                       float inTime,
                       float inFeedback,
                       float inWetDry,
                       float* inModulationBuffer,
                       float* outAudio,
                       int inNumSamplesToRender)
{
    const float wet = inWetDry;
    const float dry = 1.0f - wet;
    const float feedbackMapped = jmap(inFeedback, 0.0f, 1.0f, 0.0f, 0.95f);
    
    int index = 0;
    
    for (int i = 0; i < inNumSamplesToRender; i++) {
        
        const double delayTimeModulation = (inTime + (0.002 * inModulationBuffer[i]));
        
        mTimeSmoothed = mTimeSmoothed - kParameterSmoothingCoeff_Fine * (mTimeSmoothed - delayTimeModulation);
        
        const double delayTimeInSamples = (mTimeSmoothed * mSampleRate);
        
        const double sample = getInterpolatedSample(delayTimeInSamples);
        
        mBuffer[mDelayIndex] = inAudio[i] + (mFeedbackSample * feedbackMapped);
        
        mFeedbackSample = sample;
        
        outAudio[i] = (inAudio[i] * dry) + (sample * wet);
        
        mDelayIndex = mDelayIndex + 1;
        if (mDelayIndex >= maxBufferSize) {
            mDelayIndex = mDelayIndex - maxBufferSize;
        }
    }
}

double KAPDelay::getInterpolatedSample(float inDelayTimeInSamples)
{
    double readPosition = (double)mDelayIndex - inDelayTimeInSamples;
    if (readPosition < 0.0f) {
        readPosition = readPosition + maxBufferSize;
    }
    
    // a fractional read position will be between index_y0 and index_y1
    
    // get the lower side by taking the int part of readPosition
    int index_y0 = readPosition;
    
    // index_y1 should be based on index_y0 - just one sample higher
    int index_y1 = index_y0 + 1;
    if (index_y1 > maxBufferSize) {
        index_y1 = index_y1 - maxBufferSize;
    }
    
    const float sample_y0 = mBuffer[index_y0];
    const float sample_y1 = mBuffer[index_y1];
    const float t = readPosition - (int)readPosition;
    
    double outSample = kap_linear_interp(sample_y0, sample_y1, t);
    
    return outSample;
}

