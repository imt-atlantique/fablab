
#include <TVout.h>
#include <fontALL.h>
#include <i2cmaster.h>
#include <nunchuck.h>
#include <VideoGameHelper.h>

#define NBR 4

Nunchuck p1; //Joystick player 1
TVout TV; //sortie tv
int V=96, H1=120, H; //dimensions de l'écran
int STATE=1; //état
int score=0;
int j=0; 


PROGMEM const unsigned char bonhomme[] = {
  8,16,
  0x30, 0x78, 0x78, 0x30,
  0x78, 0xB5, 0xB2, 0xB0, 0x30,
  0x48, 0x44, 0x42, 0x84, 0x88, 0x8C, 0xC0,
};

PROGMEM const unsigned char noir[] = {
  8,16,
  0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0,
};

int px, py; //position du personnage
int posfix; //abcisse par défaut
int obstaclesx[8]={
 H1+0,  
 H1+20, 
 H1+40, 
 H1+60, 
 H1+80, 
 H1+100,
 H1+120,
 H1+140,
}; 

int obstaclesy[8]={
45, 
 21,
 21,
  45,
 21,
 45,
 40,
 96,
}; 

int current; //indice de l'obstacle courant
int vitesse;
int indice;

void setup() {
  TV.begin(NTSC, 96,96); //initialisation de la tv
  Serial.begin(9600);
  V=TV.vres(); H=TV.hres();
  p1.begin(NUNCHUCK_PLAYER_1); //initialisation du nunchuck
  TV.select_font(font4x6); //choix de la taille de police

  TV.delay_frame(1); //vitesse de défilement des images
  draw_welcome();

  initialisation();
  TV.bitmap(px, py, bonhomme);
    
}

