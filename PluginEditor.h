/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/

class SliderLookAndFeel : public LookAndFeel_V4
{
public:
    
    void drawRotarySlider (Graphics &g, int x, int y, int width, int height, float sliderPos,
                           float rotaryStartAngle, float rotaryEndAngle, Slider &slider) override
    {
        
        //Create Varible for entire Knob.
        knobMaster = ImageCache::getFromMemory(BinaryData::knobMaster_png ,BinaryData::knobMaster_pngSize);
        
        float angle = rotaryStartAngle + (sliderPos * (rotaryEndAngle - rotaryStartAngle));

        //Draw Knob.
        //knobMaster.getWidth() /2, knobMaster.getHeight() /2 Changes the point of rotation.
        g.drawImageTransformed(knobMaster, AffineTransform::rotation(angle, knobMaster.getWidth() /2, knobMaster.getHeight() /2));
        
    }
    
    void drawToggleButton (Graphics &, ToggleButton &, bool, bool) override
    {
        Buttons = ImageCache::getFromMemory(BinaryData::normal_switch_png, BinaryData::normal_switch_pngSize);
    }
        
    void drawLinearSlider (Graphics &g, int x, int y, int width, int height, float sliderPos,
                           float minSliderPos, float maxSliderPos, const Slider::SliderStyle, Slider &slider) override
    {
        Sliders = ImageCache::getFromMemory(BinaryData::faderMaster_png, BinaryData::faderMaster_pngSize);
        //create variable for slider
        float pos = sliderPos + height /5;
        g.drawImageTransformed(Sliders, AffineTransform::verticalFlip(pos));
    }
    
private:
    //Image del knob.
    Image knobSwitch;
    Image knobMaster;
    Image Sliders;
    Image Buttons;
};

class ToggleSwitch : public Button
{
public:
    
    ToggleSwitch (const String& name = String())
        : Button (name)
    {
        img = ImageCache::getFromMemory (BinaryData::toggle_switch_png, BinaryData::toggle_switch_pngSize);
    }

    void clicked() override
    {
        setToggleState(! getToggleState(), dontSendNotification);
    }

    void paintButton (Graphics& g, bool isMouseOverButton, bool isButtonDown) override
    {
        
        const int srcY = getToggleState() ? 0 : img.getHeight() / 2;
        g.drawImage (img, 0, 0, getWidth(), getHeight(),
                     0, srcY, img.getWidth(), img.getHeight() / 2);
    }
    

private:
    Image img;
};

class MetsReverbAudioProcessorEditor  : public AudioProcessorEditor,
                                        public Slider::Listener,
                                        public Button::Listener

{
public:
    MetsReverbAudioProcessorEditor (MetsReverbAudioProcessor&);
    ~MetsReverbAudioProcessorEditor();

    //==============================================================================
     void paint (Graphics&) override;
        void resized() override;
        void buttonClicked (Button* button) override;
        void buttonStateChanged (Button* button) override;
        void updateToggleState (Button* button);
        void sliderValueChanged (Slider *Slider) override;
        
        
        double freezeOn = 1.0f;
        double freezeOff = 0.0f;
           
    private:

        Slider wetSlider;
        Label wetLabel;
        Slider drySlider;
        Label dryLabel;
        Slider dampSlider;
        Label dampLabel;
        Slider roomSlider;
        Label roomLabel;
        Slider widthSlider;
        Label widthLabel;
        MetsReverbAudioProcessor& processor;
        Image backgroundImage;
        std::unique_ptr<HyperlinkButton> hyperlinkButton;
        Image Sliders;
        SliderLookAndFeel sliderLookAndFeel;
        float sliderValue;
        Image knobMaster;
        Image knobSwitch;
        Slider freezeSlider;
        ToggleSwitch freezeSwitchOn;
        ToggleSwitch freezeSwitchOff;
    
        ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> wetSliderVal;

    public:
        std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> dampAttach;
        std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> widthAttach;
        std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> roomAttach;
        std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> dryAttach;
        std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> wetAttach;
        std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> freezeAttach;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MetsReverbAudioProcessorEditor)
};
