/*
  ==============================================================================

    KAPAudioHelpers.h
    Created: 23 Apr 2019 7:19:55pm
    Author:  Eric

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

#define kParameterSmoothingCoeff_Generic 0.04
#define kParameterSmoothingCoeff_Fine 0.002
#define kMeterSmoothingCoeff 0.2

const static int maxBufferSize = 192000; // enough for 4 seconds of delay at 44100 (176400 samples)

const static double kPI = M_PI;
const static double k2PI = 2 * kPI;

static inline float dbToNormalizedGain(float inValue)
{
    float inValuedB = Decibels::gainToDecibels(inValue);
    inValuedB = (inValuedB + 96.0f) / 96.0f;
    
    return inValuedB;
}

inline float kap_linear_interp(float v0, float v1, float t)
{
    return (1 - t) * v0 + t * v1;
}

inline double tanh_clip(double x)
{
    return x * (27 + x * x) / (27 + 9 * x * x);
}

inline float kap_denormalize(float inValue)
{
    float absValue = fabs(inValue);
    
    if (absValue < 1e-15)
    {
        return 0.0f;
    }
    else
    {
        return inValue;
    }
}
