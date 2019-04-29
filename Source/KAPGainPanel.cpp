/*
  ==============================================================================

    KAPGainPanel.cpp
    Created: 27 Apr 2019 6:53:30pm
    Author:  Eric

  ==============================================================================
*/

#include "KAPGainPanel.h"
#include "KAPParameters.h"

KAPGainPanel::KAPGainPanel(KadenzeAudioPluginAudioProcessor* inProcessor)
: KAPPanelBase(inProcessor)
{
    setSize(GAIN_PANEL_WIDTH,
            GAIN_PANEL_HEIGHT);
}

KAPGainPanel::~KAPGainPanel()
{
    
}

void KAPGainPanel::setParameterID(int inParameterID)
{
    mSlider.reset(new KAPParameterSlider(mProcessor->parameters, KAPParameterID[inParameterID]));
    
    const int sliderSize = 54;
    
    mSlider->setBounds((getWidth() * 0.5f) - (sliderSize * 0.5),
                       (getHeight() * 0.5f) - (sliderSize * 0.5),
                       sliderSize,
                       sliderSize);
    
    addAndMakeVisible(mSlider.get());
}
