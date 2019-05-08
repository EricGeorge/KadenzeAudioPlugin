/*
  ==============================================================================

    KAPCenterPanelMenuBar.h
    Created: 27 Apr 2019 6:53:05pm
    Author:  Eric

  ==============================================================================
*/

#pragma once

#include "KAPPanelBase.h"
#include "KAPParameterComboBox.h"

class KAPCenterPanelMenuBar  : public KAPPanelBase
{
public:
    KAPCenterPanelMenuBar(KadenzeAudioPluginAudioProcessor* inProcessor);
    ~KAPCenterPanelMenuBar();
    
    void addFxTypeComboBoxListener(ComboBox::Listener* inListener);
    void removeFxTypeComboBoxListener(ComboBox::Listener* inListener);

private:
    std::unique_ptr<KAPParameterComboBox> mFxTypeComboBox;
};
