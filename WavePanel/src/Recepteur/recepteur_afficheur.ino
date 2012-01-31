/*
This programme manages the reception of a message sent by wireless and draws it on a LED matrix.

A XBee shield is used for the wireless communication

*/



#include <XBee.h>
#include <ht1632c.h>


XBee xbee = XBee();
XBeeResponse response = XBeeResponse();
// create reusable response objects for responses we expect to handle 
Rx16Response rx16 = Rx16Response();

int photores = A0;

int statusLed = 11;
int errorLed = 12;
int dataLed = 10;

int i = 0;
int message_received = 0;

int lumin = 0;
char message[100] = {0};
String mess = "";
char c;
int couleur = RED;

boolean new_message = false;

uint8_t option = 0;
uint8_t data = 0;
uint8_t taille = 0;

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



//Initialisation ht1632c-------------------------------------
ht1632c dotmatrix = ht1632c(PORTD, 7, 6, 4, 5, GEOM_32x16, 2);

void setup() 
{
  pinMode(photores, INPUT);
  
  pinMode(statusLed, OUTPUT);
  pinMode(errorLed, OUTPUT);
  pinMode(dataLed, OUTPUT);
  
  // start serial
  xbee.begin(9600);
  Serial.begin(9600);
  
  dotmatrix.clear();
  
  flashLed(statusLed, 3, 50);
}

