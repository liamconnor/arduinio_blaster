#include "Buttons.h"

//------Notes-------------
#define NOTE_ONE 36
#define NOTE_TWO 37
#define NOTE_THREE 38


#define NOTE_ON_CMD 0x90
#define NOTE_OFF_CMD 0x80
#define MAX_MIDI_VELOCITY 136

//------------------------

int NUMBER_BUTTONS = 3;

Button Button1(13, NOTE_ONE);
Button Button2(7, NOTE_TWO);
Button Button3(4, NOTE_THREE);

Button *Buttons[] {&Button1,&Button2,&Button3};

int red_light_pin= 11;
int green_light_pin = 12;
int blue_light_pin = 13;

void setup() {
   Serial.begin(9600);
}

void loop() {
  if (NUMBER_BUTTONS != 0) updateButtons();
}

void updateButtons() {

  for (int i = 0; i < NUMBER_BUTTONS; i++) {
      int state = Buttons[i]->getButtonState();
      
      //  Button is pressed     
      if (state == 0) 
      {
         midiNoteOn(Buttons[i]->Note,127);
      }
  
      //  Button is not pressed
      if (state == 1) 
      {
         midiNoteOff(Buttons[i]->Note,0); 
      }
  }
}


void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}

// Send MIDI note ON
void midiNoteOn(byte note, byte midiVelocity)
{
  Serial.write(NOTE_ON_CMD);
  Serial.write(note);
  Serial.write(midiVelocity);
}

//Send MIDI note OFF
void midiNoteOff(byte note, byte midiVelocity)
{
  Serial.write(NOTE_OFF_CMD);
  Serial.write(note);
  Serial.write(midiVelocity);
}
