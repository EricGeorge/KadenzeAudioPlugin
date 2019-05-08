/*
  ==============================================================================

    KAPParameterSlider.h
    Created: 28 Apr 2019 6:39:42pm
    Author:  Eric

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class KAPParameterSlider  : public Slider
{
public:
    KAPParameterSlider(AudioProcessorValueTreeState& stateToControl,
                       const String& parameterID,
                       const String& parameterLabel);
    ~KAPParameterSlider();
    
private:
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mAttachment;
};
