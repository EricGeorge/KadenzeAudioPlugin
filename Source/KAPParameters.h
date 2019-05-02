/*
  ==============================================================================

    KAPParameters.h
    Created: 28 Apr 2019 2:50:53pm
    Author:  Eric

  ==============================================================================
*/

#pragma once

enum KAPParameter
{
    kParameter_InputGain = 0,
    kParameter_ModulationRate,
    kParameter_ModulationDepth,
    kParameter_DelayTime,
    kParameter_DelayFeedback,
    kParameter_DelayWetDry,
    kParameter_DelayType,
    kParameter_OutputGain,

    kParameter_TotalNumParameters
};

static String KAPParameterID[kParameter_TotalNumParameters] =
{
    "InputGain",
    "ModulationRate",
    "ModulationDepth",
    "DelayTime",
    "DelayFeedback",
    "DelayWetDry",
    "DelayType",
    "OutputGain"
};

static String KAPParameterLabel[kParameter_TotalNumParameters] =
{
    "Input Gain",
    "Modulation Rate",
    "Modulation Depth",
    "Delay Time",
    "Delay Feedback",
    "Delay WetDry",
    "Delay Type",
    "Output Gain"
};
