// GUARD HEADER STATEMENT
#ifndef KeyboardClass_H
#define KeyboardClass_H

#include <M5Unified.h>
#include "GpioExpanderUtility.h"
#include "SoundUtils.h"

class KeyboardClass{
  private:

  int screenWidth; // SCREEN Width:1280
  int screenHeight; // SCREEN Height:720

  // Button Boolean Array
  bool buttonBoolArray[25] = {
    false,false,false,false,false,false,false,false,false,false,false,false,false,
    false,false,false,false,false,false,false,false,false,false,false,false};

  // This keeps track of the state of the notes vs chords mode
  // 0 = notes
  // 1 = should never be this state - it is the "chords" label
  // 2 = Major Chords Mode
  // 3 = Minor Chords Mode
  int notesChordsMode = 3;

  // Button Min Max Coordinates Array to determining if touch events 
  // are within boundries of buttons {minX,maxX,minY,maxY}
  struct buttonCoordinates {
      int minX;
      int maxX;
      int minY;
      int maxY;
  };

  buttonCoordinates buttonCoordinatesArray[25];

  // Key placement parameters
  int baseKeyLocX = 0;
  int baseKeyLocY = 545;
  int keyWidth = 80;
  int keyHeight = 150;
  int keyOutlineOffset = 6;
  int keyToKeyOffset = 5;
  int threeDeffectOffset = 6;
  int cornerRadius = 10;
  int whiteKeyOutlineColor = TFT_GREENYELLOW;
  int whiteKeyBodyColor = TFT_BLACK;
  int blackKeyColor = TFT_BLACK;
  
  char* keyStrings[25] = {
    "C","D","E","F","G","A","B",
    "C","D","E","F","G","A","B","C",
    "Db","Eb","Gb","Ab","Bb",
    "Db","Eb","Gb","Ab","Bb"
    };  

  int dispX = 0;
  int dispY = 0;

  float synthVelocity = 0;

  float keyLabelOffsetX = .15;
  float keyLabelOffsetY = .20;


  public:

  void initScreen();
  void processKeyPress(int keyNumber, int onOff);
  void resetBaseKeyLocXandY();
  void drawKeyboard();
  void normalizeXYvalues(int &dispX, int &dispY, int touchX, int touchY);
  void setSynthVelocityValue(int speakerVolume);
  void printButtonCoordinatesArray();

  // Set up for loop execution step timing
  long last_millis = 0;
  long millis_interval = 1;

  bool tempButtonBoolArray[25] = {
    false,false,false,false,false,false,false,
    false,false,false,false,false,
    false,false,false,false,false,false,false,false,
    false,false,false,false,false};

  /*  
  MIDI NOTES
  Num Note-Name
  60  C4 (Middle C)
  61  C#4/Db4
  62  D4
  63  D#4/Eb4
  64  E4
  65  F4
  66  F#4/Gb4
  67  G4
  68  G#4/Ab4
  69  A4
  70  A#4/Bb4
  71  B4
  72  C5
  73  C#5/Db5
  74  D5
  75  D#5/Eb5
  76  E5
  77  F5
  78  F#5/Gb5
  79  G5
  80  G#5/Ab5
  81  A5
  82  A#5/Bb5
  83  B5
  84  C6
  85  C#6/Db6
  86  D6
  87  D#6/Eb6
  88  E6
  89  F6
  90  F#6/Gb6
  91  G6
  92  G#6/Ab6
  93  A6
  94  A#6/Bb6
  95  B6
  */

  // midiNoteNumberArray is organized this way because the keyboard is 
  // drawn to the screen first with the row of 'regular notes' and then 
  // with the sharp/flat notes on the row above
  int midiNoteNumberArray[25] = {
    60,62,64,65,67,69,71,72,74,76,77,79,81,83,84, // Regular Notes
    61,63,66,68,70,73,75,78,80,82 // Sharp/Flat Notes
    };

  struct midiChordArrayAttributes {
      int note1;
      int note2;
      int note3;
  };

  // midiMajorChordNoteNumberArray is organized this way because the keyboard 
  // is drawn to the screen first with the row of 'regular notes' and then with 
  // the sharp/flat notes on the row above
  midiChordArrayAttributes midiMajorChordNoteNumberArray[25] = {
    // REGULAR NOTES
    // Base Note Octive 4
    {60,64,67}, // C-E-G
    {62,66,69}, // D-Gb-A
    {64,68,71}, // E-Ab-B
    {65,69,72}, // F-A-C
    {67,71,74}, // G-B-D
    {69,73,76}, // A-Db-E
    {71,75,78}, // B-Eb-Gb
    // Base Note Octive 5
    {72,76,79}, // C-E-G
    {74,78,81}, // D-Gb-A
    {76,80,83}, // E-Ab-B
    {77,81,84}, // F-A-C
    {79,83,86}, // G-B-D
    {81,85,88}, // A-Db-E
    {83,87,90}, // B-Eb-Gb
    // Base Note Octive 6
    {84,88,91}, // C-E-G
    // SHARP/FLAT NOTES
    // Base Note Octive 4
    {61,65,68}, // Db-F-Ab
    {63,67,71}, // Eb-G-Bb
    {66,70,73}, // Gb-Bb-Db
    {68,72,75}, // Ab-C-Eb
    {70,74,77}, // Bb-D-F
    // Base Note Octive 5
    {73,77,80}, // Db-F-Ab
    {75,79,82}, // Eb-G-Bb
    {78,82,85}, // Gb-Bb-Db
    {80,84,87}, // Ab-C-Eb
    {82,86,89}  // Bb-D-F
  };

  // midiMinorChordNoteNumberArray is organized this way because the keyboard
  // is drawn to the screen first with the row of 'regular notes' and then with 
  // the sharp/flat notes on the row above
  midiChordArrayAttributes midiMinorChordNoteNumberArray[25] = {
    // REGULAR NOTES
    // Base Note Octive 4
    {60,63,67}, // C-Eb-G
    {62,65,69}, // D-F-A
    {64,67,71}, // E-G-B
    {65,68,72}, // F-Ab-C
    {67,70,75}, // G-Bb-Eb
    {69,72,76}, // A-C-E
    {71,74,78}, // B-D-Gb
    // Base Note Ocvite 5
    {72,75,79}, // C-Eb-G
    {74,77,81}, // D-F-A
    {76,79,83}, // E-G-B
    {77,80,84}, // F-Ab-C
    {79,82,86}, // G-Bb-D
    {81,84,88}, // A-C-E
    {83,86,90}, // B-D-Gb
    // Base Note Octive 6
    {84,87,91}, // C-Eb-G
    // SHARP/FLAT NOTES
    // Base Note Octive 4
    {61,64,68}, // Db-E-Ab
    {63,66,70}, // Eb-Gb-Bb
    {66,69,73}, // Gb-A-Db
    {68,72,76}, // Ab-Cb-Eb
    {70,73,77}, // Bb-Db-F
    // Base Note Octive 5
    {73,76,80}, // Db-E-Ab
    {75,78,82}, // Eb-Gb-Bb
    {78,81,85}, // Gb-A-Db
    {80,83,87}, // Ab-B-Eb
    {82,85,89}  // Bb-Db-F
  };
  
  void keyboardResponseToTouches(int nums,m5::touch_point_t touchPoint[5],int tmpNotesChordsMode);
  void keyboardResponseToNoTouches();
  void KeyboardCheckForStateChange();

}; // End Class

#endif // Guard Statement
