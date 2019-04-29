/*
  ==============================================================================

    KAPGainPanel.h
    Created: 27 Apr 2019 6:53:30pm
    Author:  Eric

  ==============================================================================
*/

#pragma once

#include "KAPPanelBase.h"
#include "KAPParameterSlider.h"

class KAPGainPanel
:   public KAPPanelBase
{
public:
    
    KAPGainPanel(KadenzeAudioPluginAudioProcessor* inProcessor);
    ~KAPGainPanel();
    
    void setParameterID(int inParameterID);
    
private:
    
    std::unique_ptr<KAPParameterSlider> mSlider;
};
