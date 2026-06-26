#include "../SoundUtils.h"
#include <M5Unified.h>
#include <AMY-Arduino.h>


void amyConfigStartup(){
  // Amy config and startup
  // Serial.println("At top of amyConfigStartup...");
  amy_config_t amy_config = amy_default_config();
  amy_config.features.startup_bleep = 1;
  // Install the default_synths on synths (MIDI chans) 1, 2, and 10 (this is the default).
  amy_config.features.default_synths = 1;
  amy_config.features.chorus = 0;
  amy_config.features.reverb = 0;
  amy_config.audio = AMY_AUDIO_IS_I2S;

  // Critical pin configuration for M5Stack Tab5 internal circuit wiring //
  amy_config.i2s_bclk = 27;
  amy_config.i2s_lrc = 29;
  amy_config.i2s_dout = 26;
  amy_config.platform.multicore = 1;
  amy_config.platform.multithread = 1;
  amy_start(amy_config);
  M5.delay(1500);
}


void noteOnOff(int synthChannel,int noteNumber,float noteVelocity){
  // Serial.printf("Executing noteOnOff  Chan:%d,Note:%d,Vel:%f\n",synthChannel,noteNumber,noteVelocity);
  M5.Speaker.setVolume(0);
  amy_event e = amy_default_event();
  e.synth = synthChannel;
  e.midi_note = noteNumber;
  e.velocity = noteVelocity;  
  amy_add_event(&e);
}


void configureSynthEngine(int preSetPatchNumber) {
  // Configure Synth Engine - 1 Channel with 5 voices and preSet patch number
  // Serial.println("At top of configureSynthEngine...");
  amy_event e = amy_default_event();
  e.synth = 1;
  e.num_voices = 5;
  e.patch_number = preSetPatchNumber;  // Juno A18 Piano I
  amy_add_event(&e);
}


void playSomeNotes() {
  // Serial.println("At top of playSomeNotes...");
  M5.Speaker.setVolume(0);
  // Prototype for function: noteOnOff(int synthChannel,int noteNumber,int noteVelocity,int synthPatchNum);
  // Turn on 3 notes in chord staggered by 1.5 sec
  noteOnOff(1,60,.25);
  M5.delay(25);
  noteOnOff(1,64,.25);
  M5.delay(25);
  noteOnOff(1,67,.25);
  M5.delay(25);
  // Turn off 3 notes in chord staggered by 1.5 sec
  noteOnOff(1,60,0);
  M5.delay(25);
  noteOnOff(1,64,0);
  M5.delay(25);
  noteOnOff(1,67,0);
  M5.delay(25);
}


void myBeepFuntion() {
  // ######### MY BEEP FUNCTION ########## //
  // The notes in a G chord are G, B, and D
  // The notes in a C chord are C, E, and G
  float octive4CFreq = 261.626;
  float octive4DFreq = 293.66;
  float octive4EFreq = 329.63;
  float octive4FFreq = 349.23;
  float octive4GFreq = 392.0;
  float octive4AFreq = 440.0;
  float octive4BFreq = 493.88;
  float octive5CFreq = 523.25;
  float octive5DFreq = 587.33;

  // tone, duration, channel, stop_current_sound
  M5.Speaker.tone(octive4CFreq, 25, 1, false);  
  M5.Speaker.tone(octive4EFreq, 25, 2, false);  
  M5.Speaker.tone(octive4GFreq, 25, 3, false);  
  // Wait for tone to be done playing
  while (M5.Speaker.isPlaying()) { M5.delay(1); } 
}

