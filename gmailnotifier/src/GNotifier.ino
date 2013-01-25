/*

 GNotifier v1.0
 
 Key Features:
 * Display number of mail unread
 * Diplay hour
 * Display the subject and the emitter of the last unread three mails
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Sure Electronics 3216 LED matrix attached to pins 4, 5, 6, 7
 * Servomotor attached to pin 9
 
 created 22 Jan 2013
 by Baptiste Lamanda, Thierry Berthou and Najib Bajdouri
 */
 
#include <SPI.h>
#include <Ethernet.h>
#include <ht1632c.h>
#include <Servo.h> 
 
#define DEBUG

// initialize the dotmatrix with the numbers of the interface pins (data→7, wr →6, clk→4, cs→5)
ht1632c dotmatrix = ht1632c(&PORTD, 7, 6, 4, 5, GEOM_32x16, 2);

Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
byte pwm = 15;            // value output to the PWM (analog out)

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] =   {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x01 };

// fill in an available IP address on your network here,
// for auto-configuration:
IPAddress ip(192,168,1,20);
IPAddress subnet(255, 255, 0, 0);

// initialize the library instance:
EthernetClient client;

const int requestInterval = 100000;     // delay between requests

IPAddress server(192,168,25,26);  // Your favorite API server

// Variables used to parse the XML from emoncms

String currentLine = "";             // string to hold the text from server
String content = "";

boolean readingTime = false;
boolean readingEmails = false;
boolean readingCount = false;

String time = "";
String unreadMailsCount = "0";
String unreadMails[3];

char errorStr[11] = "NO SERVICE";

int cpt = 0;
int NbMails = 3;
int MailLength = 50;

byte color;

// email sprite
uint16_t emailSprite[7] = {0x0fe, 0x0183, 0x0145, 0x0129, 0x0111, 0x0101, 0x0fe};

void setup() {
  // reserve space for the strings:
  currentLine.reserve(128);
  content.reserve(64);
  time.reserve(8);
  unreadMailsCount.reserve(4);
  unreadMails[0].reserve(64);
  unreadMails[1].reserve(64);
  unreadMails[2].reserve(64);
  
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  myservo.write(30);  
  
  // Dotmatrix brightness
  dotmatrix.pwm(pwm);
  
  // initialize serial:
  #ifdef DEBUG
  Serial.begin(9600);
  #endif
  // initialize dotmatrix:
  dotmatrix.clear();
  
  // display a welcome message:
  #ifdef DEBUG
  Serial.println("GNotifier v1.0 starting...");
  #endif
  
  // attempt a DHCP connection:
  if (!Ethernet.begin(mac)) {
    // if DHCP fails, start with a hard-coded address:
    Ethernet.begin(mac, ip, subnet);
  }
  
  // print your local IP address:
  #ifdef DEBUG
  /*Serial.print("My address: ");
  Serial.println(Ethernet.localIP());*/
  #endif
  
  // connect to API server:
  connectToServer();
  
   // run the memory test function and print the results to the serial port
  int result = memoryTest();
  Serial.print("Memory test results: ");
  Serial.print(result,DEC);
  Serial.print(" bytes free");
}



void loop() {
  if (client.connected()) {
    if (client.available()) {
      // read incoming bytes:
      char inChar = client.read();
      
      #ifdef DEBUG
      Serial.print(inChar);
      #endif

      // add incoming byte to end of line:
      currentLine += inChar; 

      // if you get a newline, clear the line:
      if (inChar == '\n') {
       currentLine = "";
      } 
      
      if (currentLine.endsWith("<error/>")) {
        myservo.write(30); 
        dotmatrix.clear();
        printError();
        dotmatrix.sendframe();
        delay(1000);
        // close the connection to the server:
        client.stop();
      }
      
      if (currentLine.endsWith("<time>")) {
        readingTime = true; 
        content = "";
      }

      if (readingTime) {
        if (inChar != '<') {
          if (inChar != '>')
            content += inChar;
        } 
        else {
          readingTime = false;
          time = content;
        }
      }
      
       if ( currentLine.endsWith("<count>")) {
        readingCount = true; 
        content = "";
      }

      if (readingCount) {
        if (inChar != '<') {
          if (inChar != '>')
            content += inChar;
        } 
        else {
          readingCount = false;
          unreadMailsCount = content;
          if(stringToInt(unreadMailsCount) == 0) {
              dotmatrix.clear();
              printTime(); 
              printUnreadMailsCount();
              dotmatrix.sendframe();
              delay(5000);
              // close the connection to the server:
              client.stop();
          }
        }
      }
    
     if (currentLine.endsWith("<mail>")) {
        readingEmails = true; 
        content = "";
      }

      if (readingEmails) {
        if (inChar != '<') {
          if (inChar != '>')
            content += inChar;
        } 
        else {
          readingEmails = false;
          cpt++;
          unreadMails[cpt-1] = content;
          int count = stringToInt(unreadMailsCount);
          if(cpt == NbMails || cpt == count) {
            dotmatrix.clear();
            printTime(); 
            printUnreadMailsCount();
            dotmatrix.sendframe();
            for(int i = 0; i < NbMails && i < count; i++) {
              printMail(i);
            }
            cpt = 0;
            // close the connection to the server:
            client.stop();
          }
        }
     }
    }   
  }
  else {
    // if you're not connected
    // then attempt to connect again:
    connectToServer();
  }
}

