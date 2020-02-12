/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MetsReverbAudioProcessorEditor::MetsReverbAudioProcessorEditor (MetsReverbAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    backgroundImage = ImageCache::getFromMemory(BinaryData::Sfondo_4_png, BinaryData::Sfondo_4_pngSize);
    
    addAndMakeVisible(wetSlider);
    wetSlider.setRange(0.0f, 0.6f);
    wetSlider.setValue(0.0f);
    wetSlider.addListener (this);
    wetSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    wetSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, true, 0, 0);
    wetSlider.setLookAndFeel(&sliderLookAndFeel);
    wetLabel.setText("Wet", dontSendNotification);
    wetLabel.attachToComponent(&wetSlider, false);
    wetLabel.setColour(Label::textColourId, Colours::white);
    wetLabel.setJustificationType(Justification::left);
    

    
    addAndMakeVisible(drySlider);
    drySlider.setRange(0.0f, 0.6f);
    drySlider.setValue(0.0f);
    drySlider.addListener(this);
    drySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    drySlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, true, 0, 0);
    drySlider.setLookAndFeel(&sliderLookAndFeel);
    dryLabel.setText("Dry", dontSendNotification);
    dryLabel.attachToComponent(&drySlider, false);
    dryLabel.setColour(Label::textColourId, Colours::white);
    dryLabel.setJustificationType(Justification::left);
    
    
    addAndMakeVisible(dampSlider);
    dampSlider.setRange(0.0f, 1.0f);
    dampSlider.setValue(0.1f);
    dampSlider.addListener(this);
    dampSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    dampSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 60, 20);
    dampSlider.setTextBoxIsEditable(false);
    dampSlider.setLookAndFeel(&sliderLookAndFeel);
    dampLabel.setText("Damp", dontSendNotification);
    dampLabel.attachToComponent(&dampSlider, false);
    dampLabel.setColour(Label::textColourId, Colours::white);
    dampLabel.setJustificationType(Justification::top);

    //per impostare un colore particolare ad uno slider devo creare l'oggetto nell'handler
    //otherLookAndFeel.setColour(Slider::thumbColourId, Colours::green);
    //dampSlider.setLookAndFeel(&otherLookAndFeel);
    
    addAndMakeVisible(roomSlider);
    roomSlider.setRange(0.0f, 1.0f, 0.01f);
    roomSlider.setValue(0.1f);
    roomSlider.addListener(this);
    roomSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    roomSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 60, 20);
    roomSlider.setTextBoxIsEditable(true);
    roomSlider.setLookAndFeel(&sliderLookAndFeel);
    roomLabel.setText("Room Size", dontSendNotification);
    roomLabel.attachToComponent(&roomSlider, false);
    roomLabel.setColour(Label::textColourId, Colours::white);
    roomLabel.setJustificationType(Justification::top);
    
    addAndMakeVisible(widthSlider);
    widthSlider.setRange(0.0f, 1.0f);
    widthSlider.setValue(0.1f);
    widthSlider.addListener(this);
    widthSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    widthSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 60, 20);
    widthSlider.setLookAndFeel(&sliderLookAndFeel);
    widthLabel.setText("Width", dontSendNotification);
    widthLabel.attachToComponent(&widthSlider, false);
    widthLabel.setColour(Label::textColourId, Colours::white);
    widthLabel.setJustificationType(Justification::top);
    
    
    addAndMakeVisible(freezeSlider);
    freezeSlider.addListener(this);
    freezeSlider.setValue(0.0f);
    freezeSlider.setRange(0.0f, 1.0f, 1.0f);
    freezeSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalDrag);
    freezeSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 60, 20);
    freezeSlider.setLookAndFeel(&sliderLookAndFeel);
    
    
    addAndMakeVisible(freezeSwitchOn);
    freezeSwitchOn.addListener(this);
    freezeSwitchOn.setName("FreezeOn");
    freezeSwitchOn.setState(ToggleSwitch::buttonOver);
    
    //addAndMakeVisible(freezeSwitchOff);
    freezeSwitchOff.addListener(this);
    freezeSwitchOff.setName("FreezeOff");
    freezeSwitchOff.setState(ToggleSwitch::buttonDown);
    
    hyperlinkButton.reset (new HyperlinkButton (String(),
                                                URL ("https://metscuneo.it")));
    addAndMakeVisible (hyperlinkButton.get());
    hyperlinkButton->setTooltip (TRANS("www.metscuneo.it"));
    hyperlinkButton->setButtonText (String());

    hyperlinkButton->setBounds (150, 10, 300, 50);
    setSize(600, 300);

    
    dampAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, DAMP_ID, dampSlider);
    widthAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, WIDTH_ID, widthSlider);
    roomAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, ROOM_ID, roomSlider);
    dryAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, DRY_ID, drySlider);
    wetAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, WET_ID, wetSlider);
    freezeAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, FREEZE_ID, freezeSlider);
    

}

