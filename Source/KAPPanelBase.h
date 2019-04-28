/*
  ==============================================================================

    KAPPanelBase.h
    Created: 27 Apr 2019 6:52:41pm
    Author:  Eric

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "KAPInterfaceDefines.h"

class KAPPanelBase
: public Component
{
public:
    KAPPanelBase(KadenzeAudioPluginAudioProcessor* inProcessor);
    ~KAPPanelBase();
    
    void paint(Graphics& g) override;
    
protected:
    KadenzeAudioPluginAudioProcessor* mProcessor;
};
