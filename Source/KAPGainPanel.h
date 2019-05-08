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
#include "KAPVuMeter.h"

class KAPGainPanel  : public KAPPanelBase
{
public:
    KAPGainPanel(KadenzeAudioPluginAudioProcessor* inProcessor);
    ~KAPGainPanel();
    
    void setParameterID(int inParameterID);
    
    void paint(Graphics& g) override;
    
private:
    std::unique_ptr<KAPParameterSlider> mSlider;
    std::unique_ptr<KAPVuMeter> mVuMeter;
};
