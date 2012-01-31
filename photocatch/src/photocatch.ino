/*
||
|| @author Yohann Lepage
|| @author Quentin Rousseau
|| @version 0.2
||
|| @description
|| PhotoCatch prend automatiquement une photo lorsque
|| quelqu'un passe devant l'appareil grace à son capteur
|| à ultra-son
||
*/

#include <Servo.h>
#include <SoftwareSerial.h>
#define DEBUG true

// Librairies utilisées
// http://arduino.cc/en/Tutorial/Sweep
// http://arduino.cc/en/Tutorial/Ping

//7 Segments
int rxSegPin =  0;
int txSegPin  = 3;
int photosCounter = 0;
SoftwareSerial segSerial = SoftwareSerial(rxSegPin, txSegPin);

// Ultra Son
// Pin Ultra son
int pingPin = 9;
int val = 0;
int ultrasoundValue = 0;
int timecount = 0; // Echo counter

// Appareil Photo
// Pin Focus
int focusPin = 5;
// Pin Shoot
int shootPin = 6;
// Durée du focus
int focusTime = 0;

// Distance pour le shoot
int shoot_threshold = 100;

// Servo Moteur
Servo myservo;
// Pin Servo
int servoPin = 10;
// Position du Servo Moteur 0 - 180° 
int pos = 0;

// Démarrage de l'Arduino
void setup()
{  
    //Serial pour mode DEBUG
    if(DEBUG)
      Serial.begin(9600);    
    // Attachement du servo au servoPin 
    myservo.attach(servoPin);
    // Passage en mode Output pour l'ultra son
    pinMode(pingPin, OUTPUT);
    // Passage en Output pour le focus
    pinMode(focusPin, OUTPUT);
    // Passage en Output pour le Shoot
    pinMode(shootPin, OUTPUT);
    // Passage en low des focus et shoot
    digitalWrite(focusPin, LOW);
    digitalWrite(shootPin, LOW);
    //7 Segments
    segSerial.begin(9600);
    pinMode(rxSegPin, INPUT);
    pinMode(txSegPin, OUTPUT);
    
    segSerial.print("vv");
    //Turn Colon Off
    segSerial.print('4d',HEX);
    segSerial.print('00',HEX);
}

// Démarrage de la boucle principale
void loop()
{
	// Appel à la méthode de balayage grace au servo
    sweep();
}

// Détection d'un objet
void sonar()
{
   // establish variables for duration of the ping, 
   // and the distance result in inches and centimeters:
   long duration, inches, cm;

   // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
   // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(5);
   digitalWrite(pingPin, LOW);

   // The same pin is used to read the signal from the PING))): a HIGH
   // pulse whose duration is the time (in microseconds) from the sending
   // of the ping to the reception of its echo off of an object.
   pinMode(pingPin, INPUT);
   duration = pulseIn(pingPin, HIGH);
   
   Serial.print(microsecondsToCentimeters(duration));
   Serial.print(" cm\n");
   
   if(microsecondsToCentimeters(duration) <= shoot_threshold)
   {
     shoot();
   } 
   
   delay(150);
}
// Balayage avec le Servo
void sweep()
{
    for(pos = 0; pos < 90; pos += 1) // goes from 0 degrees to 180 degrees
    
    { // in steps of 1 degree
        myservo.write(pos); // tell servo to go to position in variable 'pos'
        //delay(15); // waits 15ms for the servo to reach the position
        sonar();
    }
    
    for(pos = 90; pos >=1; pos-=1) // goes from 180 degrees to 0 degrees
    
    {
        myservo.write(pos); // tell servo to go to position in variable 'pos'
        //delay(15); // waits 15ms for the servo to reach the position
        sonar();
    }
}

long microsecondsToCentimeters(long microseconds)
{
   // The speed of sound is 340 m/s or 29 microseconds per centimeter.
   // The ping travels out and back, so to find the distance of the
   // object we take half of the distance travelled.
   return microseconds / 29 / 2;
}

//Display Photos Counter on the 7 Segments Display
void displaySeg()
{
  photosCounter = photosCounter +1 ;
  
  if(photosCounter < 10) 
  {
    segSerial.print("   ");
    segSerial.print(photosCounter);
  } 
  else if(photosCounter < 100) 
  {
    segSerial.print("  ");
    segSerial.print(photosCounter);
  } 
  else if(photosCounter < 1000) 
  {
    segSerial.print(" ");
    segSerial.print(photosCounter);
  } 
  else 
  {
    segSerial.print(photosCounter);
  } 
  
  Serial.print("Compteur photos : ");
  Serial.print(photosCounter);
  Serial.print("\n");
}

// Capture d'une photo
void shoot()
{
    // Focus
    digitalWrite(focusPin, HIGH);
    delay(focusTime);
    
    // Déclenchement de la photo 
    digitalWrite(shootPin, HIGH);
    delay(200);
    
    displaySeg();
    
    //  Remise à 0 des Pins
    digitalWrite(focusPin, LOW);
    digitalWrite(shootPin, LOW);
}
