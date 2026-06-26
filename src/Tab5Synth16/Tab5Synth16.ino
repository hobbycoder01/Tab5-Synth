#include <M5Unified.h>
#include "TopLineButtonClass.h"
#include "KeyboardClass.h"
#include <AMY-Arduino.h>
#include "SoundUtils.h"
#include "SynthPresetSelectionScreen.h"
#include "Tab5SynthOpenScreen02.h"

int screenWidth; // SCREEN Width:1280
int screenHeight; // SCREEN Height:720
m5::touch_point_t touchPoint[5];

int tmpSelectedPresetValue = 47;
int tmpSelectedPresetIndex = 12;

// Instantiate TopLineButtonClass
TopLineButtonClass topLineButtonClass;

// Instantiate Keyboard Class
KeyboardClass keyboardClass;

// Instantiate SynthPresetSelectionScreen
SynthPresetSelectionScreen synthPresetSelectionScreen;

// Instantiate tab5SynthOpenScreen02
Tab5SynthOpenScreen02 tab5SynthOpenScreen02;


void initScreen() {
  M5.Display.setRotation(3);
  M5.Display.fillScreen(TFT_BLACK);
  // M5.Display.setBrightness(10);
  M5.Display.setBrightness(150);
  int screenWidth = M5.Lcd.width();
  int screenHeight = M5.Lcd.height();
  // Serial.printf("\nScreen Width:%d  Height:$d \n",screenWidth,screenHeight);

  M5.Display.setTextColor(TFT_GREENYELLOW,TFT_BLACK);
  M5.Display.setTextSize(2);
  // Location for all the included fonts:
  // .../Arduino/libraries/M5GFX/src/lgfx/v1/lgfx_fonts.hpp
  M5.Lcd.setFreeFont(&FreeSansBoldOblique24pt7b); // Sets the font to Free Mono 12pt
  M5.Display.drawString("Tab 5 Synth",10,10);

  topLineButtonClass.drawTopLineControls();
  topLineButtonClass.refreshVolumeIndicatorBar(topLineButtonClass.speakerVolume/250);
  
  keyboardClass.drawKeyboard();
  // keyboardClass.printButtonCoordinatesArray();

  String tmpSelectedPresetName = synthPresetSelectionScreen.getSelectedPresetName();
  M5.Lcd.setFreeFont(&FreeSansBoldOblique12pt7b); // Sets the font to Free Mono 12pt
  M5.Display.setTextColor(TFT_GREENYELLOW,TFT_BLACK);
  M5.Display.drawString("Selected Preset:",15,100);
  M5.Display.setTextColor(TFT_WHITE,TFT_BLACK);
  M5.Display.drawString(tmpSelectedPresetName,400,100);
}


void setup() {
  // put your setup code here, to run once:
  M5.begin();
  Serial.begin();
  M5.Speaker.begin();
  // M5.Speaker.setVolume(100);


  // Initialize the speaker volume   
  int tmpSpeakerVolume = topLineButtonClass.getSpeakerVolume();
  M5.Speaker.setVolume(tmpSpeakerVolume);
  // Serial.printf("in LOOP - calling topLineButtonClass.getSpeakerVolume = %d \n",tmpSpeakerVolume);
  // Serial.println("    now calling keyboardClass.setSynthVelocityValue(tmpSpeakerVolume)");
  keyboardClass.setSynthVelocityValue(tmpSpeakerVolume);


  // If headphone is plugged in turn off speaker
  checkForHeadphoneAndReact();

  // Display opening screen
  tab5SynthOpenScreen02.main();

  initScreen();

  myBeepFuntion(); // Initialize Sound Subsystem

  amyConfigStartup();
  configureSynthEngine(47);
  playSomeNotes(); 
  }


// Set up for loop execution step timing
static long last_millis = 0;
static const long millis_interval = 10;

// Set up for second loop execution step timing
static long last_millis2 = 0;
static const long millis_interval2 = 10;

// Controls the execution mode between default of playing
// the keys versus selection of the synth preset values 
int keyboardMode = 0;
int presetSelectionMode = 1;
int appExecutionMode =  keyboardMode;

