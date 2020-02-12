/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#define DAMP_ID "damp"
#define DAMP_NAME "Damp"
#define ROOM_ID "room"
#define ROOM_NAME "Room"
#define WET_ID "wet"
#define WET_NAME "Wet"
#define DRY_ID "dry"
#define DRY_NAME "Dry"
#define WIDTH_ID "width"
#define WIDTH_NAME "Width"
#define FREEZE_ID "freeze"
#define FREEZE_NAME "Freeze"

//==============================================================================
/**
*/
class MetsReverbAudioProcessor  : public AudioProcessor,
                                  public ValueTree::Listener
{
public:
    //==============================================================================
    MetsReverbAudioProcessor();
    ~MetsReverbAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

            float roomSize;     /**< Room size, 0 to 1.0, where 1.0 is big, 0 is small. */
            float damping;      /**< Damping, 0 to 1.0, where 0 is not damped, 1.0 is fully damped. */
            float wetLevel;     /**< Wet level, 0 to 1.0 */
            float dryLevel;     /**< Dry level, 0 to 1.0 */
            float width;        /**< Reverb width, 0 to 1.0, where 1.0 is very wide. */
            float freezeMode;   /**< Freeze mode - values < 0.5 are "normal" mode, values > 0.5 */
                                /*put the reverb into a continuous feedback loop. */
    // AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
     ValueTree getState() const { return state; }

private:
        class Reverb theReverb;
        Reverb::Parameters theReverbParameters;
        Slider wetSlider;
        Slider drySlider;
        Slider dampSlider;
        Slider roomSlider;
        Slider widthSlider;
        ToggleButton freeze;
        ValueTree state;
        //ToggleSwitch freeze;
    public:
        AudioProcessorValueTreeState parameters;
//==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MetsReverbAudioProcessor)
};
