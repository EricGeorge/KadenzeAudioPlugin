/*
  ==============================================================================

    KAPTopPanel.h
    Created: 27 Apr 2019 6:53:47pm
    Author:  Eric

  ==============================================================================
*/

#pragma once

#include "KAPPanelBase.h"

class KAPTopPanel : public KAPPanelBase,
                    public Button::Listener,
                    public ComboBox::Listener
{
public:
    KAPTopPanel(KadenzeAudioPluginAudioProcessor* inProcessor);
    ~KAPTopPanel();
    
    void paint(Graphics& g) override;
    
    void buttonClicked(Button* b) override;
    void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;
    
private:
    std::unique_ptr<ComboBox> mPresetDisplay;
    std::unique_ptr<TextButton> mNewPreset, mSavePreset, mSaveAsPreset;
    
    void displaySaveAsPopup();
    void updatePresetComboBox();
};
