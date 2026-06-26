#include <M5Unified.h>
#include "SynthPresetSelectionScreen.h"

// Constructor Definition
SynthPresetSelectionScreen::SynthPresetSelectionScreen(){
	Serial.println("\n\nStarted SynthPresetSelectionScreen Constructor...\n\n");
}


void SynthPresetSelectionScreen::drawSynthPresetSelectionScreen(int tmpSelectedPresetIndex){
  // Serial.println("\nAt top of drawSynthPresetSelectionScreen! \n");

	int tmpFillColor = TFT_GREENYELLOW;
  int cellCount = 0;
	appExecutionMode = presetSelectionMode;

	// Clear screen area for preset selection table SCREEN Width:1280, SCREEN Height:720
	M5.Display.fillRoundRect(
		0,
		110,
		1280,
		720,
		0,
		TFT_BLACK);

  for(int rowCount = 0; rowCount < 8; rowCount++){
    for(int colCount = 0; colCount < 3; colCount++){

			// Make background color white for currently selected preset value
			if(tmpSelectedPresetIndex == cellCount){ 
				tmpFillColor = TFT_WHITE;
      	M5.Display.setTextColor(TFT_BLACK,TFT_WHITE);
			}
			else {
				tmpFillColor = TFT_GREENYELLOW;
      	M5.Display.setTextColor(TFT_BLACK,TFT_GREENYELLOW);
			}

      // Selection Table Background
      M5.Display.fillRoundRect(
        baseLocX + (colCount * (tableCellWidth + horizontalSpacing)),
        baseLocY + (rowCount * (tableCellHeight + verticalSpacing)),
        tableCellWidth,
        tableCellHeight,
        cornerRadius,
        tmpFillColor);
      // Capture attributes and coordinates for cells - used in detecting touches later in code
      tableCellAttributesArray[cellCount].cellNumber =  cellCount;
      tableCellAttributesArray[cellCount].minX = baseLocX + colCount * (tableCellWidth + horizontalSpacing);
      tableCellAttributesArray[cellCount].maxX = baseLocX + colCount * (tableCellWidth + horizontalSpacing) + tableCellWidth;
      tableCellAttributesArray[cellCount].minY = baseLocY + (rowCount * (tableCellHeight + verticalSpacing));
      tableCellAttributesArray[cellCount].maxY = baseLocY + (rowCount * (tableCellHeight + verticalSpacing)) + tableCellHeight;
      tableCellAttributesArray[cellCount].cellState = false;
  
      // Put text labels in cells
      // M5.Display.setTextColor(TFT_BLACK,TFT_GREENYELLOW);
      M5.Lcd.setFreeFont(&AsciiFont8x16); // Sets the font to Free Mono 12pt      
      M5.Display.drawString(
        preSetArray[cellCount].preSetName,
        baseLocX + (colCount * (tableCellWidth + horizontalSpacing)) + 3,
        baseLocY + (rowCount * (tableCellHeight + verticalSpacing)) + 5
      );
      cellCount++;  
    }
  }
}


// DRAW SYNTH PRESET CHOOSER CELL
void SynthPresetSelectionScreen::drawSynthPresetChooserCell(int cellCount, bool highlightOn){
	uint16_t highlightColor;
	if(highlightOn){
		highlightColor = TFT_WHITE;
	}
	else {
		highlightColor = TFT_GREENYELLOW;
	}

	M5.Display.fillRoundRect(
		tableCellAttributesArray[cellCount].minX,
		tableCellAttributesArray[cellCount].minY,
		tableCellWidth,
		tableCellHeight,
		cornerRadius,
		highlightColor);

	// Put text labels in cells
	M5.Display.setTextColor(TFT_BLACK,highlightColor);
	M5.Lcd.setFreeFont(&AsciiFont8x16); // Sets the font to Free Mono 12pt

	// Serial.printf("preSetArray[cellCount].preSetName:%s \n",preSetArray[cellCount].preSetName);
	
	M5.Display.drawString(
		preSetArray[cellCount].preSetName,
		tableCellAttributesArray[cellCount].minX + 3,
		tableCellAttributesArray[cellCount].minY + 5
	);
}


