// GUARD HEADER STATEMENT
#ifndef Tab5SynthOpenScreen02_H
#define Tab5SynthOpenScreen02_H

#include <M5Unified.h>
#include "icons.h"

class Tab5SynthOpenScreen02 {
  private:	

    int screenWidth; // SCREEN Width:1280
    int screenHeight; // SCREEN Height:720

    int xValues[9] = {680, 920, 360, 520, 280, 600, 760, 840, 440 };

    void initScreen();

    void playChordWithTone(int chordNumber, int chordDuration);

    void drawNoteOnScreen(bool blankOn, int xLoc, int yLoc);

    void drawOpeningScreen();


  public:

    Tab5SynthOpenScreen02(); // the default constructor
    
    void main();



};  // End of Class Definition 
 
#endif // End of Guard Statement