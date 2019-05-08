/*
  ==============================================================================

    KAPVuMeter.h
    Created: 6 May 2019 7:38:11pm
    Author:  Eric

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"

class KAPVuMeter  : public Component,
                    public Timer
{
public:
    KAPVuMeter(KadenzeAudioPluginAudioProcessor* inProcessor);
    ~KAPVuMeter();
    
    void paint(Graphics& g) override;
    
    void timerCallback() override;
    
    void setParameterID(int inParameterID);
    
private:
    int mParameterID;
    
    float mCh0Level;
    float mCh1Level;
    
    KadenzeAudioPluginAudioProcessor* mProcessor;
};
