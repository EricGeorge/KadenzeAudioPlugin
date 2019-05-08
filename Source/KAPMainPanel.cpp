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
:   KAPPanelBase(inProcessor)
{
    setSize(mainPanelWidth,
            mainPanelHeight);
    
    mTopPanel.reset(new KAPTopPanel(inProcessor));
    mTopPanel->setTopLeftPosition(0, 0);
    addAndMakeVisible(mTopPanel.get());
    
    mInputGainPanel.reset(new KAPGainPanel(inProcessor));
    mInputGainPanel->setTopLeftPosition(0, topPanelHeight);
    mInputGainPanel->setParameterID(kParameter_InputGain);
    addAndMakeVisible(mInputGainPanel.get());

    mOutputGainPanel.reset(new KAPGainPanel(inProcessor));
    mOutputGainPanel->setTopLeftPosition(mainPanelWidth - gainPanelWidth , topPanelHeight);
    mOutputGainPanel->setParameterID(kParameter_OutputGain);
    addAndMakeVisible(mOutputGainPanel.get());
    
    mCenterPanel.reset(new KAPCenterPanel(inProcessor));
    mCenterPanel->setTopLeftPosition(gainPanelWidth, topPanelHeight);
    addAndMakeVisible(mCenterPanel.get());
}

KAPMainPanel::~KAPMainPanel()
{
}
