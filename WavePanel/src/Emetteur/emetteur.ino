
/*

This program manages the emission of a string of characters which will be emitted to another arduino.
A XBee shield is used for the wireless communication

*/



#include <XBee.h>


XBee xbee = XBee();

unsigned long start = millis();

// allocate two bytes for to hold a 10-bit analog reading
char msg[] = "IT'S ME, MARIO !";
uint8_t payload[80] = "g";

boolean acquis = true;
boolean requeteOK = false;
char thisChar = 0;
int i = 0;
char couleur = 'g';

// with Series 1 you can use either 16-bit or 64-bit addressing


// 16-bit addressing: Enter address of remote XBee, typically the coordinator
Tx16Request tx = Tx16Request(0xFFFF, payload, sizeof(payload));

// 64-bit addressing: This is the SH + SL address of remote XBee
//XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x4008b490);
// unless you have MY on the receiving radio set to FFFF, this will be received as a RX16 packet
//Tx64Request tx = Tx64Request(addr64, payload, sizeof(payload));

TxStatusResponse txStatus = TxStatusResponse();


int statusLed = 11;
int errorLed = 12;

int Bvert = 5;
int Borange = 6;
int Brouge = 7;

void flashLed(int pin, int times, int wait) {
    
    for (int i = 0; i < times; i++) {
      digitalWrite(pin, HIGH);
      delay(wait);
      digitalWrite(pin, LOW);
      
      if (i + 1 < times) {
        delay(wait);
      }
    }
}

void setup() {
  
  pinMode(Bvert, INPUT);
  pinMode(Borange, INPUT);
  pinMode(Brouge, INPUT);
  
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  
  pinMode(statusLed, OUTPUT);
  pinMode(errorLed, OUTPUT);
  
  xbee.begin(9600);
  Serial.println("Ecrire un message:");
  Serial.println();
  
}

void loop() 
{
  
  //Choix de la couleur -----------------------------
  if(digitalRead(Brouge) == HIGH)
  {
    couleur = 'r';
    requeteOK = false;
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
  }
  else if(digitalRead(Borange) == HIGH)
  {
    couleur = 'o';
    requeteOK = false;
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
  }
  else if(digitalRead(Bvert) == HIGH)
  {
    couleur = 'v';
    requeteOK = false;
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
  }
  
  
  
  
  //String conversion ------------------------------------
  if(!acquis)
  {
    if (Serial.available() > 0) 
    {
      thisChar = Serial.read();
      
      if(thisChar != '$')
      {
        msg[i] = thisChar;
        i++; 

      }
      else
      {
        msg[i] = '\0';
        acquis = true;

      }
      
    } 
  }
  else 
  {
    if(!requeteOK)
    {
      int j = 0;
      payload[0] = couleur;
      while(msg[j] != '\0')
      {
        payload[j+1] = msg[j];
        j++;
      }
      
      
      requeteOK = true;
      Serial.println(msg);
    }
    else
    {
      Serial.println(msg);
      xbee.send(tx);   
      // flash TX indicator
      flashLed(statusLed, 1, 100);
    }
  }
  
    flashLed(errorLed, 2, 25);
      
    delay(200);
}

