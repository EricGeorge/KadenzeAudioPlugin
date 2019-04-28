/*
  ==============================================================================

    KAPFxPanel.cpp
    Created: 27 Apr 2019 6:53:10pm
    Author:  Eric

  ==============================================================================
*/

#include "KAPFxPanel.h"

KAPFxPanel::KAPFxPanel(KadenzeAudioPluginAudioProcessor* inProcessor)
:   KAPPanelBase(inProcessor),
    mStyle(kKAPFxPanelStyle_Delay)
{
    setSize(FX_PANEL_WIDTH,
            FX_PANEL_HEIGHT);
}

KAPFxPanel::~KAPFxPanel()
{
    
}

void KAPFxPanel::paint(Graphics& g)
{
    KAPPanelBase::paint(g);
    
    switch(mStyle) {
        case kKAPFxPanelStyle_Delay:
            g.drawFittedText("DELAY",
                             0,
                             0,
                             getWidth(),
                             getHeight(),
                             Justification::centred,
                             1);
            break;
        case kKAPFxPanelStyle_Chorus:
            g.drawFittedText("CHORUS",
                             0,
                             0,
                             getWidth(),
                             getHeight(),
                             Justification::centred,
                             1);
            break;
        default:
        case kKAPFxPanelStyle_TotalNumStyles:
            // should make kKAPFxPanelStyle_TotalNumStyles = last style (kKAPFxPanelStyle_Chorus) instead!
            jassertfalse;
            break;
    }
}

void KAPFxPanel::setFxPanelStyle(KAPFxPanelStyle inStyle)
{
    mStyle = inStyle;
}