// Need to normalize touch values to display values since
// the screen rotation does not handle this automatically
void SynthPresetSelectionScreen::normalizeXYvalues(int &dispX, int &dispY, int touchX, int touchY){
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


void SynthPresetSelectionScreen::synthPresetSelectionRespondToTouches(int nums, m5::touch_point_t touchPoint[5]){
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
		for(int btnCount = 0; btnCount <= 23; btnCount++) {
			int tmpMinX = tableCellAttributesArray[btnCount].minX;
			int tmpMaxX = tableCellAttributesArray[btnCount].maxX;
			int tmpMinY = tableCellAttributesArray[btnCount].minY;
			int tmpMaxY = tableCellAttributesArray[btnCount].maxY;

			// Check to see if any of those touches are within bounds of one of our buttons 
			if ( (dispX > tmpMinX) && (dispX < tmpMaxX) && (dispY > tmpMinY) && (dispY < tmpMaxY) ){
				// This if statement allows us to skip some of the overall loop steps
				// to act as a kind of debounce function
				int now_millis2 = millis();
				if ((now_millis2 - last_millis2) > millis_interval2) {
					last_millis2 = now_millis2;
					tempTableCellBoolArray[btnCount] = true;
				}
			}
		}
	}
}
	
	
void SynthPresetSelectionScreen::synthPresetSelectionRespondToNoTouches(){
	// If we have no touchPoints then all buttons must be off
	// Reset tempButtonBoolArray to all false so it is picked up
	// and processed in the next code block 
	for(int tmpCntr = 0; tmpCntr <= 23 ; tmpCntr++){
		tempTableCellBoolArray[tmpCntr] = false;
	}
}


void SynthPresetSelectionScreen::synthPresetSelectionCheckForStateChange(){
	// We now know the current button state based on the touches we processed 
	// above, so roll though the topLineButtonArray checking against the 
	// tempButtonBoolArray and process any state changes to buttons
	int highlightOn = true;
	int highlightOff = false;

	for(int cellCount = 0; cellCount <= 23; cellCount++ ) {
		bool currentButtonState = tableCellAttributesArray[cellCount].cellState;
		bool newButtonState = tempTableCellBoolArray[cellCount];
		if(currentButtonState != newButtonState){ // checking to see if old state equals new state
			if(newButtonState == true){ // Button has changed to true state
				tableCellAttributesArray[cellCount].cellState = true;
				// Serial.print("We got a button PRESS on ");
				// Serial.println(tableCellAttributesArray[cellCount].cellNumber);
				drawSynthPresetChooserCell(cellCount, highlightOn);
			}
			else { // Button has changed to false state
				tableCellAttributesArray[cellCount].cellState = false;
				// Serial.print("We got a button RELEASE on ");
				// Serial.println(tableCellAttributesArray[cellCount].cellNumber);
				drawSynthPresetChooserCell(cellCount, highlightOff);
				selectedPresetValue = preSetArray[cellCount].preSetNum;
				selectedPresetIndex = cellCount;
				// Serial.println("From SynthPresetSelectionScreen - changing appExecutionMode to keyboardMode...");
				appExecutionMode = keyboardMode;
			}
		}
	}
}


int SynthPresetSelectionScreen::getSelectedPresetValue(){
	return selectedPresetValue;
}


int SynthPresetSelectionScreen::getSelectedPresetIndex(){
	return selectedPresetIndex;
}


String SynthPresetSelectionScreen::getSelectedPresetName(){
	return preSetArray[selectedPresetIndex].preSetName;
}


int SynthPresetSelectionScreen::getAppExecutionMode(){
	return appExecutionMode;
}
