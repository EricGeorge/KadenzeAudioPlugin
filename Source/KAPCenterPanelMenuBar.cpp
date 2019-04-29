/*
  ==============================================================================

    KAPCenterPanelMenuBar.cpp
    Created: 27 Apr 2019 6:53:05pm
    Author:  Eric

  ==============================================================================
*/

#include "KAPCenterPanelMenuBar.h"
#include "KAPParameters.h"

KAPCenterPanelMenuBar::KAPCenterPanelMenuBar(KadenzeAudioPluginAudioProcessor* inProcessor)
: KAPPanelBase(inProcessor)
{
    setSize(CENTER_PANEL_MENU_BAR_WIDTH,
            CENTER_PANEL_MENU_BAR_HEIGHT);
    
    const int width = 85;
    
    mFxTypeComboBox.reset(new KAPParameterComboBox(mProcessor->parameters, KAPParameterID[kParameter_DelayType]));
    mFxTypeComboBox->setBounds(getWidth() - width, 0, width, getHeight());
    mFxTypeComboBox->addItem("DELAY", 1);
    mFxTypeComboBox->addItem("CHORUS", 2);
    mFxTypeComboBox->setSelectedItemIndex((int)mProcessor->getParameter(kParameter_DelayType), dontSendNotification);
    addAndMakeVisible(mFxTypeComboBox.get());
}

KAPCenterPanelMenuBar::~KAPCenterPanelMenuBar()
{
    
}

void KAPCenterPanelMenuBar::addFxTypeComboBoxListener(ComboBox::Listener* inListener)
{
    mFxTypeComboBox->addListener(inListener);
}

void KAPCenterPanelMenuBar::removeFxTypeComboBoxListener(ComboBox::Listener* inListener)
{
    mFxTypeComboBox->removeListener(inListener);
}
