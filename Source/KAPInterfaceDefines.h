/*
  ==============================================================================

    KAPInterfaceDefines.h
    Created: 27 Apr 2019 7:03:24pm
    Author:  Eric

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

const int mainPanelWidth = 750;
const int mainPanelHeight = 300;

const int topPanelWidth = mainPanelWidth;
const int topPanelHeight = 45;

const int gainPanelWidth = 100;
const int gainPanelHeight = mainPanelHeight - topPanelHeight;

const int centerPanelWidth = mainPanelWidth - (gainPanelWidth * 2);
const int centerPanelHeight = gainPanelHeight;

const int centerPanelMenuBarWidth = centerPanelWidth;
const int centerPanelMenuBarHeight = 35;

const int fxPanelWidth = centerPanelWidth;
const int fxPanelHeight = centerPanelHeight - centerPanelMenuBarHeight;

const Colour KAPColour_1 = Colour(105, 105, 105);
const Colour KAPColour_2 = Colour(0, 0, 0).withAlpha(0.0f);
const Colour KAPColour_3 = Colour(0, 0, 0).withAlpha(0.3f);
const Colour KAPColour_4 = Colour(0, 0, 0).withAlpha(0.6f);
const Colour KAPColour_5 = Colour(105, 105, 105).withAlpha(0.3f);
const Colour KAPColour_6 = Colour(0, 0, 0).withAlpha(0.8f);
const Colour KAPColour_7 = Colour(125, 125, 125);

const Font font_1("Helvetica Neue", 12.00f, Font::bold);
const Font font_2("Helvetica Neue", 22.00f, Font::bold);
const Font font_3("Helvetica Neue", 48.00f, Font::bold);
