/*
  ==============================================================================

    KAPParameterComboBox.cpp
    Created: 28 Apr 2019 6:39:53pm
    Author:  Eric

  ==============================================================================
*/

#include "KAPParameterComboBox.h"

KAPParameterComboBox::KAPParameterComboBox(AudioProcessorValueTreeState& stateToControl,
                                           const String& parameterID)
:   juce::ComboBox(parameterID)
{
    
    mAttachment.reset(new AudioProcessorValueTreeState::ComboBoxAttachment(stateToControl,
                                                                           parameterID,
                                                                           *this));
}

KAPParameterComboBox::~KAPParameterComboBox()
{
}