void connectToServer()
{
  // attempt to connect:
  #ifdef DEBUG
  Serial.println("Connecting to http:/192.168.25.1/arduino/gmail.php...");
  #endif
  if (client.connect(server, 80))
  {
    #ifdef DEBUG
    Serial.println("Making HTTP request...");
    #endif
    
    // make HTTP GET request to API server:
    client.println("GET /arduino/gmail.php");
    client.println("Host: 192.168.25.1");
    //client.println("User-Agent: Arduino/1.0");
    client.println();
  }
}

void printTime() {
  dotmatrix.putchar(4, 1, time[0], ORANGE);
  dotmatrix.putchar(9, 1, time[1], ORANGE);
  dotmatrix.putchar(14, 1, time[2], ORANGE);
  dotmatrix.putchar(18, 1, time[3], ORANGE);
  dotmatrix.putchar(23, 1, time[4], ORANGE);
}

void printUnreadMailsCount() {
   if(stringToInt(unreadMailsCount) == 0) { 
      myservo.write(30);
   }else{
      myservo.write(110);
   }
   
   byte color = RED;
   int length = unreadMailsCount.length();
   if(length >= 3) {
      dotmatrix.putchar(14, 9, '9', RED);
      dotmatrix.putchar(19, 9, '9', RED);
      dotmatrix.putchar(24, 9, '+', RED);
   }
   else if(length == 2) {
     color = ORANGE;
     dotmatrix.putchar(16, 9, unreadMailsCount[0], RED);
     dotmatrix.putchar(21, 9, unreadMailsCount[1], RED);
   }
   else {
     color = GREEN;
     dotmatrix.putchar(19, 9, unreadMailsCount[0], RED);
   }
   
   dotmatrix.putbitmap(3, 9, emailSprite, 9, 7, color);
}

void printMail(int i) {
  char charBuf[MailLength];
  unreadMails[i].toCharArray(charBuf, MailLength);
  dotmatrix.hscrolltext(9, charBuf,GREEN, 20, 1, LEFT);
}

void printError() {
  dotmatrix.hscrolltext(4, errorStr,RED, 20, 1, LEFT);
}

int stringToInt(String string) {
  char buffer[8];
  string.toCharArray(buffer, string.length()+1);
  return atoi(buffer);
}


//SOURCE:http://www.faludi.com/itp/arduino/Arduino_Available_RAM_Test.pde
// this function will return the number of bytes currently free in RAM
int memoryTest() {
  int byteCounter = 0; // initialize a counter
  byte *byteArray; // create a pointer to a byte array
  // More on pointers here: http://en.wikipedia.org/wiki/Pointer#C_pointers

  // use the malloc function to repeatedly attempt allocating a certain number of bytes to memory
  // More on malloc here: http://en.wikipedia.org/wiki/Malloc
  while ( (byteArray = (byte*) malloc (byteCounter * sizeof(byte))) != NULL ) {
    byteCounter++; // if allocation was successful, then up the count for the next try
    free(byteArray); // free memory after allocating it
  }
  
  free(byteArray); // also free memory after the function finishes
  return byteCounter; // send back the highest number of bytes successfully allocated
}
