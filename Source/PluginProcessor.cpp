/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "KAPParameters.h"

//==============================================================================
KadenzeAudioPluginAudioProcessor::KadenzeAudioPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
    parameters(*this, nullptr)
#endif
{
    initializeParameters();
    initializeDSP();
    
    mPresetManager.reset(new KAPPresetManager(this));
}

KadenzeAudioPluginAudioProcessor::~KadenzeAudioPluginAudioProcessor()
{
}

//==============================================================================
const String KadenzeAudioPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool KadenzeAudioPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool KadenzeAudioPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool KadenzeAudioPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double KadenzeAudioPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int KadenzeAudioPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int KadenzeAudioPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void KadenzeAudioPluginAudioProcessor::setCurrentProgram (int index)
{
}

const String KadenzeAudioPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void KadenzeAudioPluginAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void KadenzeAudioPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    for (int i = 0; i < 2; i++)
    {
        mDelay[i]->setSampleRate(sampleRate);
        mLfo[i]->setSampleRate(sampleRate);
    }
}

void KadenzeAudioPluginAudioProcessor::releaseResources()
{
    for (int i = 0; i < 2; i++)
    {
        mDelay[i]->reset();
        mLfo[i]->reset();
    }
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool KadenzeAudioPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void KadenzeAudioPluginAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        
        mInputGain[channel]->process(channelData,
                                getParameter(kParameter_InputGain),
                                channelData,
                                buffer.getNumSamples());
        
        // a chorus should only modulate 1 channel
        float rate = channel==0 ? getParameter(kParameter_ModulationRate): 0;
        
        mLfo[channel]->process(rate,
                               getParameter(kParameter_ModulationDepth),
                               buffer.getNumSamples());
        
        mDelay[channel]->process(channelData,
                                 getParameter(kParameter_DelayTime),
                                 getParameter(kParameter_DelayFeedback),
                                 getParameter(kParameter_DelayWetDry),
                                 getParameter(kParameter_DelayType),
                                 mLfo[channel]->getBuffer(),
                                 channelData,
                                 buffer.getNumSamples());
        
        mOutputGain[channel]->process(channelData,
                                     getParameter(kParameter_OutputGain),
                                     channelData,
                                     buffer.getNumSamples());

    }
}

//==============================================================================
bool KadenzeAudioPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* KadenzeAudioPluginAudioProcessor::createEditor()
{
    return new KadenzeAudioPluginAudioProcessorEditor (*this);
}

//==============================================================================
void KadenzeAudioPluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    
    XmlElement preset("KAP_StateInfo");
    XmlElement* presetBody = new XmlElement("KAP_Preset");
    
    mPresetManager->getXmlForPreset(presetBody);
    preset.addChildElement(presetBody);
    copyXmlToBinary(preset, destData);
}

void KadenzeAudioPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
 
    if (xmlState)
    {
        forEachXmlChildElement(*xmlState, subChild)
        {
            mPresetManager->loadPresetForXml(subChild);
        }
        
    }
    else
    {
        jassertfalse;
    }
}

float KadenzeAudioPluginAudioProcessor::getInputMeterGainLevel(int inChannel)
{
    const float normalizeddB = dbToNormalizedGain(mInputGain[inChannel]->getMeterLeve());
    return normalizeddB;
}

float KadenzeAudioPluginAudioProcessor::getOutputMeterGainLevel(int inChannel)
{
    const float normalizeddB = dbToNormalizedGain(mOutputGain[inChannel]->getMeterLeve());
    return normalizeddB;
}

void KadenzeAudioPluginAudioProcessor::initializeDSP()
{
    for (int i = 0; i < 2; i++)
    {
        mInputGain[i].reset(new KAPGain());
        mOutputGain[i].reset(new KAPGain());
        mDelay[i].reset(new KAPDelay());
        mLfo[i].reset(new KAPLfo());
    }
}

void KadenzeAudioPluginAudioProcessor::initializeParameters()
{
    for (int i = 0; i < kParameter_TotalNumParameters; i++)
    {
        parameters.createAndAddParameter(KAPParameterID[i],
                                         KAPParameterID[i],
                                         KAPParameterLabel[i],
                                         NormalisableRange<float>(0.0f, 1.0f),
                                         0.5f,
                                         nullptr,
                                         nullptr);
    }
    
    parameters.state = ValueTree("foo");    // do this to avoid the assert in the newer version of JUCE
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new KadenzeAudioPluginAudioProcessor();
}
