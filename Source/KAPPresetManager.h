/*
  ==============================================================================

    KAPPresetManager.h
    Created: 30 Apr 2019 8:44:38pm
    Author:  Eric

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

#define PRESET_FILE_EXTENSION ".kpf"

class KAPPresetManager
{
public:
    KAPPresetManager(AudioProcessor* inProcessor);
    ~KAPPresetManager();
    
    void getXmlForPreset(XmlElement* inElement);
    void loadPresetForXml(XmlElement* inElement);
    
    int getNumberOfPresets();
    String getPresetName(int inPresetIndex);
    void createNewPreset();
    void savePreset();
    void saveAsPreset(String inPresetName);
    void loadPreset(int inPresetIndex);
    bool getIsCurrentPresetSaved();
    String getCurrentPresetName();
    
private:
    bool mCurrentPresetIsSaved;
    File mCurrentlyLoadedPreset;
    Array<File> mLocalPresets;
    String mCurrentPresetName;
    String mPresetDirectory;
    
    AudioProcessor* mProcessor;
    XmlElement* mCurrentPresetXml;
    
    void storeLocalPreset();
};
