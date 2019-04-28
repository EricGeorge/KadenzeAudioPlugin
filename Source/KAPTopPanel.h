/*
  ==============================================================================

    KAPTopPanel.h
    Created: 27 Apr 2019 6:53:47pm
    Author:  Eric

  ==============================================================================
*/

#pragma once

#include "KAPPanelBase.h"

class KAPTopPanel
:   public KAPPanelBase
{
public:
    
    KAPTopPanel(KadenzeAudioPluginAudioProcessor* inProcessor);
    ~KAPTopPanel();

    void paint(Graphics& g) override;
};
