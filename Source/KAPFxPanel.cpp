/*
  ==============================================================================

    KAPFxPanel.cpp
    Created: 27 Apr 2019 6:53:10pm
    Author:  Eric

  ==============================================================================
*/

#include "KAPFxPanel.h"
#include "KAPParameters.h"
#include "KAPHelperFunctions.h"

KAPFxPanel::KAPFxPanel(KadenzeAudioPluginAudioProcessor* inProcessor)
:   KAPPanelBase(inProcessor)
{
    setSize(FX_PANEL_WIDTH,
            FX_PANEL_HEIGHT);
    
    auto& parameters = mProcessor->getParameters();
    AudioProcessorParameterWithID* delayType = (AudioProcessorParameterWithID*)parameters.getUnchecked(kParameter_DelayType);
    const int currentStyle = (int)delayType->getValue();
    setFxPanelStyle((KAPFxPanelStyle)currentStyle);
}

KAPFxPanel::~KAPFxPanel()
{
    
}

void KAPFxPanel::paint(Graphics& g)
{
    KAPPanelBase::paint(g);
    
    String label;
    
    switch(mStyle) {
        case kKAPFxPanelStyle_Delay:
            label = "DELAY";
            break;
        case kKAPFxPanelStyle_Chorus:
            label = "CHORUS";
            break;
        default:
        case kKAPFxPanelStyle_TotalNumStyles:
            jassertfalse;
    }
    
    g.setColour(KAPColour_5);
    g.setFont(font_3);
    
    g.drawText(label, 0, 0, getWidth(), 80, Justification::centred);
    
    for (int i = 0; i < mSliders.size(); i++)
    {
        paintComponentLabel(g, mSliders[i]);
    }
}

void KAPFxPanel::setFxPanelStyle(KAPFxPanelStyle inStyle)
{
    mStyle = inStyle;
    
    mSliders.clear();
    
    const int sliderSize = 56;
    int x = 130;
    int y = (getHeight() * 0.5) - (sliderSize * 0.5);
    
    switch(mStyle) {
        case kKAPFxPanelStyle_Delay:
        {
            KAPParameterSlider* time = new KAPParameterSlider(mProcessor->parameters, KAPParameterID[kParameter_DelayTime], KAPParameterLabel[kParameter_DelayTime]);
            time->setBounds(x, y, sliderSize, sliderSize);
            addAndMakeVisible(time);
            mSliders.add(time);
            x = x + sliderSize * 2;
            
            KAPParameterSlider* feedback = new KAPParameterSlider(mProcessor->parameters, KAPParameterID[kParameter_DelayFeedback], KAPParameterLabel[kParameter_DelayFeedback]);
            feedback->setBounds(x, y, sliderSize, sliderSize);
            addAndMakeVisible(feedback);
            mSliders.add(feedback);
            x = x + sliderSize * 2;
            
            KAPParameterSlider* wetDry = new KAPParameterSlider(mProcessor->parameters, KAPParameterID[kParameter_DelayWetDry], KAPParameterLabel[kParameter_DelayWetDry]);
            wetDry->setBounds(x, y, sliderSize, sliderSize);
            addAndMakeVisible(wetDry);
            mSliders.add(wetDry);
            x = x + sliderSize * 2;
            
            break;
        }
        case kKAPFxPanelStyle_Chorus:
        {
            KAPParameterSlider* rate = new KAPParameterSlider(mProcessor->parameters, KAPParameterID[kParameter_ModulationRate], KAPParameterLabel[kParameter_ModulationRate]);
            rate->setBounds(x, y, sliderSize, sliderSize);
            addAndMakeVisible(rate);
            mSliders.add(rate);
            x = x + sliderSize * 2;
            
            KAPParameterSlider* depth = new KAPParameterSlider(mProcessor->parameters, KAPParameterID[kParameter_ModulationDepth], KAPParameterLabel[kParameter_ModulationDepth]);
            depth->setBounds(x, y, sliderSize, sliderSize);
            addAndMakeVisible(depth);
            mSliders.add(depth);
            x = x + sliderSize * 2;
            
            KAPParameterSlider* wetDry = new KAPParameterSlider(mProcessor->parameters, KAPParameterID[kParameter_DelayWetDry], KAPParameterLabel[kParameter_DelayWetDry]);
            wetDry->setBounds(x, y, sliderSize, sliderSize);
            addAndMakeVisible(wetDry);
            mSliders.add(wetDry);
            x = x + sliderSize * 2;

            break;
        }
        default:
        case kKAPFxPanelStyle_TotalNumStyles:
            jassertfalse;
            break;
    }
    
    repaint();
}

void KAPFxPanel::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    KAPFxPanelStyle style = (KAPFxPanelStyle)comboBoxThatHasChanged->getSelectedItemIndex();
    setFxPanelStyle(style);
}
