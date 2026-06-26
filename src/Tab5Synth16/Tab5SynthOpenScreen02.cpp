#include <M5Unified.h>
#include "icons.h"
#include "Tab5SynthOpenScreen02.h"


// Constructor Definition
Tab5SynthOpenScreen02::Tab5SynthOpenScreen02(){
Serial.println("\n\nStarted Tab5SynthOpenScreen02 Constructor...\n\n");
}


void Tab5SynthOpenScreen02::initScreen() {
  M5.Display.setRotation(3);
  M5.Display.fillScreen(TFT_BLACK);
  M5.Display.setTextColor(TFT_GREENYELLOW,TFT_BLACK);
  M5.Display.setTextSize(2);

  // Location for all the included fonts:
  // .../Arduino/libraries/M5GFX/src/lgfx/v1/lgfx_fonts.hpp
  M5.Lcd.setFreeFont(&FreeSansBoldOblique24pt7b); // Sets the font to Free Mono 12pt
}


void Tab5SynthOpenScreen02::playChordWithTone(int chordNumber, int chordDuration) {
  // ######### playChordWithTone ########## //
  // The notes in a C chord are C, E, and G
  // The notes in a D chord are D, Gb, and A
  // The notes in a E chord are E, Ab, and B
  // The notes in a F chord are F, A, and C
  // The notes in a G chord are G, B, and D
  // The notes in a A chord are A, Db, and E
  // The notes in a B chord are B, Eb, and Gb
  float octive4CFreq = 261.626;
  float octive4DbFreq = 277.18;
  float octive4DFreq = 293.66;
  float octive4EbFreq = 311.13;
  float octive4EFreq = 329.63;
  float octive4FFreq = 349.23;
  float octive4GbFreq = 369.99;
  float octive4GFreq = 392.0;
  float octive4AbFreq = 415.3;
  float octive4AFreq = 440.0;
  float octive4BbFreq = 466.16;
  float octive4BFreq = 493.88;

  struct noteToneAttributes{
    String noteName;
    float noteFreq;
  };

  noteToneAttributes noteToneTable[12] = {
    {"C",261.626}, // 0
    {"Db",277.18}, // 1
    {"D",293.66},  // 2
    {"Eb",311.13}, // 3
    {"E",329.63},  // 4
    {"F",349.23},  // 5
    {"Gb",369.99}, // 6
    {"G",392.0},   // 7
    {"Ab",415.3},  // 8
    {"A",440.0},   // 9
    {"Bb",466.16}, // 10
    {"B",493.88}  // 11
  };

  struct chordTableLayout{
    String chordName;
    int chordTableIndex01;
    int chordTableIndex02;
    int chordTableIndex03;
  };

  chordTableLayout chordTable[7] = {
    {"C-Maj",0,4,7}, // 0
    {"D-Maj",11,3,6},// 1
    {"E-Maj",4,8,11},// 2
    {"F-Maj",5,9,0}, // 3
    {"G-Maj",7,11,2},// 4
    {"A-Maj",9,1,4}, // 5
    {"B-Maj",11,3,6} // 6
  };

  // tone, duration, channel, stop_current_sound
  M5.Speaker.tone(noteToneTable[chordTable[chordNumber].chordTableIndex01].noteFreq, chordDuration, 1, true);  
  M5.Speaker.tone(noteToneTable[chordTable[chordNumber].chordTableIndex02].noteFreq, chordDuration, 2, true);  
  M5.Speaker.tone(noteToneTable[chordTable[chordNumber].chordTableIndex03].noteFreq, chordDuration, 3, true);  
}


// DRAW NOTE ON SCREEN //
void Tab5SynthOpenScreen02::drawNoteOnScreen(bool blankOn, int xLoc, int yLoc){
  // Place icon on screen	
  if(blankOn){
    M5.Display.fillRect(
      xLoc,
      yLoc,
      80,
      80,
      TFT_BLACK);
  }
  else {
    M5.Display.drawPng(
      music_png,
      music_png_len,
      xLoc,
      yLoc,
      80,
      80,
      0,
      0,
      .45,
      .45);
  }
}


void Tab5SynthOpenScreen02::drawOpeningScreen(){
  struct chordsToPlayAttributes{
    int chordNum;
    int chordLength;
  };

  chordsToPlayAttributes chordsToPlay[9] = {
    {1,600},
    {2,600},
    {1,600},
    {5,300},
    {5,300},
    {1,600},
    {2,600},
    {1,600},
    {5,300}
  };

  // M5.Speaker.tone(1000, 100, 1, false); 
  for(int cntr1=0;cntr1<9;cntr1++){
    // Interleave chords while title screen builds
    // code to execute if variable doesn't match any case
    playChordWithTone(chordsToPlay[cntr1].chordNum,chordsToPlay[cntr1].chordLength);
    
    for(int cntr2=0;cntr2<7;cntr2++){
      drawNoteOnScreen(false, xValues[cntr1], cntr2*100);
      M5.delay(50);
      if(cntr2 !=3){
        drawNoteOnScreen(true, xValues[cntr1], cntr2*100);
      }
    }
  }
  M5.Display.drawString("Tab 5 Synth",378,300);
  M5.delay(250);
}


void Tab5SynthOpenScreen02::main() {
  initScreen();
  drawOpeningScreen();
  M5.delay(250);
}
