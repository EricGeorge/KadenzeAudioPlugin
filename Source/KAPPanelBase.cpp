/*
  ==============================================================================

    KAPPanelBase.cpp
    Created: 27 Apr 2019 6:52:41pm
    Author:  Eric

  ==============================================================================
*/

#include "KAPPanelBase.h"
#include "KAPInterfaceDefines.h"

KAPPanelBase::KAPPanelBase(KadenzeAudioPluginAudioProcessor* inProcessor)
:   mProcessor(inProcessor)
{
}

KAPPanelBase::~KAPPanelBase()
{
}

void KAPPanelBase::mouseEnter(const MouseEvent& event)
{
    repaint();
}

void KAPPanelBase::mouseExit(const MouseEvent& event)
{
    repaint();
}

void KAPPanelBase::paint(Graphics& g)
{
    if (isMouseOver())
    {
//        g.setColour(KAPColour_4);
//        g.fillAll();
    }
}
