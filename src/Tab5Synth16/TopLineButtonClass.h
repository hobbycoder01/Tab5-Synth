// GUARD HEADER STATEMENT
#ifndef TopLnBtnClass_H
#define TopLnBtnClass_H

#include <M5Unified.h>
#include "TopLineButtonClass.h"
// #include "IconResources01.h"

class TopLineButtonClass {
  private:	
    // Global Vars for standardized user interface sizing
    int iconHeight = 85;
    int iconWidth = 85;
    int iconHorizontalSpacing = 20;

    int screenWidth; // SCREEN Width:1280
    int screenHeight; // SCREEN Height:720

    // RGB565 is a 16-bit color encoding format that uses 5 bits for Red, 
    // 6 bits for Green, and 5 bits for Blue. It is widely used in embedded 
    // systems, microcontrollers, and low-power displays (e.g., e-ink or TFT 
    // screens) because it reduces memory usage and processing load compared 
    // to standard 24-bit color.   Web Site: https://rgbcolorpicker.com/565
    static constexpr uint16_t TFT_MY_GRAY = 0x39c7; // R = 7, G = 14, B = 7 within RGB565 color scheme

    // Button Min Max Coordinates Array to determining if touch events 
    // are within boundries of buttons {minX,maxX,minY,maxY}
    struct buttonAttributes {
        String buttonName;
        int minX;
        int maxX;
        int minY;
        int maxY;
        bool buttonState;
    };
        
    buttonAttributes topLineButtonArray[7] = {
      // Top Right Volume and Preset Select Buttons
      {"VOL_DOWN", 785, 870, 6, 91, 0},
      {"VOL_UP", 1070, 1155, 6, 91, 0},
      {"PRESET", 1175, 1260, 6, 91, 0},
      // 3rd Line down Notes vs Chords Controls
      {"NOTES", 20, 200, 185, 255, 0},
      {"CHORDS:", 225, 452, 185, 255, 0},
      {"MAJOR", 455, 645, 185, 255, 0},
      {"MINOR", 650, 825, 185, 255, 0}
    };

    int dispX = 0;
    int dispY = 0;

    void buttonNormalizeXYvalues(int &dispX, int &dispY, int touchX, int touchY);

    // Controls the execution mode between default of playing
    // the keys versus selection of the synth preset values 
    int keyboardMode = 0;
    int presetSelectionMode = 1;
    int appExecutionMode =  keyboardMode;

    // This keeps track of the state of the notes vs chords mode
    // 3 = notes mode
    // 4 = should never be this state - it is the "chords" label
    // 5 = Major Chords Mode
    // 6 = Minor Chords Mode
    int notesChordsMode = 3;

    // Set up for loop execution step timing
    // static long last_millis2 = 0;
    // static const long millis_interval2 = 250;
    long last_millis2 = 0;
    long millis_interval2 = 100;


	public:

    float speakerVolume = 150;

    TopLineButtonClass(); // Actual Constructor

    void drawTopLineControls();

   // REFRESH VOLUME INDICATOR BAR //
    void refreshVolumeIndicatorBar(float pctToMax);

    // DRAW VOLUME DOWN CONTROL //
    void drawVolumeDownControl(bool highlightOn);

    // DRAW VOLUME UP CONTROL //
    void drawVolumeUpControl(bool highlightOn);

    // Return the current value for speakerVolume
    int getSpeakerVolume();

    // DRAW SYNTH PRESET CHOOSER CONTROL
    void drawSynthPresetChooserControl(bool highlightOn);

    // Draw Notes/Chords Controls
    void drawNotesChordsChooserControls(int highlightNumber);

    // Print out the topLineButtonArray
    void printTopLineButtonArray();

    // Iterate through all the touches
    void topLineButtonResponseToTouches(int nums, m5::touch_point_t touchPoint[5]);
      
    // If we have no touchPoints then all buttons must be off
    // Reset tempButtonBoolArray to all false so it is picked up
    // and processed in the next code block   
    void topLineButtonResponseToNoTouches();

    // We now know the current button state based on the touches we processed 
    // above, so roll though the topLineButtonArray checking against the 
    // tempButtonBoolArray and process any state changes to buttons
    void topLineButtonCheckForStateChange();

    // Returns value for app execution when the Preset Selection button is pressed
    int getExecutionModeValue();

    // Resets value for app execution when the Preset Selection button is pressed
    void resetExecutionModeValue();

    // This keeps track of the state of the notes vs chords mode
    // 3 = notes mode
    // 4 = should never be this state - it is the "chords" label
    // 5 = Major Chords Mode
    // 6 = Minor Chords Mode    
    int getNotesChordsMode();

 };  // End of Class Definition
 
#endif // End of Guard Statement