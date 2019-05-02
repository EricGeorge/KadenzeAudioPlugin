/*
  ==============================================================================

    KAPParameterSlider.cpp
    Created: 28 Apr 2019 6:39:42pm
    Author:  Eric

  ==============================================================================
*/

#include "KAPParameterSlider.h"


KAPParameterSlider::KAPParameterSlider(AudioProcessorValueTreeState& stateToControl,
                                       const String& parameterID,
                                       const String& parameterLabel)
:   juce::Slider(parameterLabel)
{
    setSliderStyle(SliderStyle::RotaryHorizontalVerticalDrag);
    setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 0, 0);
    setRange(0.0f, 1.0f, 0.001f);
    
    mAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(stateToControl,
                                                                         parameterID,
                                                                         *this));
}

KAPParameterSlider::~KAPParameterSlider()
{
    
}