void loop() {
  M5.update();
  int nums = M5.Lcd.getTouchRaw(touchPoint, 5);  
  int dispX = 0;
  int dispY = 0;

  // Give Amy chance to do its processing
  amy_update();

  // If headphone is plugged in turn off speaker
  checkForHeadphoneAndReact();

  // Check to see if the Top Line Button Class is calling for Synth Preset Selection 
  if(topLineButtonClass.getExecutionModeValue() == presetSelectionMode){
    if(appExecutionMode == keyboardMode){
      appExecutionMode = presetSelectionMode;
      tmpSelectedPresetIndex = synthPresetSelectionScreen.getSelectedPresetIndex();
      synthPresetSelectionScreen.drawSynthPresetSelectionScreen(tmpSelectedPresetIndex);
    }
  }
  
  // Check to see if the Synth Preset Selection Class is calling for Keyboard Mode 
  if(synthPresetSelectionScreen.getAppExecutionMode() == keyboardMode){
    if(appExecutionMode == presetSelectionMode){
      topLineButtonClass.resetExecutionModeValue(); // to keyboard mode
      appExecutionMode = keyboardMode; // Local appExecutionMode variable changed to keyboard mode

      M5.Display.clearDisplay();
      M5.Lcd.setFreeFont(&FreeSansBoldOblique24pt7b); // Sets the font to Free Mono 12pt
      M5.Display.setTextColor(TFT_GREENYELLOW,TFT_BLACK);
      M5.Display.drawString("Tab 5 Synth",10,10);

      topLineButtonClass.drawTopLineControls();

      tmpSelectedPresetValue = synthPresetSelectionScreen.getSelectedPresetValue();
      configureSynthEngine(tmpSelectedPresetValue);
      keyboardClass.resetBaseKeyLocXandY();
      keyboardClass.drawKeyboard(); // Redraw the keyboard on the screen

      // Replace the Selected Preset label on the main keyboard screen
      String tmpSelectedPresetName = synthPresetSelectionScreen.getSelectedPresetName();
      M5.Lcd.setFreeFont(&FreeSansBoldOblique12pt7b); // Sets the font to Free Mono 12pt
      M5.Display.setTextColor(TFT_GREENYELLOW,TFT_BLACK);
      M5.Display.drawString("Selected Preset:",15,100);
      M5.Display.setTextColor(TFT_WHITE,TFT_BLACK);
      M5.Display.drawString(tmpSelectedPresetName,400,100);
    }
  }

  // If nums is > 0 then we received some touch points to process...
  if(nums){ 
    // This if statement allows us to skip some of the overall loop steps
    // to act as a kind of debounce function
    int now_millis = millis();
    if ((now_millis - last_millis) > millis_interval) {
      last_millis = now_millis;
      
      topLineButtonClass.topLineButtonResponseToTouches(nums, touchPoint);

      // Decide which set of controls are currently on the screen and send
      // to appropriate touch detection routines
      if(appExecutionMode == keyboardMode){
        int tmpNotesChordsMode = topLineButtonClass.getNotesChordsMode();
        keyboardClass.keyboardResponseToTouches(nums,touchPoint,tmpNotesChordsMode);
      }
      else if(appExecutionMode == presetSelectionMode){
        synthPresetSelectionScreen.synthPresetSelectionRespondToTouches(nums,touchPoint);
      }
    }   
  }
  
  // If nums == 0 we have no touchPoints then all buttons must be off
  // Reset tempButtonBoolArray to all false so it is picked up
  // and processed in the next code block 
  else {  
    topLineButtonClass.topLineButtonResponseToNoTouches();

    // Decide which set of controls are currently on the screen and send
    // to appropriate no touch  routines
    if(appExecutionMode == keyboardMode){
      keyboardClass.keyboardResponseToNoTouches();
    }
    else if(appExecutionMode == presetSelectionMode){
      synthPresetSelectionScreen.synthPresetSelectionRespondToNoTouches();
    }
  }

  // We now know the current button state based on the touches we processed 
  // above, so roll though the buttonBoolArray checking against the 
  // tempButtonBoolArray and process any state changes to buttons
  if(appExecutionMode == keyboardMode){
    topLineButtonClass.topLineButtonCheckForStateChange();
  }

  // Decide which set of controls are currently on the screen and send
  // to appropriate no touch  routines
  if(appExecutionMode == keyboardMode){
    keyboardClass.KeyboardCheckForStateChange();
  }
  else if(appExecutionMode == presetSelectionMode){
    synthPresetSelectionScreen.synthPresetSelectionCheckForStateChange();
  }

  // This if statement allows us to skip some of the overall loop steps
  // to act as a kind of debounce function
  int now_millis2 = millis();
  if ((now_millis2 - last_millis2) > millis_interval2) {
    last_millis2 = now_millis2;
    int tmpSpeakerVolume = topLineButtonClass.getSpeakerVolume();
    // Serial.printf("in LOOP - calling topLineButtonClass.getSpeakerVolume = %d \n",tmpSpeakerVolume);
    // Serial.println("    now calling keyboardClass.setSynthVelocityValue(tmpSpeakerVolume)");
    keyboardClass.setSynthVelocityValue(tmpSpeakerVolume);
  }

}
