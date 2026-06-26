#include "../GpioExpanderUtility.h"
#include <M5Unified.h>



// *** I/O Expander PI4IOE5V6408 I2C Definitions *** //
// Set GPIO 31 as SDA and GPIO 32 as SCL for Tab5
uint8_t IO_EXPANDER_SDA_GPIO = 31;
uint8_t IO_EXPANDER_SCL_GPIO = 32;
// CALL TO FUNCTION: M5.In_I2C.bitOff(0x43, 0x05, 0b00000010, 400000);
// FUNCTION PROTOTYPE: M5.In_I2C.bitOff(Io Expander Address, GPIO REGISTER, PERIPHERIAL BIT LOCATION, FREQ);
// Chip U6 PI4IOE5V6408 - GPIO Expander
std::uint8_t IO_EXPANDER_U6_ADDR = 0x43;  // Chip U6 PI4IOE5V6408 (Includes SPK_EN on P1)
uint8_t SPK_AMP = 0b00000010;        // Speaker Amp Bit On IO_EXPANDER_U6_ADDR 0x43
uint8_t HP_DET = 0b10000000; // Headphone detection bit on IO_EXPANDER_U6_ADDR 0x43
// Chip U7 PI4IOE5V6408 - GPIO Expander
std::uint8_t  IO_EXPANDER_U7_ADDR = 0x44;  // Chip U7 PI4IOE5V6408
uint8_t USBA_5V_EN = 0b00001000;     // USB A 5V Bit On IO_EXPANDER_U6_ADDR 0x44
// GPIO Expander Registers
std::uint8_t  IO_EXPANDER_IO_DIRECTION = 0x03;  // pin direction - 0 is an output and 1 is an input
std::uint8_t IO_EXPANDER_OUTPUT_STATE = 0x05;  // outgoing logic levels of the pins defined as outputs
std::uint8_t  IO_EXPANDER_INPUT_STATUS = 0x0F;  // incoming logic levels of the pins set as inputs
// Frequency of transmission for ESP32-P4 on Tab 5
std::uint32_t TAB5_XMIT_FREQ = 400000;
// *** I/O Expander PI4IOE5V6408 I2C Definitions *** //


void turnSpeakerOnOff(int onOff){
	uint8_t resultCode;
  // Initialize I2C
  resultCode = M5.In_I2C.begin();
  // Serial.print("\nResult Code from I2C.Begin:");
  // Serial.println(resultCode, BIN);

  // Read the incoming logic states of Chip U6 PI4IOE5V6408 (Includes HP_DET on P7)
  resultCode = M5.In_I2C.readRegister8(IO_EXPANDER_U6_ADDR, IO_EXPANDER_OUTPUT_STATE, TAB5_XMIT_FREQ);
  // Serial.print("\nResult Code from readRegister8 INITIAL:");
  // Serial.println(resultCode, BIN);

  if(onOff == 1){
  // Turn the speaker amp bit on
  resultCode = M5.In_I2C.bitOn(IO_EXPANDER_U6_ADDR, IO_EXPANDER_OUTPUT_STATE, SPK_AMP, TAB5_XMIT_FREQ);
  // Serial.print("\nResult Code from bitOn:");
  // Serial.println(resultCode, BIN);
  }
  else {
  // Turn the speaker amp bit off
  resultCode = M5.In_I2C.bitOff(IO_EXPANDER_U6_ADDR, IO_EXPANDER_OUTPUT_STATE, SPK_AMP, TAB5_XMIT_FREQ);
  // Serial.print("\nResult Code from bitOn:");
  // Serial.println(resultCode, BIN);
  }

  // Read the outoing logic states again to ensure bit 2 (SPK_AMP) is off
  // resultCode = M5.In_I2C.readRegister8(std::uint8_t address, std::uint8_t reg, std::uint32_t freq)
  resultCode = M5.In_I2C.readRegister8(IO_EXPANDER_U6_ADDR, IO_EXPANDER_OUTPUT_STATE, TAB5_XMIT_FREQ);
  // Serial.print("\nResult Code from readRegister8 AFTER CHANGE:");
  // Serial.println(resultCode, BIN);
}	
	
	
int checkForHeadphone(){	
  uint8_t resultCode;
  // Initialize I2C
  resultCode = M5.In_I2C.begin();
  // Serial.print("\nResult Code from I2C.Begin:");
  // Serial.println(resultCode, BIN);

  // Read the outgoing logic states of Chip U6 PI4IOE5V6408 (Includes SPK_EN on P1)
  resultCode = M5.In_I2C.readRegister8(IO_EXPANDER_U6_ADDR, IO_EXPANDER_INPUT_STATUS, TAB5_XMIT_FREQ);
  // Serial.print("\nResult Code from readRegister8 IO_EXPANDER_INPUT_STATUS:");
  // Serial.println(resultCode, BIN);

  if(resultCode >= HP_DET){
  // Headphone Is Present
  return 1;
  }
  else {
  // Headphone Not Present
  return 0;
  }
}


void checkForHeadphoneAndReact(){
	int headphoneStatus = 0;
  int speakerSwitch = 0;
  headphoneStatus = checkForHeadphone();
  // Serial.println(headphoneStatus);
  if(headphoneStatus == 1){
    speakerSwitch = 0;
  }
  else {
    speakerSwitch = 1;
  }
  turnSpeakerOnOff(speakerSwitch);
}


/*
void setup() {
  // put your setup code here, to run once:
  M5.begin();
  Serial.begin(115200);
  // sets the output master volume of the sound.
  // @param master_volume master volume (0~255)
  M5.Speaker.setVolume(200);
  Serial.println("Starting Execution...");
}


void loop() {
  // put your main code here, to run repeatedly:
  int headphoneStatus = 0;
  int speakerSwitch = 0;
  headphoneStatus = checkForHeadphone();
  Serial.println(headphoneStatus);
  if(headphoneStatus == 1){
    speakerSwitch = 0;
  }
  else {
    speakerSwitch = 1;
  }
  turnSpeakerOnOff(speakerSwitch);
  Serial.println("Playing Tone...");
    // tone, duration, channel, stop_current_sound
  M5.Speaker.tone(261.626, 500, 1, false);  
  M5.delay(1500);
}
*/
