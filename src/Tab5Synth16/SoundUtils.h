#ifndef SoundUtils_H
#define SoundUtils_H

#include <M5Unified.h>
#include <AMY-Arduino.h>

void amyConfigStartup();

// noteVelocity range should be .05 to 5
void noteOnOff(int synthChannel,int noteNumber,float noteVelocity);

void configureSynthEngine(int preSetPatchNumber);

void playSomeNotes();

void myBeepFuntion();

#endif