/*
 ArduinoAtmogram
 
 Monitor the temperature and humidity and display the values on the LCD screen.
 It also POST the values to a web server to log it.
  
 Build on the top of Web client arduino's example.
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * DHT11 (temp & humidity sensors)
 * LCD4884 shield
 
 Florian Lissot & Victor Jolissaint
 @ FabLab Telecom Bretagne 2012.
 */

#include <SPI.h>
#include <Ethernet.h>
#include "LCD4884.h"
#include "DHT.h"

#define DHTPIN A1       // what pin we're connected to
#define DHTTYPE DHT11   // DHT 11 : our captor

DHT dht(DHTPIN, DHTTYPE);

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,0, 2); // IP Arduino
IPAddress server(192,168,0, 254); // IP web server

// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

void setup() {
  // start the serial library:
  Serial.begin(9600);
  // start the Ethernet connection:
  Ethernet.begin(mac, ip);
  
  // Show if the @IP is set
  // print your local IP address:
  Serial.print("My IP address: ");
  ip = Ethernet.localIP();
  for (byte thisByte = 0; thisByte < 4; thisByte++)
  {
    // print the value of each byte of the IP address:
    Serial.print(ip[thisByte], DEC);
    Serial.print("."); 
  }
  Serial.println();
  
  /* init lcd screen */
  lcd.LCD_init();
  lcd.LCD_clear();
  lcd.LCD_write_string(0, 0, "Florian &", MENU_NORMAL );
  lcd.LCD_write_string(0, 1, "Victor", MENU_NORMAL );
  lcd.LCD_write_string(0, 2, "presents:", MENU_NORMAL );
  lcd.LCD_write_string(0, 3, "", MENU_NORMAL );
  lcd.LCD_write_string(0, 4, "      Arduino", MENU_NORMAL );
  lcd.LCD_write_string(0, 5, "     Atmogram", MENU_NORMAL );
  
  // LCD blink 3 times
  lcdBlink(3, 200);
  
  // Sensors
  dht.begin();
  
  // Give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("ready...");
}

void loop()
{
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float humi = dht.readHumidity();
  float temp = dht.readTemperature();

  // Convert int to char
  char humiBuf[3];
  char tempBuf[3];
  sprintf(humiBuf, "%d", (int)humi);
  sprintf(tempBuf, "%d", (int)temp);  

  // Check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(temp) || isnan(humi)) {
    Serial.println("Failed to read from DHT");
  } 
  else {
    Serial.print("Humidity: "); 
    Serial.print(humi);
    Serial.print(" %\t");
    Serial.print("Temperature: "); 
    Serial.print(temp);
    Serial.println(" *C");
  }
  
  lcd.LCD_clear();
  
  // int raw = analogRead(8);
  // int temp = MULTIPLIER * (float) raw;
  char tempString[6] = "";
  char humiString[6] = "";
  
  sprintf(tempString,"%d",(int)temp);
  sprintf(humiString,"%d",(int)humi);
  
  // Draw a cloud    
  unsigned char sunnycloudbmp[] = 
  {
    0x00,0xE0,0x18,0x0C,0x0C,0x08,0x08,0xD0,0x20,0x10,0x08,0x08,0x08,0x10,0x10,0x30,0x10,0x20,0x24,0x44,0x48,0xB0,0x10,0x13,0x0C,0x08,0x08,0x1C,0x16,0x71,0xA0,0x10,0x18,0x08,0x00,
    0x00,0x71,0x9F,0x03,0x02,0x02,0x00,0x20,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x00,0x08,0x08,0x0F,0x08,0x88,0x88,0x90,0xF0,0x70,0xCC,0x0F,0x19,0x31,0x61,0x01,
    0x00,0x00,0x01,0x02,0x02,0x02,0x02,0x02,0x02,0x01,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x03,0x04,0x04,0x0C,0x08,0x08,0x08,0x0C,0x07,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00
  };
  lcd.LCD_draw_bmp_pixel(40, 0, sunnycloudbmp, 35,20); // (posi,tion , name, si,ze)
  
  // Display temp
  lcd.LCD_write_string(0, 1, "+", MENU_NORMAL);
  lcd.LCD_write_string_big(6, 0, tempString, MENU_NORMAL);
  lcd.LCD_write_string(30, 1, "C", MENU_NORMAL);
   
  // Draw a drop 
  unsigned char dropbmp[] = 
    {
      0x00,0x00,0x00,0x80,0x40,0x20,0x18,0x07,0x0C,0x10,0x60,0x80,0x00,0x00,0x00,
      0x00,0x00,0x06,0x0B,0x10,0x26,0x28,0x28,0x20,0x20,0x10,0x0F,0x00,0x00,0x00
    };
  lcd.LCD_draw_bmp_pixel(32,4, dropbmp, 15,15); // (posi,tion , name, si,ze) 
  
  // Display humidity
  lcd.LCD_write_string_big(50, 3, humiString, MENU_NORMAL);
  lcd.LCD_write_string(75, 4, "%", MENU_NORMAL);
  
  Serial.println("connecting...");
  
  // If you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected");
    
    // Make a HTTP request:
    char req[80];
    sprintf(req, "GET /index.php?temp=%s&humi=%s HTTP/1.0", tempBuf, humiBuf);
    
    //Serial.println(req); // print the request
    
    client.println(req); //send request
    client.println();
  } 
  else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
  
  // if there are incoming bytes available 
  // from the server, read them and print them:
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }
  
  client.stop(); // if not, it can re-connect anymore
  
  // Refresh time
  delay(10000);

  // LCD blink 2 times to notify the refresh
  lcdBlink(2, 200);
}

void lcdBlink(int count, int delayMs) {
    for(int i=0; i< count; i++){
      lcd.LCD_backlight(1);
      delay(delayMs);
      lcd.LCD_backlight(0);     
      delay(delayMs);
    }
    lcd.LCD_backlight(1);
}
