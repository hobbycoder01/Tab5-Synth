# Tab 5 Synth

## What is it
This app turns your M5Stack Tab5 device into a small battery powered, portable musical instrument. By default the app will use the Tab5’s built in speaker, but if headphones are plugged in the audio will be routed through them and the speaker will be muted.
The primary user interface is a two octave virtual keyboard presented on the Tab5 LCD screen with a volume control and 3 virtual buttons that allow the user to select one of the three modes available.  The default mode is “Notes” which tells the app to play one note per keyboard key press.  The user can press up to 5 notes simultaneously to take advantage of the 5 note polyphony of the app.  The other two modes play a chord per keyboard key press.  One chord mode plays major chords and the other plays minor chords. 
The Tab5 device is a small electronic platform, manufactured by the M5Stack company, that integrates an ESP32-P4 microprocessor, a 5 inch touch screen, a snap on rechargeable battery along with electronics that provide audio capabilities and even a camera.  What really attracted me to this device was the solid integration of all the electronic parts.  It is possible to purchase all the underlying electronic components and create a device with similar capabilities, but the Tab5 puts this all together in a really robust compact package with a very nice industrial design at a fair price.

## Why Did I Create It
When I first saw the Tab5 device I immediately thought it would make a great platform for a pocket sized synth.  I wanted to dive into the capabilities of the Tab5 and thought creating a portable synth app would allow me to explore all of it’s technical inner workings.  I have two target audiences for this App.  First, I hope some folks get a Tab5 and use this app to create music.  Second, I hope the code base behind this App can provide examples to others that can be used in their own new projects or to expand this project.

## Feature Set
- Two Octave On Screen Virtual Keyboard
- Five Voice Polyphony
- Three modes of operation: Individual Note, Major Chord, Minor Chord
- 24 Preset Sound Patches can be selected to provide varied instrument sounds
- Automatic speaker muting when headphones are plugged into the Tab5 unit 3.5mm jack
- Code base is logically broken down in an object oriented design
- Extensive commenting within the code

## How was it created
This app is essentially a robust user interface built around the AMY high-performance synthesizer library.  The AMY synthesizer library is fully integrated into the Arduino IDE.  I used the Arduino IDE for almost all the code.  The only exceptions are the two files called GpioExpanderUtility.cpp and SoundUtils.cpp.   For these two files I used the Geany programming editor.  Besides the AMY library, almost everything else is implemented with the M5Unified Arduino library provided by the device manufacturer, M5Stack.
I created this app by working on one segment or feature at a time.  The manufacturer of this device provides some really detailed documentation and code examples which I leveraged heavily to gain the necessary learning to accomplish the overall goal.  The I2C interface to the bus expander (necessary for headphone detection and speaker muting) was probably the most difficult and confusing to me at first, but I eventually worked it out.

## Code Layout
The code layout is as follows (Lines of code shown in parenthesis):
Tab5Synth Folder (Total Lines Of Code: 2023)
- Tab5Synth.ino (210) – The main Arduino Sketch
- GpioExpanderUtility.h (12) – Header file for GpioExpanderUtility.cpp
- IconResources01.h (NA) – Holds the volume up, down and Pre Set Selection icons
- icons.h (NA) – holds the Note icons used in the intro screen animation
- KeyboardClass.cpp (311) – Draws the 2 octave keyboard and handles the key touches
- KeyboardClass.h (224) – The header file for KeyboardClass.cpp
- SoundUtils.h (18) – The header file for SoundUtils.cpp 
- src
  - GpioExpanderUtility.cpp (132) – I2c bus expander for speaker on/off and headphone detection
  - SoundUtils.cpp (91)  – Handles all Amy library interactions and one speaker tone function 
- SynthPresetSelectionScreen.cpp (129) – Draws 24 pre set values to screen and handles keypresses
- SynthPresetSelectionScreen.h (105) – Header file for  SynthPresetSelectionScreen.cpp
- Tab5SynthOpenScreen02.cpp (158) – Draws animation and plays notes for the opening screen
- Tab5SynthOpenScreen02.h (35) – Header file for  Tab5SynthOpenScreen02.cpp
- TopLineButtonClass.cpp (467) – Draws volume, preset, notes & chords buttons; handles keypresses
- TopLineButtonClass.h (131) – Header file for TopLineButtonClass.cpp
    
## Summary
I am still very much a novice in understanding Arduino IDE programming as well as how to implement the full feature set of ESP32 microprocessors.  I learned so much during the creation of this app, but that means that there may be some more efficient or standardized methods to get the same results.  I didn’t have any idea how many lines of code this project would take to implement.  I am not even sure if the resulting 2,023 lines of code is large or small when it comes to ESP32 Arduino projects.  I think the number I ended up with is inflated because I added a lot of comments and in line documentation.  Even though it was frustrating at times, I really enjoyed learning what was necessary to create this App.
