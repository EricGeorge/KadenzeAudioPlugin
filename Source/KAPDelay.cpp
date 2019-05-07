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
//    mFeedbackSample(0.0),
    mTimeSmoothed(0.0),
    mDelayIndex(0)
{
    zeromem(mCircularBuffer, sizeof(double) * maxBufferSize);
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
    zeromem(mCircularBuffer, sizeof(double) * maxBufferSize);
}

void KAPDelay::process(float* inAudio,
                       float inTime,
                       float inFeedback,
                       float inWetDry,
                       float inType,
                       float* inModulationBuffer,
                       float* outAudio,
                       int inNumSamplesToRender)
{
    // TODO:  Smooth the wet/dry so there isn't a zipper noise when turning
    const float wet = inWetDry;
    const float dry = 1.0f - wet;
    
    float feedbackMapped = 0;
    
    for (int i = 0; i < inNumSamplesToRender; i++)
    {
        if ((int)inType == KAPDelayType_Delay)
        {
            mTimeSmoothed = mTimeSmoothed - kParameterSmoothingCoeff_Fine * (mTimeSmoothed - inTime);
            feedbackMapped = jmap(inFeedback, 0.0f, 1.0f, 0.0f, 0.95f);
        }
        else
        {
            const double delayTimeModulation = (0.003 + (0.002 * inModulationBuffer[i]));
            mTimeSmoothed = mTimeSmoothed - kParameterSmoothingCoeff_Fine * (mTimeSmoothed - delayTimeModulation);
        }
    
        // after we smooth the modulation value to prevent discontinuities, we figure out the number of samples of delay
        const double delayTimeInSamples = (mTimeSmoothed * mSampleRate);
        
        // read the current sample
        const double sample = getInterpolatedSample(delayTimeInSamples);
        
        // write back into the circular buffer applying the feedback to the current sample
        // using tanh_clip in case we want to increase our feedback above 100%.
        mCircularBuffer[mDelayIndex] = tanh_clip(inAudio[i] + (sample * feedbackMapped));
        
        // and write the mix to the output buffer using the current sample
        outAudio[i] = (inAudio[i] * dry) + (sample * wet);
        
        /** mDelayIndex is the write pointer - and we are only incrementing it by 1
         so we just reset to 0 when out of bounds
         */
        mDelayIndex = mDelayIndex + 1;
        if (mDelayIndex >= maxBufferSize) {
            mDelayIndex = 0;
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
    
    const float sample_y0 = mCircularBuffer[index_y0];
    const float sample_y1 = mCircularBuffer[index_y1];
    const float t = readPosition - (int)readPosition;
    
    double outSample = kap_linear_interp(sample_y0, sample_y1, t);
    
    return outSample;
}

