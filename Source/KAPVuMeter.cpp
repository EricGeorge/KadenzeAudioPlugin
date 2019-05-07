/*
  ==============================================================================

    KAPVuMeter.cpp
    Created: 6 May 2019 7:38:11pm
    Author:  Eric

  ==============================================================================
*/

#include "KAPVuMeter.h"
#include "KAPInterfaceDefines.h"
#include "KAPParameters.h"

KAPVuMeter::KAPVuMeter(KadenzeAudioPluginAudioProcessor* inProcessor)
:   mParameterID(-1),
    mCh0Level(0),
    mCh1Level(0),
    mProcessor(inProcessor)
{
    
}

KAPVuMeter::~KAPVuMeter()
{
    
}

void KAPVuMeter::paint(Graphics& g)
{
    const int meterWidth = getWidth() / 3;
    
    g.setColour(KAPColour_6);
    
    g.fillRect(0, 0, meterWidth, getHeight());
    g.fillRect(meterWidth * 2, 0, meterWidth, getHeight());
    
    int ch0Fill = getHeight() - (getHeight() * mCh0Level);
    int ch1Fill = getHeight() - (getHeight() * mCh1Level);
    
    if (ch0Fill < 0)
    {
        ch0Fill = 0;
    }
    
    if (ch1Fill < 0)
    {
        ch1Fill = 0;
    }
    
    g.setColour(KAPColour_7);
    g.fillRect(0, ch0Fill, meterWidth, getHeight());
    g.fillRect(meterWidth * 2, ch1Fill, meterWidth, getHeight());
}

void KAPVuMeter::timerCallback()
{
    float updatedCh0Level = 0.0f;
    float updatedCh1Level = 0.0f;
    
    switch (mParameterID)
    {
        case kParameter_InputGain:
            updatedCh0Level = mProcessor->getInputMeterGainLevel(0);
            updatedCh1Level = mProcessor->getInputMeterGainLevel(1);
            break;
            
        case kParameter_OutputGain:
            updatedCh0Level = mProcessor->getOutputMeterGainLevel(0);
            updatedCh1Level = mProcessor->getOutputMeterGainLevel(1);
            break;
    }
    
    if (updatedCh0Level > mCh0Level)
    {
        mCh0Level = updatedCh0Level;
    }
    else
    {
        mCh0Level = kMeterSmoothingCoeff * (mCh0Level - updatedCh0Level) + updatedCh0Level;
    }
    
    if (updatedCh1Level > mCh1Level)
    {
        mCh1Level = updatedCh1Level;
    }
    else
    {
        mCh1Level = kMeterSmoothingCoeff * (mCh1Level - updatedCh1Level) + updatedCh1Level;
    }
    
    mCh0Level = kap_denormalize(mCh0Level);
    mCh1Level = kap_denormalize(mCh1Level);
    
    if (mCh0Level && mCh1Level)
    {
        repaint();
    }
}

void KAPVuMeter::setParameterID(int inParameterID)
{
    mParameterID = inParameterID;
    
    startTimerHz(15);
}
