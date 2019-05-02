/*
  ==============================================================================

    KAPGainPanel.cpp
    Created: 27 Apr 2019 6:53:30pm
    Author:  Eric

  ==============================================================================
*/

#include "KAPGainPanel.h"
#include "KAPParameters.h"
#include "KAPHelperFunctions.h"

KAPGainPanel::KAPGainPanel(KadenzeAudioPluginAudioProcessor* inProcessor)
: KAPPanelBase(inProcessor)
{
    setSize(GAIN_PANEL_WIDTH,
            GAIN_PANEL_HEIGHT);
}

KAPGainPanel::~KAPGainPanel()
{
    
}

void KAPGainPanel::paint(Graphics& g)
{
    KAPPanelBase::paint(g);
    
    if (mSlider != nullptr)
    {
       paintComponentLabel(g, mSlider.get());
    }
}

void KAPGainPanel::setParameterID(int inParameterID)
{
    mSlider.reset(new KAPParameterSlider(mProcessor->parameters, KAPParameterID[inParameterID], KAPParameterLabel[inParameterID]));
    
    const int sliderSize = 54;
    
    mSlider->setBounds((getWidth() * 0.5f) - (sliderSize * 0.5),
                       (getHeight() * 0.5f) - (sliderSize * 0.5),
                       sliderSize,
                       sliderSize);
    
    addAndMakeVisible(mSlider.get());
}