MetsReverbAudioProcessorEditor::~MetsReverbAudioProcessorEditor()
{
}

//==============================================================================
void MetsReverbAudioProcessorEditor::paint (Graphics& g)
{
    g.drawImage(backgroundImage, 0, 0, 600, 300, 0, 0, 2043, 1169);
}

void MetsReverbAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if (slider == &wetSlider)
    {
        processor.wetLevel = wetSlider.getValue();
        //drySlider.setValue(0.04f / wetSlider.getValue(), dontSendNotification);
    }
    if (slider == &drySlider)
    {
        processor.dryLevel = drySlider.getValue();
        //wetSlider.setValue(0.04f / drySlider.getValue(), dontSendNotification);
    }
    if (slider == &dampSlider)
    {
        processor.damping = dampSlider.getValue();
    }
    if (slider == &roomSlider)
    {
        processor.roomSize = roomSlider.getValue();
    }
    if (slider == &widthSlider)
    {
        processor.width = widthSlider.getValue();
    }
    if (slider == &freezeSlider)
    {
        processor.freezeMode = freezeSlider.getValue();
    }
}

void MetsReverbAudioProcessorEditor::buttonClicked(Button *button)
{
    
    if (button == &freezeSwitchOn)
    {
        processor.freezeMode = freezeOn;
    }
    if (button == &freezeSwitchOff)
    {
        processor.freezeMode = freezeOff;
    }
    
    if (button == &freezeSwitchOn)
    {
        freezeSlider.setValue(freezeOn, dontSendNotification);
    }
    else if (button == &freezeSwitchOff)
    {
        freezeSlider.setValue(freezeOff, dontSendNotification);
    }
    
    if (button == &freezeSwitchOn)
    {
        freezeSwitchOn.setVisible(false);
        addAndMakeVisible(freezeSwitchOff);
        freezeSwitchOff.setVisible(true);
        freezeSwitchOff.setState(ToggleSwitch::buttonDown);
        freezeSwitchOff.clicked();
        //freezeSwitchOff.setTransform(AffineTransform::rotation(180));
    }
    
    if (button == &freezeSwitchOff)
    {
        freezeSwitchOff.setVisible(false);
        addAndMakeVisible(freezeSwitchOn);
        freezeSwitchOn.setVisible(true);
        freezeSwitchOn.setState(ToggleSwitch::buttonOver);
        freezeSwitchOn.clicked();
    }
 /*
    if (float freezeSlider = 1.0f) {
        addAndMakeVisible(freezeSwitchOff);
        freezeSwitchOff.setVisible(true);
        freezeSwitchOn.setVisible(false);
    } //else freezeSwitchOff.setVisible(false);
      
    if (float freezeSlider = 0.0f) {
        addAndMakeVisible(freezeSwitchOn);
        freezeSwitchOn.setVisible(true);
        freezeSwitchOff.setVisible(false);
    } //else freezeSwitchOn.setVisible(false);

    if (! freezeSwitchOn.isVisible())
        processor.freezeMode = freezeOn;
        freezeSwitchOff.setVisible(true);
        freezeSwitchOn.setVisible(false);
    
    if (! freezeSwitchOff.isVisible())
        processor.freezeMode = freezeOff;
        freezeSwitchOn.setVisible(true);
    freezeSwitchOff.setVisible(false);
    
    {
    if (float freezeSlider = 0.0f)
        freezeSlider = 1.0f;
    else if (float freezeSlider = 1.0f)
        freezeSlider = 0.0f;
    }
    
    {
    if (float freezeSlider = 0.0f)
        processor.freezeMode = 1.0f;
    }*/
}

void MetsReverbAudioProcessorEditor::updateToggleState(Button *button)
{
    auto state = freezeSwitchOn.getToggleStateValue();
}

void MetsReverbAudioProcessorEditor::buttonStateChanged(Button *button)
{
    
}

void MetsReverbAudioProcessorEditor::resized()
{
    wetSlider.setBounds(520, 80, 100, 170);
    wetLabel.setBounds(518, 60, 50, 20);
    drySlider.setBounds(52, 80, 100, 170);
    dryLabel.setBounds(50, 60, 50, 20);
    roomSlider.setBounds(170, 130, 60, 85);
    roomLabel.setBounds(162, 110, 80, 20);
    widthSlider.setBounds(270, 130, 60, 85);
    widthLabel.setBounds(276, 110, 60, 20);
    dampSlider.setBounds(370, 130, 60, 85);
    dampLabel.setBounds(375, 110, 60, 20);
    freezeSwitchOff.setBounds(270, 230, 60, 60);
    freezeSwitchOn.setBounds(270, 230, 60, 60);
    
    //non utilizzati perchè invisibili
    freezeSlider.setBounds(270, 230, 0, 0);
}