// continuously reads packets, looking for RX16
void loop() 
{
  if(message_received < 1)
  {  
    xbee.readPacket();
        
    if (xbee.getResponse().isAvailable()) 
    {
      // got something
      xbee.getResponse().getRx16Response(rx16);
      option = rx16.getOption();
      data = rx16.getData(1);
      taille = rx16.getDataLength();
      
      c = char(rx16.getData(0));
      for(i=0;i<taille;i++)
      {
        if(message[i] != char(rx16.getData(i+1)))
        {
          new_message = true; 
        }
        message[i] = char(rx16.getData(i+1));
      }
       
            
      // TODO check option, rssi bytes
      flashLed(statusLed, 1, 100);
      message_received++;
      
      
    }
    else
    {
      	// not something we were expecting
        flashLed(errorLed, 1, 25);    
    }
  }
  else
  {
    // screening -----------------------------------------
    int x = 0;
    int y = 3;
    
    if(c == 'r')
    {
      couleur = RED; 
    }
    else if(c == 'o')
    {
      couleur = ORANGE; 
    }
    else if(c == 'v')
    {
      couleur = GREEN; 
    }
    
    //luminosity captor
    lumin = map(analogRead(photores), 0, 1023, 0, 15);
    dotmatrix.pwm(lumin);
    

    if(new_message)
    {
	  //Message receceived drawing
      dotmatrix.line(0, 0, 0, 7, couleur);
      dotmatrix.sendframe();
      delay(80);
      dotmatrix.line(0, 8, 0, 15, couleur);
      dotmatrix.sendframe();
      delay(80);
      
      dotmatrix.line(0, 15, 7, 15, couleur);
      dotmatrix.sendframe();
      delay(80);
      dotmatrix.line(8, 15, 15, 15, couleur);
      dotmatrix.sendframe();
      delay(80);
      dotmatrix.line(16, 15, 23, 15, couleur);
      dotmatrix.sendframe();
      delay(80);
      dotmatrix.line(24, 15, 31, 15, couleur);
      dotmatrix.sendframe();
      delay(80);
      
      dotmatrix.line(31, 15, 31, 8, couleur);
      dotmatrix.sendframe();
      delay(80);
      dotmatrix.line(31, 7, 31, 0, couleur);
      dotmatrix.sendframe();
      delay(80);
      
      dotmatrix.line(31, 0, 24, 0, couleur);
      dotmatrix.sendframe();
      delay(80);
      dotmatrix.line(23, 0, 16, 0, couleur);
      dotmatrix.sendframe();
      delay(80);
      dotmatrix.line(15, 0, 8, 0, couleur);
      dotmatrix.sendframe();
      delay(80);
      dotmatrix.line(7, 0, 0, 0, couleur);
      dotmatrix.sendframe();
      delay(80);
      
      dotmatrix.line(0, 1, 7, 4, couleur);
      dotmatrix.sendframe();
      delay(80);
      dotmatrix.line(8, 5, 15, 8, couleur);
      dotmatrix.sendframe();
      delay(80);
      
      dotmatrix.line(16, 8, 23, 5, couleur);
      dotmatrix.sendframe();
      delay(80);
      dotmatrix.line(24, 4, 31, 1, couleur);
      dotmatrix.sendframe();
      
   
      delay(3000);
      
      new_message = false; 
    }
    
    dotmatrix.clear();
    
    dotmatrix.hscrolltext(y, message, couleur, 100);
    
  
    message_received--;
  
    //delay(400);
    dotmatrix.clear(); 
    
    if(couleur == GREEN)
    {
      //Mario
      y = 0;
      for(x = -13; x<31; x++)
      {
        dotmatrix.clear();
    
        dotmatrix.line(x+3, y, x+7, y, RED);
        
        dotmatrix.line(x+2, y+1, x+10, y+1, RED);
        
        dotmatrix.line(x+2, y+2, x+4, y+2, GREEN);
        dotmatrix.line(x+5, y+2, x+6, y+2, ORANGE);
        dotmatrix.plot(x+7, y+2, GREEN);
        dotmatrix.plot(x+8, y+2, ORANGE);
        
        dotmatrix.plot(x+1, y+3, GREEN);
        dotmatrix.plot(x+2, y+3, ORANGE);
        dotmatrix.plot(x+3, y+3, GREEN);
        dotmatrix.line(x+4, y+3, x+6, y+3, ORANGE);
        dotmatrix.plot(x+7, y+3, GREEN);
        dotmatrix.line(x+8, y+3, x+10, y+3, ORANGE);
     
        dotmatrix.plot(x+1, y+4, GREEN);
        dotmatrix.plot(x+2, y+4, ORANGE);
        dotmatrix.plot(x+3, y+4, GREEN);
        dotmatrix.plot(x+4, y+4, GREEN);
        dotmatrix.line(x+5, y+4, x+7, y+4, ORANGE);
        dotmatrix.plot(x+8, y+4, GREEN);
        dotmatrix.line(x+9, y+4, x+11, y+4, ORANGE);
      
        dotmatrix.plot(x+1, y+5, GREEN);
        dotmatrix.plot(x+2, y+5, GREEN);
        dotmatrix.line(x+3, y+5, x+6, y+5, ORANGE);
        dotmatrix.line(x+7, y+5, x+10, y+5, GREEN);
        
        dotmatrix.line(x+3, y+6, x+9, y+6, ORANGE);
        
        dotmatrix.plot(x+2, y+7, GREEN);
        dotmatrix.plot(x+3, y+7, GREEN);
        dotmatrix.plot(x+4, y+7, RED);
        dotmatrix.line(x+5, y+7, x+7, y+7, GREEN);
        
        dotmatrix.line(x+1, y+8, x+3, y+8, GREEN);
        dotmatrix.plot(x+4, y+8, RED);
        dotmatrix.plot(x+5, y+8, GREEN);
        dotmatrix.plot(x+6, y+8, GREEN);
        dotmatrix.plot(x+7, y+8, RED);      
        dotmatrix.line(x+8, y+8, x+10, y+8, GREEN);
        
        dotmatrix.line(x+0, y+9, x+3, y+9, GREEN);
        dotmatrix.line(x+4, y+9, x+7, y+9, GREEN);
        dotmatrix.line(x+8, y+9, x+11, y+9, GREEN);
        
        dotmatrix.plot(x, y+10, ORANGE);
        dotmatrix.plot(x+1, y+10, ORANGE);
        dotmatrix.plot(x+2, y+10, GREEN);
        dotmatrix.plot(x+3, y+10, RED);
        dotmatrix.plot(x+4, y+10, ORANGE);
        dotmatrix.plot(x+5, y+10, RED);
        dotmatrix.plot(x+6, y+10, RED);
        dotmatrix.plot(x+7, y+10, ORANGE);
        dotmatrix.plot(x+8, y+10, RED);
        dotmatrix.plot(x+9, y+10, GREEN);
        dotmatrix.plot(x+10, y+10, RED);
        dotmatrix.plot(x+11, y+10, RED);
        
        dotmatrix.line(x, y+11, x+2, y+11, ORANGE);
        dotmatrix.line(x+3, y+11, x+8, y+11, RED);
        dotmatrix.line(x+9, y+11, x+11, y+11, ORANGE);
        
        dotmatrix.line(x, y+12, x+1, y+12, ORANGE);
        dotmatrix.line(x+2, y+12, x+9, y+12, RED);
        dotmatrix.line(x+10, y+12, x+11, y+12, ORANGE);
        
        dotmatrix.line(x+2, y+13, x+4, y+13, RED);
        dotmatrix.line(x+7, y+13, x+9, y+13, RED);
        
        dotmatrix.line(x+1, y+14, x+3, y+14, GREEN);
        dotmatrix.line(x+8, y+14, x+10, y+14, GREEN);
        
        dotmatrix.line(x, y+15, x+3, y+15, GREEN);
        dotmatrix.line(x+8, y+15, x+11, y+15, GREEN);
        
        dotmatrix.sendframe();
        delay(100);
        dotmatrix.clear(); 
        
        
        
        
        
      }
    }
    
    else
    {
      //Space Invader
      y = 4;
      for(x = 31;x>-12;x--)
      {      
        dotmatrix.clear();
        
        dotmatrix.plot(x+2, y, couleur);
        dotmatrix.plot(x+8, y, couleur);
        dotmatrix.plot(x+3, y+1, couleur);
        dotmatrix.plot(x+7, y+1, couleur);
        
        dotmatrix.line(x+2, y+2, x+8, y+2, couleur);
        
        dotmatrix.plot(x+1, y+3, couleur);
        dotmatrix.plot(x+2, y+3, couleur);
        dotmatrix.plot(x+3, y+3, GREEN);
        dotmatrix.plot(x+4, y+3, couleur);
        dotmatrix.plot(x+5, y+3, couleur);
        dotmatrix.plot(x+6, y+3, couleur);
        dotmatrix.plot(x+7, y+3, GREEN);
        dotmatrix.plot(x+8, y+3, couleur);
        dotmatrix.plot(x+9, y+3, couleur);
        
        dotmatrix.line(x, y+4, x+10, y+4, couleur);
        
        dotmatrix.plot(x, y+5, couleur);
        dotmatrix.line(x+2, y+5, x+8, y+5, couleur);
        dotmatrix.plot(x+10, y+5, couleur);
        
        dotmatrix.plot(x, y+6, couleur);
        dotmatrix.plot(x+2, y+6, couleur);
        dotmatrix.plot(x+8, y+6, couleur);
        dotmatrix.plot(x+10, y+6, couleur);
        
        dotmatrix.plot(x+3, y+7, couleur);
        dotmatrix.plot(x+4, y+7, couleur);
        dotmatrix.plot(x+6, y+7, couleur);
        dotmatrix.plot(x+7, y+7, couleur);
        
        
        dotmatrix.sendframe();
        delay(100);
      }    
    }

  }
  
}