void loop(){
  TV.draw_rect(0, 0, H-1, V-1, 1);
  TV.draw_rect(0, 0, H-1, 20, 1);
  TV.draw_rect(0, V-10, H-1, 10, 1);
  TV.set_cursor(30, 10);
  TV.printPGM(PSTR("Score "));  
  p1.update();
  STATE=1;
  for(int i=0; i<NBR; i++){
          TV.delay(0);
          p1.update();
          if(p1.joy_up()){
            if(py>21) {
              TV.bitmap(px, py, noir);
              py--;
            }
          }
          if(p1.joy_down()){
            if((py+16)<V-10){
              TV.bitmap(px, py, noir);
              py++;
            }
          }
          indice = recherche(posfix + 8);
          //Serial.println(indice);
          //Serial.print("py = "); Serial.println(py);
          
          /*
          if(indice >= 0 && ((py > obstaclesy[indice] && py < (obstaclesy[indice]+30) ) || ((py + 16) > obstaclesy[indice] && (py+16) < (obstaclesy[indice]+30))))
          {
            Serial.print("obstaclex ind : "); Serial.println(obstaclesx[indice]);
            Serial.print("obstacley ind : "); Serial.println(obstaclesy[indice]);
            TV.clear_screen();
            TV.delay(1000);
            STATE=2 ;//perdu
            for(int i=0; i < 8; i++){
              obstaclesx[i] = H1 + i*20;
            }
            TV.clear_screen();
            break;
          }*/
           /*if(obstaclesx[j%8]==posfix+8 && ((py > obstaclesy[j%8] && py < (obstaclesy[j%8]+30) ) || ((py + 16) > obstaclesy[j%8] && (py+16) < (obstaclesy[j%8]+30))))
          {
            //Serial.print("obstaclex ind : "); Serial.println(obstaclesx[j%8]);
            //Serial.print("obstacley ind : "); Serial.println(obstaclesy[j%8]);
            TV.clear_screen();
            TV.delay(1000);
            STATE=2 ;//perdu
            for(int i=0; i < 8; i++){
              obstaclesx[i] = H1 + i*20;
            }
            TV.clear_screen();
            //j++;
            //j=0;
          }*/
          //j++;
          
          TV.bitmap(px, py, bonhomme);
          //if(obstacle[0][i] == 
          TV.draw_rect(obstaclesx[i], obstaclesy[i], 3, 40, BLACK, BLACK);
          obstaclesx[i]--;
          //Serial.println(obstaclesx[i]);
          TV.draw_rect(obstaclesx[i], obstaclesy[i], 3, 40, WHITE, WHITE);
          //TV.delay(5);
     
     }
     /*if(indice >= 0 && ((py > obstaclesy[indice] && py < (obstaclesy[indice]+30) ) || ((py + 16) > obstaclesy[indice] && (py+16) < (obstaclesy[indice]+30))))
          {
            Serial.print("obstaclex ind : "); Serial.println(obstaclesx[indice]);
            Serial.print("obstacley ind : "); Serial.println(obstaclesy[indice]);
            TV.clear_screen();
            TV.delay(1000);
            STATE=2 ;//perdu
            for(int i=0; i < 8; i++){
              obstaclesx[i] = H1 + i*20;
            }
            TV.clear_screen();
            //break;
          }*/
       j++;
       if(j==10 && ((py > obstaclesy[0] && py < obstaclesy[0]+40)  || (py + 16 > obstaclesy[0] && py+16 < obstaclesy[0]+40))){
         TV.clear_screen();
            TV.delay(1000);
            STATE=2 ;//perdu
            for(int i=0; i < 8; i++){
              obstaclesx[i] = H1 + i*20;
            }
            TV.clear_screen();
            j=0;
       }
       if(j==27 && ((py > obstaclesy[1] && py < obstaclesy[1]+40)  || (py + 16 > obstaclesy[1] && py+16 < obstaclesy[1]+40))){
         TV.clear_screen();
            TV.delay(1000);
            STATE=2 ;//perdu
            for(int i=0; i < 8; i++){
              obstaclesx[i] = H1 + i*20;
            }
            TV.clear_screen();
            j=0;
       }
       if(j==47 && ((py > obstaclesy[2] && py < obstaclesy[2]+40)  || (py + 16 > obstaclesy[2] && py+16 < obstaclesy[2]+40))){
         TV.clear_screen();
            TV.delay(1000);
            STATE=2 ;//perdu
            for(int i=0; i < 8; i++){
              obstaclesx[i] = H1 + i*20;
            
            TV.clear_screen();
            j = 0;
            }
       }
       
       
       if(j==67 && ((py > obstaclesy[3] && py < obstaclesy[3]+40)  || (py + 16 > obstaclesy[3] && py+16 < obstaclesy[3]+40))){
         TV.clear_screen();
            TV.delay(1000);
            STATE=2 ;//perdu
            for(int i=0; i < 8; i++){
              obstaclesx[i] = H1 + i*20;
            
            TV.clear_screen();
            j = 0;
            }
       }
       
       /*if(j==87 && ((py > obstaclesy[4] && py < obstaclesy[4]+40)  || (py + 16 > obstaclesy[4] && py+16 < obstaclesy[4]+40))){
         Serial.print("py");  Serial.println(obstaclesy[4]);
         TV.clear_screen();
            TV.delay(1000);
            STATE=2 ;//perdu
            for(int i=0; i < 8; i++){
              obstaclesx[i] = H1 + i*20;
            
            TV.clear_screen();
            j = 0;
            }
       }*/
       
       if(j==107 && ((py > obstaclesy[4] && py < obstaclesy[4]+40)  || (py + 16 > obstaclesy[4] && py+16 < obstaclesy[4]+40))){
         Serial.print("py");  Serial.println(obstaclesy[4]);
         TV.clear_screen();
            TV.delay(1000);
            STATE=2 ;//perdu
            for(int i=0; i < 8; i++){
              obstaclesx[i] = H1 + i*20;
            
            TV.clear_screen();
            j = 0;
            }
       }
       
       if(j==127 && ((py > obstaclesy[4] && py < obstaclesy[4]+40)  || (py + 16 > obstaclesy[4] && py+16 < obstaclesy[4]+40))){
         Serial.print("py");  Serial.println(obstaclesy[4]);
         TV.clear_screen();
            TV.delay(1000);
            STATE=2 ;//perdu
            for(int i=0; i < 8; i++){
              obstaclesx[i] = H1 + i*20;
            
            TV.clear_screen();
            j = 0;
            }
       }
       
       /*if(j==30 && ((py > obstaclesy[1] && py < obstaclesy[1]+30)  || (py + 16 > obstaclesy[1] && py+16 < obstaclesy[1]+30)))
       else if (j==30 && (py > obstaclesy[1] && (py < (obstaclesy[1]+30)) ) || ((py + 16) > obstaclesy[1] )&& (py+16) < (obstaclesy[1]+30)))){
         TV.clear_screen();
            TV.delay(1000);
            STATE=2 ;//perdu
            for(int i=0; i < 8; i++){
              obstaclesx[i] = H1 + i*20;
            }
            TV.clear_screen();
       }*/
     score+=1;
 //if(score < 70 || score > 100) { 
      TV.draw_rect(41, 16, 20, 6, 0,0);
      TV.set_cursor(54, 10);
      TV.print(score);
  if(STATE==2){
    TV.clear_screen();
    TV.draw_rect(0, 0, H-1, V-1, 1);
  TV.draw_rect(0, 0, H-1, 20, 1);
  TV.draw_rect(0, V-10, H-1, 10, 1);  
         TV.set_cursor(TV.hres()/2-40, TV.vres()/2);
          TV.print("PERDU !!!  score "); TV.print(score);
          TV.delay(7000);
          STATE=1;
          score=0;
          TV.clear_screen();
          px=10; py=22;
  //}
  
  //switch (STATE) {
    
    /*case 1:
      
          break;
      
      /* case 2:
          
          break;*/
      
    //}
  }
  
  //animation();
}

void draw_welcome(){


  TV.draw_rect(0, 0, H-1, V-1,WHITE);
  TV.draw_rect(H/2-30, V/2-10, 60, 20,WHITE);
  TV.set_cursor(H/2-13, V/2-2);
  TV.printPGM(PSTR("PLAYTV"));
  TV.delay(1000);
  TV.set_cursor(H/2-18, V/2+15);
  TV.printPGM(PSTR("loading..."));
  TV.draw_rect(H/2-25, V/2+25, 50, 5,WHITE);
  for(int i=0; i<50; i++){
    TV.draw_rect(H/2-25, V/2+25, i, 5,WHITE, WHITE);
    TV.delay(100);
  }
  TV.delay(100);
  
  TV.draw_rect(H/2-30, V/2+12, 60, 30,BLACK, BLACK);
  TV.set_cursor(H/2-35, V/2+20);
  title_screen_init_nunchucks(&TV, "Play TV", &p1, NULL, false);

  STATE=1; //état start
  TV.clear_screen();
}



void initialisation(){
  posfix=30; px=10; py=22;
  current = 0;
  score=vitesse=1;
}

int recherche(int ax){
  int ind=-1;
  for(int j=0; j<8; j++){
    if(obstaclesx[j]==ax){
      ind=j;
      break;
    }
  }
  return ind;
}

   
  



