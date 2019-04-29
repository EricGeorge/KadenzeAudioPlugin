/*
  ==============================================================================

    KAPParameterComboBox.h
    Created: 28 Apr 2019 6:39:53pm
    Author:  Eric

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class KAPParameterComboBox
: public ComboBox
{
public:
    
    KAPParameterComboBox(AudioProcessorValueTreeState& stateToControl,
                       const String& parameterID);
    
    ~KAPParameterComboBox();
    
private:
    
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> mAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KAPParameterComboBox);
};
