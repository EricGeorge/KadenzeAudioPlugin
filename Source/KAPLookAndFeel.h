/*
  ==============================================================================

    KAPLookAndFeel.h
    Created: 2 May 2019 7:03:40pm
    Author:  Eric

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class KAPLookAndFeel  : public LookAndFeel_V4
{
public:
    KAPLookAndFeel()
    {
        mSliderImage = ImageCache::getFromMemory(BinaryData::kadenze_knob_png, BinaryData::kadenze_knob_pngSize);
        
        setColour(ComboBox::backgroundColourId, KAPColour_3);
        setColour(ComboBox::outlineColourId, KAPColour_2);
        setColour(ComboBox::arrowColourId, KAPColour_1);
        setColour(ComboBox::textColourId, KAPColour_1);
        
        setColour(TextButton::buttonColourId, KAPColour_1);
        setColour(TextButton::textColourOnId, KAPColour_1);
        setColour(TextButton::textColourOffId, KAPColour_1);
    }
    
    ~KAPLookAndFeel()
    {
    };
    
    /** buttons */
    
    Font getTextButtonFont(TextButton&, int buttonHeight) override
    {
        return font_1;
    }
    
    void drawButtonBackground (Graphics& g,
                               Button& button,
                               const Colour& backgroundColour,
                               bool shouldDrawButtonAsHighlighted,
                               bool shouldDrawButtonAsDown) override
    {
        Colour fillColour;
        
        if (shouldDrawButtonAsDown)
        {
            fillColour = KAPColour_6;
        }
        else if (shouldDrawButtonAsHighlighted)
        {
            fillColour = KAPColour_5;
        }
        else
        {
            fillColour = KAPColour_3;
        }
        
        const float cornerSize = 6.0f;
        const Rectangle<float> bounds = button.getLocalBounds().toFloat().reduced(0.5f, 0.5f);
        
        g.setColour(fillColour);
        g.fillRoundedRectangle(bounds.reduced(1), cornerSize);
    }
    
    /** comboBoxes */
    Font getLabelFont(Label& label) override
    {
        return font_1;
    }
    
    void drawPopupMenuItem (Graphics& g,
                            const Rectangle<int>& area,
                            bool isSeparator,
                            bool isActive,
                            bool isHighlighted,
                            bool isTicked,
                            bool hasSubMenu,
                            const String& text,
                            const String& shortcutKeyText,
                            const Drawable* icon,
                            const Colour* textColour) override
    {
        juce::Rectangle<int> r(area);

        Colour fillColour = isHighlighted ? KAPColour_5 : KAPColour_4;
        g.setColour(fillColour);
        g.fillRect(r.getX(), r.getY(), r.getWidth(), r.getHeight() - 1);

        Colour myTextColour = isTicked ? KAPColour_7 : KAPColour_1;
        g.setColour(myTextColour);
        g.setFont(font_1);

        r.setLeft(10);
        r.setY(1);
        g.drawFittedText(text, r, Justification::left, 1);
    }

    void drawComboBox (Graphics& g,
                       int width,
                       int height,
                       bool isButtonDown,
                       int buttonX,
                       int buttonY,
                       int buttonW,
                       int buttonH,
                       ComboBox& box) override
    {
        const float cornerSize = 3.0f;
        const juce::Rectangle<int> boxBounds(0, 0, width, height);
        
        g.setColour(KAPColour_3);
        g.fillRoundedRectangle(boxBounds.toFloat(), cornerSize);
        
        juce::Rectangle<int> arrow(width - 30, 0, 20, height);
        
        Path path;
        path.startNewSubPath(arrow.getX() + 3.0f, arrow.getCentreY() - 2.0f);
        path.lineTo(arrow.toFloat().getCentreX(), arrow.toFloat().getCentreY() + 3.0f);
        path.lineTo(arrow.toFloat().getRight() - 3.0f, arrow.toFloat().getCentreY() - 2.0f);
        
        Colour arrowColor = box.findColour(ComboBox::arrowColourId).withAlpha(box.isEnabled() ? 0.9f : 0.2f);
        g.setColour(arrowColor);
        g.strokePath(path, PathStrokeType(2.0f));
    }
    
    
    /** sliders */
    void drawRotarySlider (Graphics& g,
                           int x,
                           int y,
                           int width,
                           int height,
                           float sliderPosProportional,
                           float rotaryStartAngle,
                           float rotaryEndAngle,
                           Slider& slider) override
    {
        const int numFrames = mSliderImage.getHeight() / mSliderImage.getWidth();
        const int frameIndex = (int)std::ceil(sliderPosProportional * (numFrames - 1));
        
        const float radius = jmin(width * 0.5f, height * 0.5f);
        const float centreX = x + width * 0.5f;
        const float centreY = y + width * 0.5f;
        const float rx = centreX - radius;
        const float ry = centreY - radius;
        
        g.drawImage(mSliderImage,
                    rx,
                    ry,
                    2 * radius,
                    2 * radius,
                    0,
                    frameIndex * mSliderImage.getWidth(),
                    mSliderImage.getWidth(),
                    mSliderImage.getWidth());
    }
    
private:
    Image mSliderImage;
};
