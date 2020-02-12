/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MetsReverbAudioProcessor::MetsReverbAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),   parameters (*this, nullptr, Identifier ("parameters"), { std::make_unique<AudioParameterFloat> ("damp", "Damp", 0.0, 1.0, 0.0), std::make_unique<AudioParameterFloat> ("width", "Width", 0.0f, 1.0f, 0.0f), std::make_unique<AudioParameterFloat> ("dry", "Dry", 0.0f, 0.6f, 0.0f), std::make_unique<AudioParameterFloat> ("wet", "Wet", 0.0f, 0.6f, 0.0f), std::make_unique<AudioParameterFloat> ("room", "Room", 0.0f, 1.0f, 0.0f), std::make_unique<AudioParameterInt> ("freeze", "Freeze", 0, 1, 0) } )
#endif
{
}

MetsReverbAudioProcessor::~MetsReverbAudioProcessor()
{
}

//==============================================================================
const String MetsReverbAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MetsReverbAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MetsReverbAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MetsReverbAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MetsReverbAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MetsReverbAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MetsReverbAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MetsReverbAudioProcessor::setCurrentProgram (int index)
{
}

const String MetsReverbAudioProcessor::getProgramName (int index)
{
    return {};
}

void MetsReverbAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MetsReverbAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    theReverb.setSampleRate(sampleRate);
}

void MetsReverbAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MetsReverbAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void MetsReverbAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
        //Rilevamento I/O
        ScopedNoDenormals noDenormals;
        auto totalNumInputChannels  = getTotalNumInputChannels();
        auto totalNumOutputChannels = getTotalNumOutputChannels();

        //Pulizia del buffer
        for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
            buffer.clear (i, 0, buffer.getNumSamples());
        //Elaborazione dei dati

        theReverbParameters.dryLevel = dryLevel;
        theReverbParameters.wetLevel = wetLevel;
        theReverbParameters.roomSize = roomSize;
        theReverbParameters.damping = damping;
        theReverbParameters.width = width;
        theReverbParameters.freezeMode = freezeMode;
    
    
        theReverb.getParameters();
        theReverb.setParameters(theReverbParameters);

            const auto numChannels = jmin (totalNumInputChannels, totalNumOutputChannels);
    if (numChannels == 1)
        theReverb.processMono(buffer.getWritePointer(0), buffer.getNumSamples());
    else if (numChannels == 2)
        theReverb.processStereo(buffer.getWritePointer(0), buffer.getWritePointer(1), buffer.getNumSamples());
}

//==============================================================================
bool MetsReverbAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MetsReverbAudioProcessor::createEditor()
{
    return new MetsReverbAudioProcessorEditor (*this);
}

//==============================================================================
void MetsReverbAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void MetsReverbAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (parameters.state.getType()))
            parameters.replaceState (ValueTree::fromXml (*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MetsReverbAudioProcessor();
}
