/*
  ==============================================================================

    KAPCenterPanel.cpp
    Created: 27 Apr 2019 6:52:50pm
    Author:  Eric

  ==============================================================================
*/

#include "KAPCenterPanel.h"

KAPCenterPanel::KAPCenterPanel(KadenzeAudioPluginAudioProcessor* inProcessor)
:   KAPPanelBase(inProcessor)
{
    setSize(centerPanelWidth,
            centerPanelHeight);
    
    mMenuBar.reset(new KAPCenterPanelMenuBar(inProcessor));
    mMenuBar->setTopLeftPosition(0, 0);
    addAndMakeVisible(mMenuBar.get());
    
    mFxPanel.reset(new KAPFxPanel(inProcessor));
    mFxPanel->setTopLeftPosition(0, centerPanelMenuBarHeight);
    addAndMakeVisible(mFxPanel.get());
    
    mMenuBar->addFxTypeComboBoxListener(mFxPanel.get());
}

KAPCenterPanel::~KAPCenterPanel()
{
    mMenuBar->removeFxTypeComboBoxListener(mFxPanel.get());
}
