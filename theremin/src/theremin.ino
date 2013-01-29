/* 

*********************
Babis Chatzinakis
   27/01/13
*********************

*/


// The pitches.h file must be in another tab on the same sketch with this code
// and can be found with the tone examples

#include "pitches.h"

// Define constants for LED and buttons

const int ledPin =13;
int sensorLow = 1023;
int sensorHigh = 0;
const int buttonPin = 2;
const int buttonPin2 = 4;

// Initialize button stastes

int buttonState = 0;
int buttonState2 = 0;

void setup () {

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  pinMode(buttonPin, INPUT);
  pinMode(buttonPin2, INPUT);

  // Calibrate during the first five seconds
  // while the LED is on. Move your hand further and closer
  // to the two photoresistors

  while (millis() < 5000) {
    int sensorValue = analogRead(A0);
    int sensorValue2 = analogRead(A2);

    //record the maximum sensor value

    if (sensorValue > sensorHigh) {
      sensorHigh = sensorValue;
    }
    
     if (sensorValue2 > sensorHigh) {
      sensorHigh = sensorValue2;
    }
    
    

    //record the minimum sensor value

      if (sensorValue < sensorLow) {

      sensorLow = sensorValue;
    }
    
     if (sensorValue2 < sensorLow) {

      sensorLow = sensorValue2;
    }
  }
  
   
  // Signal the end of the calibration period

  digitalWrite(ledPin, LOW);

}

void loop() {
  
  // Buttons in pins 2 and 4

  int buttonState = digitalRead(buttonPin);
  int buttonState2 = digitalRead(buttonPin2);
  
  // Photoresistors in A0 and A2 inputs
  int sensorValue = analogRead(A0);
  int sensorValue2 = analogRead(A2);
 our
  
  /* SOME SIMPLE MELODIES
     Uncomment the melody you want to play and comment out the previously
     uncommented one
  */

  // C major scale
  /*const int melody[] = { NOTE_C5, NOTE_D5,  NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6 };
  const int melody2[] = { NOTE_C5, NOTE_D5,  NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6 }; */
  
  // Nothing Else Matters intro
  /*const int melody[] = { NOTE_E4, NOTE_G4,  NOTE_B4, NOTE_E5 };
  const int melody2[] = { NOTE_C6, NOTE_B6,  NOTE_A6, NOTE_E5 }; */
  
  // Sweet Child o' Mine intro
  const int melody[] = { NOTE_D4, NOTE_D5, NOTE_A4, NOTE_G4, NOTE_G5, NOTE_G4, NOTE_FS5, NOTE_G4 };
  const int melody2[] = {NOTE_D5, NOTE_D6, NOTE_A5, NOTE_G5, NOTE_G6, NOTE_G5, NOTE_FS6, NOTE_G5 };
  
  // For Elise
  /*const int melody[] = { NOTE_C4, NOTE_B4, NOTE_G4, NOTE_AS4, NOTE_GS4, NOTE_F4};
  const int melody2[] = { NOTE_C5, NOTE_B5,NOTE_G5, NOTE_AS5, NOTE_GS5, NOTE_F5};*/

  // 7 octave chromatic scale (all frequencies)
  /*int pitch= map(sensorValue, sensorLow, sensorHigh, 50, 4000);
  int pitch2= map(sensorValue2, sensorLow, sensorHigh, 50, 4000);*/
  
  // Map the values of the photoresistor to the frequencies defined in the melody arrays

  int pitch_temp = map(sensorValue, sensorLow, sensorHigh, 0, sizeof(melody)/sizeof(melody[0])+1);
  int pitch = melody[pitch_temp];
  
  int pitch_temp2 = map(sensorValue2, sensorLow, sensorHigh, 0, sizeof(melody2)/sizeof(melody2[0])+1);
  int pitch2 = melody2[pitch_temp2];
  
  
  // Play the lower octave if button 1 is pressed  
  // first buzzer in pin 8
  if (buttonState == HIGH) {     
    
    tone(8, pitch, 50);
    
    
  }
  
  // Play the higher octave if button 2 is pressed
  // second buzzer in pin 10
  if (buttonState2 == HIGH) {
    
    tone(10, pitch2, 50);
    
  }
  
}
