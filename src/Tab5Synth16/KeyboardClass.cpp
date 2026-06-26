#include "KeyboardClass.h"
#include <M5Unified.h>
#include <AMY-Arduino.h>
#include "GpioExpanderUtility.h"
#include "SoundUtils.h"


void KeyboardClass::processKeyPress(int keyNumber, int onOff){
  int tmpMinX = buttonCoordinatesArray[keyNumber].minX;
  int tmpMaxX = buttonCoordinatesArray[keyNumber].maxX;
  int tmpMinY = buttonCoordinatesArray[keyNumber].minY;
  int tmpMaxY = buttonCoordinatesArray[keyNumber].maxY;
  int tmpHeight = tmpMaxX - tmpMinX; 
  int tmpWidth = tmpMaxY - tmpMinY;
  float tmpKeyLabelOffsetX = keyLabelOffsetX;
  float tmpKeyLabelOffsetY = keyLabelOffsetY;


  // Key outline
  M5.Display.fillRoundRect(
    tmpMinX,
    tmpMinY,
    keyWidth,
    keyHeight,
    cornerRadius,
    whiteKeyOutlineColor);

  if(onOff == 0){
    M5.Display.fillRoundRect(
      tmpMinX + keyOutlineOffset,
      tmpMinY + keyOutlineOffset - threeDeffectOffset + 3,
      keyWidth - (2 * keyOutlineOffset) - threeDeffectOffset,
      keyHeight - (2 * keyOutlineOffset) - threeDeffectOffset,
      cornerRadius,
      whiteKeyBodyColor
    );

    // Put text labels on keys
    M5.Display.setTextColor(WHITE,TFT_WHITE);
    M5.Display.setTextFont(&FreeSansBoldOblique12pt7b);

    // This block of code handles centering the key labels 
    if(keyNumber > 14){ // "Black" Keys
       tmpKeyLabelOffsetX = keyLabelOffsetX * .09; // we need a bit less of X offset because of 2 character key labels
    }    

    M5.Display.drawString(
      keyStrings[keyNumber],
      tmpMinX + (tmpKeyLabelOffsetX * keyWidth),
      tmpMinY + (tmpKeyLabelOffsetY * keyHeight)
    );
  }
}


void KeyboardClass::resetBaseKeyLocXandY(){
  baseKeyLocX = 0;
  baseKeyLocY = 545;
}


void KeyboardClass::drawKeyboard() {
  // Serial.println("\n\nAt the top of drawKeyboard!!!\n\n");
  int tmpKeyIndex = 0;
  float tmpKeyLabelOffsetX = keyLabelOffsetX;
  float tmpKeyLabelOffsetY = keyLabelOffsetY;

	// Clear screen area for keyboard SCREEN Width:1280, SCREEN Height:720
	M5.Display.fillRect(
		0,
		260,
		1280,
		720-260,
		TFT_BLACK);

  for(int keyCount = 0; keyCount < 25; keyCount++ ) {
    tmpKeyIndex = keyCount; // tmpKeyIndex is used to place keys on screen

    if(keyCount == 15){ // This logic sets up the "Black" keys to be placed above "white" keys
      baseKeyLocX = (keyWidth * .5);
      baseKeyLocY -= (keyHeight + keyToKeyOffset);
    }

    if(keyCount >= 15){ // the keyCount is used to index the array of key data
      tmpKeyIndex -= 15; // the tmpKeyIndex is used to index the position of the key on the screen
    }
  
    if(keyCount == 17){ // this pushes the 3rd, 4th and 5th "Black" keys into position between
      baseKeyLocX += (keyWidth + keyToKeyOffset); // the F and G "White" keys
    }
  
    if(keyCount == 20){ // this pushes the 6th and 7th "Black" keys into position between
      baseKeyLocX += (keyWidth + keyToKeyOffset); // the C and D "White" keys
    }
  
    if(keyCount == 22){ // this pushes the 8th, 9th and 10th "Black" keys into position between
      baseKeyLocX += (keyWidth + keyToKeyOffset); // the F and G "White" keys
    }

    // Key outline
    M5.Display.fillRoundRect(
      baseKeyLocX + (tmpKeyIndex * (keyWidth + keyToKeyOffset)),
      baseKeyLocY,
      keyWidth,
      keyHeight,
      cornerRadius,
      whiteKeyOutlineColor);
    // Capture min and max coordinates for keys
    buttonCoordinatesArray[keyCount].minX = baseKeyLocX + (tmpKeyIndex * (keyWidth + keyToKeyOffset));
    buttonCoordinatesArray[keyCount].maxX = baseKeyLocX + (tmpKeyIndex * (keyWidth + keyToKeyOffset)) + keyWidth;
    buttonCoordinatesArray[keyCount].minY = baseKeyLocY;
    buttonCoordinatesArray[keyCount].maxY = baseKeyLocY + keyHeight;

    // Fill in key to create border visual effect
    M5.Display.fillRoundRect(
      baseKeyLocX + keyOutlineOffset + (tmpKeyIndex * (keyWidth + keyToKeyOffset)) - threeDeffectOffset + 3,
      baseKeyLocY + keyOutlineOffset - threeDeffectOffset + 3,
      keyWidth - (2 * keyOutlineOffset) - threeDeffectOffset,
      keyHeight - (2 * keyOutlineOffset) - threeDeffectOffset,
      cornerRadius,
      whiteKeyBodyColor
      );
    
    // Put text labels on keys
    M5.Display.setTextColor(WHITE,TFT_WHITE);
    M5.Lcd.setFreeFont(&FreeSansBoldOblique12pt7b); // Sets the font to Free Mono 12pt

    // This block of code handles centering the key labels 
    if(keyCount > 14){ // "Black" Keys
       tmpKeyLabelOffsetX = keyLabelOffsetX * .09; // we need a bit less of X offset because of 2 character key labels
    }    

    M5.Display.drawString(
      keyStrings[keyCount],
      baseKeyLocX + (tmpKeyIndex * (keyWidth + keyToKeyOffset)) + (tmpKeyLabelOffsetX * keyWidth),
      baseKeyLocY + (tmpKeyLabelOffsetY * keyHeight)
      );
  }
}


