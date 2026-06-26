// GUARD HEADER STATEMENT
#ifndef SynthPresetSelectionScreen_H
#define SynthPresetSelectionScreen_H

#include <M5Unified.h>
// #include "AmyPresetList.h"

class SynthPresetSelectionScreen {
  private:	
    // Global Vars for standardized user interface sizing
    int baseLocX = 20;
    int baseLocY = 120;
    int horizontalSpacing = 20;
    int verticalSpacing = 40;
    int tableCellWidth = 400;
    int tableCellHeight = 40;
    int cornerRadius = 10;

    int selectedPresetValue = 47;
    int selectedPresetIndex = 12;

    // Button Min Max Coordinates Array to determining if touch events 
    // are within boundries of buttons {minX,maxX,minY,maxY}
    struct cellAttributes {
        int cellNumber;
        int minX;
        int maxX;
        int minY;
        int maxY;
        bool cellState;
    };
    cellAttributes tableCellAttributesArray[24];

		int screenWidth; // SCREEN Width:1280
		int screenHeight;  // SCREEN Height:720
		int dispY;
		int dispX;

    // Set up for loop execution step timing
    // static long last_millis2 = 0;
    // static const long millis_interval2 = 250;
    long last_millis2 = 0;
    long millis_interval2 = 10;

    // Controls the execution mode between default of playing
    // the keys versus selection of the synth preset values 
    int keyboardMode = 0;
    int presetSelectionMode = 1;
    int appExecutionMode =  presetSelectionMode;
    
    // Amy PreSet List
    struct instrumentStruct {
      int preSetNum;
      String preSetName;
    };
    
    instrumentStruct preSetArray[24] = {
      {7,"Juno A18 Piano I"},         //  0
      {213,"DX7 GLOKENSL"},           //  1
      {14,"Juno A27 Elect. Piano I"}, //  2
      {17,"Juno A32 Steel Drums"},    //  3
      {58,"Juno A83 Drum Booms"},     //  4
      {231,"DX7 SYN-PIANO"},          //  5
      {26,"Juno A43 Brass Ensemble"}, //  6
      {27,"Juno A44 Guitar"},         //  7
      {29,"Juno A46 Dark Pluck"},     //  8
      {31,"Juno A48 Synth Bass I"},   //  9
      {34,"Juno A53 Lead III"},       // 10
      {36,"Juno A55 Synth Bass II"},  // 11
      {47,"* Juno A68 Synth Pad"},    // 12
      {186,"DX7 LUTE"},               // 13
      {223,"DX7 LOG DRUM"},           // 14
      {69,"Juno B16 Recorder"},       // 15
      {119,"Juno B78 Brassy Organ"},  // 16
      {120,"* Juno B81 Dark Strings"},// 17
      {167,"DX7 Toy Piano"},          // 18
      {185,"DX7 Guitar"},             // 19
      {193,"DX7 Flute"},              // 20
      {203,"DX7 Bass"},               // 21
      {43,"Juno A64 Snare Drum"},     // 22
      {215,"DX7 XYLOPHONE"}           // 23
    };
    

    bool tempTableCellBoolArray[24] = {false,false,false,false,false,false,false,false,false,false,false,false,
      false,false,false,false,false,false,false,false,false,false,false,false};


  public:
    SynthPresetSelectionScreen(); // Actual Constructor

    void normalizeXYvalues(int &dispX, int &dispY, int touchX, int touchY);
    void drawSynthPresetSelectionScreen(int tmpSelectedPresetIndex);
    void drawSynthPresetChooserCell(int cellCount, bool highlightOn);
    void synthPresetSelectionRespondToTouches(int nums, m5::touch_point_t touchPoint[5]);
    void synthPresetSelectionRespondToNoTouches();
    void synthPresetSelectionCheckForStateChange();
    int getSelectedPresetValue();
    int getSelectedPresetIndex();
    String getSelectedPresetName();
    int getAppExecutionMode();

};  // End of Class Definition

#endif // End of Guard Statement