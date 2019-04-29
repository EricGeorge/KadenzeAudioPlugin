/*
  ==============================================================================

    KAPHelperFunctions.h
    Created: 29 Apr 2019 11:58:52am
    Author:  Eric

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

inline void paintComponentLabel(Graphics& g, Component* inComponent)
{
    const int x = inComponent->getX() - (inComponent->getWidth() * 0.25f);
    const int y = inComponent->getY() + inComponent->getHeight();
    const int w = inComponent->getWidth() * 1.5f;
    const int h = 20;
    
    const String label = inComponent->getName();
    
    g.setColour(Colours::darkgrey);
    g.drawFittedText(label, x, y, w, h, Justification::centred, 1);
}