// Need to normalize touch values to display values since
// the screen rotation does not handle this automatically
void KeyboardClass::normalizeXYvalues(int &dispX, int &dispY, int touchX, int touchY){
  int currentDisplayRotation = M5.Display.getRotation();
  switch (currentDisplayRotation) {
    case 0:
        // code to execute if variable == value1
        Serial.print("ERROR IN NORMALIZEXYVALUES FUNCTION!!!");
        break;
    case 1:
        // code to execute if variable == 1
        Serial.print("ERROR IN NORMALIZEXYVALUES FUNCTION!!!");
        break;
    case 2:
        // code to execute if variable == 2
        Serial.print("ERROR IN NORMALIZEXYVALUES FUNCTION!!!");
        break;
    case 3:
        // code to execute if variable == 3
        screenWidth = M5.Lcd.width();
        screenHeight = M5.Lcd.height();
        dispY = touchX;
        dispX = (screenWidth - touchY);
        break;
    default:
        // code to execute if no cases match
        Serial.print("ERROR IN NORMALIZEXYVALUES FUNCTION!!!");
        break;
  }
}


// Translates the raw volume setting (range 0 to 255) 
// to the synth velocity range (.5 to 5) in ten steps
// using .02 as the factor to interpolate the two values
// *************************************************
// Now want to limit the velocity range to be .5 to 2.5
// since velocity at 5 overwhelms the speaker
// now need to change translation factor to .01
void KeyboardClass::setSynthVelocityValue(int speakerVolume){
  // synthVelocity = (float)speakerVolume * .02;
  synthVelocity = (float)speakerVolume * .01;
  // Serial.printf("Call to KeyboardClass::setSynthVelocityValue - speakerVolume:%d \n",speakerVolume);
  // Serial.printf("synthVelocity:%d \n",synthVelocity);
}


// Print out the topLineButtonArray
void KeyboardClass::printButtonCoordinatesArray(){
  Serial.println("\nbuttonCoordinatesArray Contents");
	for (int keyCount = 0; keyCount < 13; keyCount++) {
    Serial.printf(
      "     BtnCoordArr: %s   %d   %d  %d  %d \n",
      keyStrings[keyCount],
      buttonCoordinatesArray[keyCount].minX,
      buttonCoordinatesArray[keyCount].maxX,
      buttonCoordinatesArray[keyCount].minY,
      buttonCoordinatesArray[keyCount].maxY
    );
  }
}


