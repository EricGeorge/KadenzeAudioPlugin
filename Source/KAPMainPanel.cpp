/*
  ==============================================================================

    KAPMainPanel.cpp
    Created: 27 Apr 2019 6:53:41pm
    Author:  Eric

  ==============================================================================
*/

#include "KAPMainPanel.h"
#include "KAPParameters.h"


KAPMainPanel::KAPMainPanel(KadenzeAudioPluginAudioProcessor* inProcessor)
: KAPPanelBase(inProcessor)
{
    setSize(MAIN_PANEL_WIDTH,
            MAIN_PANEL_HEIGHT);
    
    mTopPanel.reset(new KAPTopPanel(inProcessor));
    mTopPanel->setTopLeftPosition(0, 0);
    addAndMakeVisible(mTopPanel.get());
    
    mInputGainPanel.reset(new KAPGainPanel(inProcessor));
    mInputGainPanel->setTopLeftPosition(0, TOP_PANEL_HEIGHT);
    mInputGainPanel->setParameterID(kParameter_InputGain);
    addAndMakeVisible(mInputGainPanel.get());

    mOutputGainPanel.reset(new KAPGainPanel(inProcessor));
    mOutputGainPanel->setTopLeftPosition(MAIN_PANEL_WIDTH - GAIN_PANEL_WIDTH , TOP_PANEL_HEIGHT);
    mOutputGainPanel->setParameterID(kParameter_OutputGain);
    addAndMakeVisible(mOutputGainPanel.get());
    
    mCenterPanel.reset(new KAPCenterPanel(inProcessor));
    mCenterPanel->setTopLeftPosition(GAIN_PANEL_WIDTH, TOP_PANEL_HEIGHT);
    addAndMakeVisible(mCenterPanel.get());
}

KAPMainPanel::~KAPMainPanel()
{
    
}
