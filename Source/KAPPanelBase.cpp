/*
  ==============================================================================

    KAPPanelBase.cpp
    Created: 27 Apr 2019 6:52:41pm
    Author:  Eric

  ==============================================================================
*/

#include "KAPPanelBase.h"

KAPPanelBase::KAPPanelBase(KadenzeAudioPluginAudioProcessor* inProcessor)
: mProcessor(inProcessor)
{
    
}

KAPPanelBase::~KAPPanelBase()
{
    
}

void KAPPanelBase::paint(Graphics& g)
{
    g.setColour(Colours::whitesmoke);
    g.fillAll();
    
    g.setColour(Colours::black);
    g.drawRoundedRectangle(0,
                           0,
                           getWidth(),
                           getHeight(),
                           4,
                           2);
}
