// #include <M5Unified.h>
#include "IconResources01.h"
#include "TopLineButtonClass.h"


// Constructor Definition
TopLineButtonClass::TopLineButtonClass(){
	Serial.println("\n\nStarted TopLineButtonClass Constructor...\n\n");
}


void TopLineButtonClass::drawTopLineControls(){
	drawVolumeDownControl(0);


	refreshVolumeIndicatorBar(speakerVolume/250);
	
	
	drawVolumeUpControl(0);
	drawSynthPresetChooserControl(0);
	drawNotesChordsChooserControls(notesChordsMode);
}


// Need to normalize touch values to display values since
// the screen rotation does not handle this automatically
void TopLineButtonClass::buttonNormalizeXYvalues(int &dispX, int &dispY, int touchX, int touchY){
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


// REFRESH VOLUME INDICATOR BAR //
void TopLineButtonClass::refreshVolumeIndicatorBar(float pctToMax){
	// Serial.printf("Updating REFRESH_VOL_IND_BAR - pctToMax = %f \n",pctToMax);
	int xLoc = 870;
	int yLoc = 6;
	int volumeIndicatorHorizontalSpacing = 200;
	int iconHorizontalSpacing = 20;
	int lineHeight = 6;

	// Draw the background for the volume indicator travel bar
	M5.Display.fillRoundRect(
	xLoc,
	yLoc,
	volumeIndicatorHorizontalSpacing,
	iconHeight,
	11,
	TFT_DARKGREY);
	
	// Draw volume indicator travel bar 
	M5.Display.fillRoundRect(
	xLoc + 2,
	yLoc + (.5 * iconHeight) - 6, 
	volumeIndicatorHorizontalSpacing - 4, 
	lineHeight,
	0,
	TFT_MY_GRAY);

	// Draw volume indicator button
	M5.Display.fillCircle(
	xLoc + 22 + (pctToMax * (volumeIndicatorHorizontalSpacing - 44)), 
	yLoc + (.5 * iconHeight) - 4,
	iconHeight / 4, 
	TFT_MY_GRAY
	);

	// Draw volume indicator button center circle (to give it the outline appearance)
	M5.Display.fillCircle(
	xLoc + 22 + (pctToMax * (volumeIndicatorHorizontalSpacing - 44)), 
	yLoc + (.5 * iconHeight) - 4,
	iconHeight / 4.5, 
	TFT_LIGHTGREY
	);
}


// DRAW VOLUME DOWN CONTROL //
void TopLineButtonClass::drawVolumeDownControl(bool highlightOn){
	// Serial.println("Updating REFRESH_VOL_DOWN");
	// Place volume down icon on screen
	
	uint16_t highlightColor;
	if(highlightOn){
	highlightColor = TFT_WHITE;
	}
	else {
	highlightColor = TFT_DARKGRAY;
	}

	M5.Display.fillRoundRect(
	topLineButtonArray[0].minX,
	topLineButtonArray[0].minY,
	iconWidth,
	iconHeight,
	11,
	highlightColor);

	M5.Display.drawPng(
	volume_down_png,
	volume_down_png_len,
	topLineButtonArray[0].minX + 6,
	topLineButtonArray[0].minY + 4,
	iconWidth,
	iconHeight,
	0,
	0,
	.35,
	.35);
}


// DRAW VOLUME UP CONTROL //
void TopLineButtonClass::drawVolumeUpControl(bool highlightOn){
	// Serial.println("Updating REFRESH_VOL_UP");  
	// Place volume up icon on screen
	
	uint16_t highlightColor;
	if(highlightOn){
	highlightColor = TFT_WHITE;
	}
	else {
	highlightColor = TFT_DARKGRAY;
	}

	M5.Display.fillRoundRect(
	topLineButtonArray[1].minX,
	topLineButtonArray[1].minY,
	iconWidth,
	iconHeight,
	11,
	highlightColor);

	M5.Display.drawPng(
	volume_up_png,
	volume_up_png_len,
	topLineButtonArray[1].minX + 6,
	topLineButtonArray[1].minY + 4,
	iconWidth,
	iconHeight,
	0,
	0,
	.35,
	.35);
}


int TopLineButtonClass::getSpeakerVolume(){
	return speakerVolume;
}


// DRAW SYNTH PRESET CHOOSER CONTROL
void TopLineButtonClass::drawSynthPresetChooserControl(bool highlightOn){
	// Serial.println("Updating REFRESH_PRESET_CHOOSER");     
	// Draw Synth Preset Chooser Icon
	
	uint16_t highlightColor;
	if(highlightOn){
	highlightColor = TFT_WHITE;
	}
	else {
	highlightColor = TFT_DARKGRAY;
	}


	M5.Display.fillRoundRect(
	topLineButtonArray[2].minX,
	topLineButtonArray[2].minY,
	iconWidth,
	iconHeight,
	11,
	highlightColor);

	M5.Display.drawPng(
	setting_config_png,
	setting_config_png_len,
	topLineButtonArray[2].minX + 6,
	topLineButtonArray[2].minY + 4,
	iconWidth,
	iconHeight,
	0,
	0,
	.35,
	.35);
}
	

// Print out the topLineButtonArray
void TopLineButtonClass::printTopLineButtonArray(){
	for (int i = 0; i < 7; i++) {
	Serial.printf(
		"%s   %d.   %d.  %d.  %d.  %d \n",
		topLineButtonArray[i].buttonName,
		topLineButtonArray[i].minX,
		topLineButtonArray[i].maxX,
		topLineButtonArray[i].minY,
		topLineButtonArray[i].maxY,
		topLineButtonArray[i].buttonState
		);
	}
}


// DRAW NOTES / CHORDS CHOOSER CONTROLS
void TopLineButtonClass::drawNotesChordsChooserControls(int notesChordsMode){
	// Serial.println("DRAW NOTES / CHORDS CHOOSER CONTROLS");     
	uint16_t backgroundColor;

	// Rows 3 through 6 of the topLineButtonArray contains the notes/chords controls
	for(int tmpCntr = 3;tmpCntr <7;tmpCntr++){

		if(tmpCntr == notesChordsMode){
			backgroundColor = TFT_GREENYELLOW;
		}
		else {
			backgroundColor = TFT_GREY;
		}

		if(tmpCntr != 4){
			M5.Display.fillRoundRect(
				topLineButtonArray[tmpCntr].minX,
				topLineButtonArray[tmpCntr].minY,
				topLineButtonArray[tmpCntr].maxX - topLineButtonArray[tmpCntr].minX,
				topLineButtonArray[tmpCntr].maxY - topLineButtonArray[tmpCntr].minY,
				8,
				backgroundColor
			);

		}

    // Put text labels on keys
    M5.Display.setTextFont(&FreeSansBoldOblique12pt7b);
		M5.Display.setTextColor(TFT_WHITE,TFT_BLACK);

    M5.Display.drawString(
      topLineButtonArray[tmpCntr].buttonName,
			topLineButtonArray[tmpCntr].minX + 4,
			topLineButtonArray[tmpCntr].minY + 7
    );
	}
}


bool tempButtonBoolArray[3] = {false,false,false};

void TopLineButtonClass::topLineButtonResponseToTouches(int nums, m5::touch_point_t touchPoint[5]){
	// Iterate through all the touches received
	for (int i = 0; i < nums; i++) {  
		int tmpX = touchPoint[i].x;
		int tmpY = touchPoint[i].y;
		dispX = 0;
		dispY = 0;

		// Need to normalize touch values to display values since
		// the screen rotation does not handle this automatically
		buttonNormalizeXYvalues(dispX, dispY, tmpX, tmpY);

		// We have one or more touch values so now iterate
		// through button array to see if any of those
		// touches are within bounds of x and y of any button 
		for(int btnCount = 0; btnCount < 7; btnCount++) {
			int tmpMinX = topLineButtonArray[btnCount].minX;
			int tmpMaxX = topLineButtonArray[btnCount].maxX;
			int tmpMinY = topLineButtonArray[btnCount].minY;
			int tmpMaxY = topLineButtonArray[btnCount].maxY;

			// Check to see if any of those touches are within bounds of one of our buttons 
			if ( (dispX > tmpMinX) && (dispX < tmpMaxX) && (dispY > tmpMinY) && (dispY < tmpMaxY) ){
				// This if statement allows us to skip some of the overall loop steps
				// to act as a kind of debounce function
				int now_millis2 = millis();
				if ((now_millis2 - last_millis2) > millis_interval2) {
					last_millis2 = now_millis2;
					tempButtonBoolArray[btnCount] = true;
				}
			}
		}
	}
}
	
	
void TopLineButtonClass::topLineButtonResponseToNoTouches(){
	// If we have no touchPoints then all buttons must be off
	// Reset tempButtonBoolArray to all false so it is picked up
	// and processed in the next code block 
	for(int tmpCntr = 0; tmpCntr < 7 ; tmpCntr++){
		tempButtonBoolArray[tmpCntr] = false;
	}
}


void TopLineButtonClass::topLineButtonCheckForStateChange(){
	// We now know the current button state based on the touches we processed 
	// above, so roll though the topLineButtonArray checking against the 
	// tempButtonBoolArray and process any state changes to buttons
	for(int buttonCount = 0; buttonCount < 7; buttonCount++ ) {
		bool currentButtonState = topLineButtonArray[buttonCount].buttonState;
		bool newButtonState = tempButtonBoolArray[buttonCount];
		if(currentButtonState != newButtonState){ // checking to see if old state equals new state
			if(newButtonState == true){ // Button has changed to true state
			topLineButtonArray[buttonCount].buttonState = true;
			// Serial.print("We got a button PRESS on ");
			// Serial.println(topLineButtonArray[buttonCount].buttonName);

			switch (buttonCount) {

				case 0:
					drawVolumeDownControl(1);
					speakerVolume  -= 25;
					if(speakerVolume < 0){
						speakerVolume = 0;
					}
					// Serial.printf("    Volume Down speakerVolume = %f  \n",speakerVolume);
					refreshVolumeIndicatorBar(speakerVolume/250);
					M5.Speaker.setVolume(speakerVolume);
					M5.Speaker.setAllChannelVolume(speakerVolume);
					break;

				case 1:
					drawVolumeUpControl(1);
					speakerVolume += 25;
					if(speakerVolume > 250){
						speakerVolume = 250;
					}
					// Serial.printf("   Volume Up speakerVolume = %f  \n",speakerVolume);
					refreshVolumeIndicatorBar(speakerVolume/250);
					M5.Speaker.setVolume(speakerVolume);
					M5.Speaker.setAllChannelVolume(speakerVolume);
					break;

				case 2:
					// Bring up Synth Pre Set Selection Screen
					drawSynthPresetChooserControl(1);
					break;

				case 3:
					// This keeps track of the state of the notes vs chords mode
					// 3 = notes mode
					notesChordsMode = 3;
					drawNotesChordsChooserControls(notesChordsMode);
					break;

				case 4:
					// This keeps track of the state of the notes vs chords mode
					// 4 = should never be this state - it is the "chords" label
					break;

				case 5:
					// This keeps track of the state of the notes vs chords mode
					// 5 = Major Chords Mode
					notesChordsMode = 5;
					drawNotesChordsChooserControls(notesChordsMode);
					break;

				case 6:
					// This keeps track of the state of the notes vs chords mode
					// 6 = Minor Chords Mode
					notesChordsMode = 6;
					drawNotesChordsChooserControls(notesChordsMode);
					break;

				default:
					// code to execute if no cases match
					Serial.print("ERROR IN Button has changed to true state FUNCTION!!!");
					break;
				}
			}

			else { // Button has changed to false state
				topLineButtonArray[buttonCount].buttonState = false;
				// Serial.print("We got a button RELEASE on ");
				// Serial.println(topLineButtonArray[buttonCount].buttonName);

				switch (buttonCount) {
					case 0:
						drawVolumeDownControl(0);
						break;

					case 1:
						drawVolumeUpControl(0);
						break;

					case 2:
						// Bring up Synth Pre Set Selection Screen
						drawSynthPresetChooserControl(0);
						appExecutionMode =  presetSelectionMode;
						break;

					case 3:
						// This keeps track of the state of the notes vs chords mode
						// 3 = notes mode
						notesChordsMode = 3;
						drawNotesChordsChooserControls(notesChordsMode);
						break;

					case 4:
						// This keeps track of the state of the notes vs chords mode
						// 4 = should never be this state - it is the "chords" label
						break;

					case 5:
						// This keeps track of the state of the notes vs chords mode
						// 5 = Major Chords Mode
						notesChordsMode = 5;
						drawNotesChordsChooserControls(notesChordsMode);
						break;

					case 6:
						// This keeps track of the state of the notes vs chords mode
						// 6 = Minor Chords Mode
						notesChordsMode = 6;
						drawNotesChordsChooserControls(notesChordsMode);
						break;

					default:
						// code to execute if no cases match
						Serial.print("ERROR IN Button has changed to false state FUNCTION!!!");
						break;
				}
			}
		}
	}
}


// Returns execution mode value to control swap between keyboard mode and synth
// preset selection mode 
int TopLineButtonClass::getExecutionModeValue(){
	return appExecutionMode;
}


// Resets value for keyboard mode app execution when 
// one of the Preset Selection buttons is pressed
void TopLineButtonClass::resetExecutionModeValue(){
	appExecutionMode = keyboardMode;
}


// Returns value for notesChordsMode 
// 3 = Notes, 4 = Error, 5 = MAJOR (chords), 6 = MINOR (chords)
int TopLineButtonClass::getNotesChordsMode(){
	return notesChordsMode;
}

