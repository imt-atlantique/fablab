// DFRobot LCD4884 Graphic LCD shield test
// http://bit.ly/dPTETI
// John Boxall - tronixstuff.com - March 2011 

#include <LCD4884.h>
int z=0;
int dd=200;

void setup()
{
  lcd.LCD_init(); // creates instance of LCD
  lcd.LCD_clear(); // blanks the display
  pinMode(7, OUTPUT);
}

void loop()
{
  // first some text display
  for (int a=0; a<5; a++)
  {
    digitalWrite(7, LOW);
    delay(300);
    digitalWrite(7, HIGH);
    delay(300);
  }
  for (int a=0; a<6; a++)
  {
    lcd.LCD_write_string(0,a,"01234567980123", MENU_NORMAL); // ignore MENU_NORMAL for now
    delay(dd);
  }
  delay(dd);
  lcd.LCD_clear();   // blanks the display
  delay(500);
  lcd.LCD_write_string_big(0, 0, "012345", MENU_NORMAL);
  lcd.LCD_write_string_big(0, 3, "-+-+-+", MENU_NORMAL);
  delay(1000);
  lcd.LCD_clear();
  // now to read the joystick using analogRead(0). Press RESET whien finished
  do
  {
    z=analogRead(0);
    if (z==0)
    {
      lcd.LCD_write_string(2,2,"Down", MENU_NORMAL);      
    } 
    else
      if (z>0 && z<150)
      {
        lcd.LCD_write_string(2,2,"OK   ", MENU_NORMAL);
        delay(dd);        
      } 
      else
        if (z>150 && z<350)
        {
          lcd.LCD_write_string(2,2,"Right", MENU_NORMAL);
          delay(dd);
        } 
        else 
          if (z>350 && z<510)
        {
          lcd.LCD_write_string(2,2,"Up   ", MENU_NORMAL);
          delay(dd);          
        } 
        else
          if (z>510 && z<750)
          {
            lcd.LCD_write_string(2,2,"Left ", MENU_NORMAL);
            delay(dd);
          } 
          else
            if (z>750)
            {
              lcd.LCD_write_string(2,2,"nil  ", MENU_NORMAL);
              delay(dd);
            } 
  }
  while (1>0);
}