void KeyboardClass::keyboardResponseToTouches(int nums,m5::touch_point_t touchPoint[5],int tmpNotesChordsMode){
  notesChordsMode = tmpNotesChordsMode;
  // Reset tmpButtonBoolArray to all false 
  for(int tmpCntr = 0;tmpCntr<25;tmpCntr++){
    tempButtonBoolArray[tmpCntr] = false;
  }

  // Iterate through all the touches received
  for (int i = 0; i < nums; i++) {  
      int tmpX = touchPoint[i].x;
      int tmpY = touchPoint[i].y;
      dispX = 0;
      dispY = 0;
      
      // Need to normalize touch values to display values since
      // the screen rotation does not handle this automatically
      normalizeXYvalues(dispX, dispY, tmpX, tmpY);

    // We have one or more touch values so now iterate
    // through button array to see if any of those
    // touches are within bounds of x and y of any button 
    for(int keyCount = 0; keyCount < 25; keyCount++ ) {
      int tmpMinX = buttonCoordinatesArray[keyCount].minX;
      int tmpMaxX = buttonCoordinatesArray[keyCount].maxX;
      int tmpMinY = buttonCoordinatesArray[keyCount].minY;
      int tmpMaxY = buttonCoordinatesArray[keyCount].maxY;

      // Check to see if any of those touches are within bounds of one of our buttons 
      if ( (dispX > tmpMinX) && (dispX < tmpMaxX) && (dispY > tmpMinY) && (dispY < tmpMaxY) ){
          tempButtonBoolArray[keyCount] = true;
      }
    }
  }
}


void KeyboardClass::keyboardResponseToNoTouches(){
  // If we have no touchPoints then all buttons must be off
  // Reset tempButtonBoolArray to all false so it is picked up
  // and processed in the next code block 
  for(int tmpCntr = 0;tmpCntr<25;tmpCntr++){
    tempButtonBoolArray[tmpCntr] = false;
  }
}


void KeyboardClass::KeyboardCheckForStateChange(){
  // We now know the current button state based on the touches we processed 
  // above, so roll though the buttonBoolArray checking against the 
  // tempButtonBoolArray and process any state changes to buttons
  int onOff = 0;
  for(int keyCount = 0; keyCount < 25; keyCount++ ) {
    bool currentButtonState = buttonBoolArray[keyCount];
    bool newButtonState = tempButtonBoolArray[keyCount];
    if(currentButtonState != newButtonState){ // checking to see if old state equals new state
      if(newButtonState == true){ // Button has changed to true state
        buttonBoolArray[keyCount] = true;
        onOff = 1;
        processKeyPress(keyCount,onOff); // Make the display changes to reflect a button press

        switch (notesChordsMode) {
          case 3:
            // This keeps track of the state of the notes vs chords mode
            // 3 = notes mode
            noteOnOff(1,midiNoteNumberArray[keyCount],synthVelocity);
            break;
          case 5:
            // This keeps track of the state of the notes vs chords mode
            // 5 = Major Chords Mode
            noteOnOff(1,midiMajorChordNoteNumberArray[keyCount].note1,synthVelocity);
            noteOnOff(1,midiMajorChordNoteNumberArray[keyCount].note2,synthVelocity);
            noteOnOff(1,midiMajorChordNoteNumberArray[keyCount].note3,synthVelocity);
            break;
          case 6:
            // This keeps track of the state of the notes vs chords mode
            // 6 = Minor Chords Mode
            noteOnOff(1,midiMinorChordNoteNumberArray[keyCount].note1,synthVelocity);
            noteOnOff(1,midiMinorChordNoteNumberArray[keyCount].note2,synthVelocity);
            noteOnOff(1,midiMinorChordNoteNumberArray[keyCount].note3,synthVelocity);
            break;
        }
      }
      
      else { // Button has changed to false state
        buttonBoolArray[keyCount] = false;
        onOff = 0;
        processKeyPress(keyCount,onOff); // Make the display changes to reflect a button press

        switch (notesChordsMode) {
          case 3:
            // This keeps track of the state of the notes vs chords mode
            // 3 = notes mode
            noteOnOff(1,midiNoteNumberArray[keyCount],0);
            break;
          case 5:
            // This keeps track of the state of the notes vs chords mode
            // 5 = Major Chords Mode
            noteOnOff(1,midiMajorChordNoteNumberArray[keyCount].note1,0);
            noteOnOff(1,midiMajorChordNoteNumberArray[keyCount].note2,0);
            noteOnOff(1,midiMajorChordNoteNumberArray[keyCount].note3,0);
            break;
          case 6:
            // This keeps track of the state of the notes vs chords mode
            // 6 = Minor Chords Mode
            noteOnOff(1,midiMinorChordNoteNumberArray[keyCount].note1,0);
            noteOnOff(1,midiMinorChordNoteNumberArray[keyCount].note2,0);
            noteOnOff(1,midiMinorChordNoteNumberArray[keyCount].note3,0);
            break;
        }
      }

    }
  }
}

