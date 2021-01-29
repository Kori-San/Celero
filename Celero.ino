// Celero by Kori-San //

//Libraries
#if defined(ENERGIA)
#include "Energia.h"
#else 
#error Platform not defined
#endif
#include "SPI.h"
#include "Screen_HX8353E.h"
Screen_HX8353E myScreen;

//All Pins
const int accelerometer_x_pin = 23; // X Axis Pin of the Acceleromemtter
const int accelerometer_y_pin = 24; // Y Axis Pin of the Acceleromemtter
const int red_led_pin= 39; // Red Led's Pin
const int buzzer_pin = 40; // Buzzer's Pin
const int joystick_button = 5; // Joystick's Button Pin
const int joystick_x = 2; // X Axis Pin of the Joystick
const int joystick_y =  26; // Y Axis Pin of the Joystick
const int button_a = 32 ; //Pin of the Bottom Button
const int button_b = 33 ; //Pin of the Top Button

//All var
int x, y, basex, basey, x_forward_var, y_forward_var;
int maniability = 4;
int deaths = 0;
int best_deaths = 0;
long time_var_init, time_var;
long best_time_var = 0;
int menu_choice = 1;
int option_choice = 1;
uint16_t colors[6];
int color_cycle = 0;

//All booleans
boolean resetVar = false;
boolean victory_var = false;
boolean timeUp = false;
boolean gameloop = false;
boolean optionloop = false;
boolean menu_displayVar = false;
boolean gameover_displayVar = false;
boolean bestscore_displayVar = false;
boolean option_displayVar = false;
boolean one_game_done = false;
boolean block_cursor = false;

void beep(int note, int duration)
{
  tone(buzzer_pin, note, duration/2);
  delay(duration/2);
  noTone(buzzer_pin);
  delay(duration/2 + 20);
}

void setup()
{
  //Start Serial communication
  Serial.begin(9600);
  
  //Initialize myScreen
  myScreen.begin();

  //Putting colors in the list
  colors[0] = blackColour;
  colors[1] = redColour;
  colors[2] = orangeColour;
  colors[3] = yellowColour;
  colors[4] = greenColour;
  colors[5] = blueColour;
}

void loop()
{
 if (gameloop == true)
 {
  while (victory_var == false)
  {
   //Print Serial
   Serial.print("accelerometer_x_pin ="); Serial.print(((int) analogRead(accelerometer_x_pin))); Serial.print("\n");
   Serial.print("accelerometer_y_pin ="); Serial.print(((int) analogRead(accelerometer_y_pin))); Serial.print("\n");

   Serial.print("\n");
  
   Serial.print("x = "); Serial.print(x); Serial.print("\n");
   Serial.print("y = "); Serial.print(y); Serial.print("\n");

   Serial.print("\n");
  
   Serial.print("basex = "); Serial.print(basex); Serial.print("\n");
   Serial.print("basey = "); Serial.print(basey); Serial.print("\n");

   Serial.print("\n");
  
   Serial.print("x_forward_var = "); Serial.print(x_forward_var); Serial.print("\n");
   Serial.print("y_forward_var = "); Serial.print(y_forward_var); Serial.print("\n");

   //Death
   if ( x_forward_var < -12 )// If the player touches the left limit
   {
    resetVar = true;
   }
   else if ( y_forward_var < -12 )// If the player touches the top limit
   {
    resetVar = true;
   }
   else if ( x_forward_var > 101 )// If the player touches the right limit
   {
    resetVar = true;
   }
   else if ( y_forward_var > 101 )// If the player touches the bottom limit
   {
    resetVar = true;
   }
   else if ( 7 < x_forward_var && x_forward_var < 22 && -12 < y_forward_var && y_forward_var < 75 )// If the player touches the first obstacle
   {
    resetVar = true;
   }
   else if ( 67 < x_forward_var && x_forward_var < 82 && 7 < y_forward_var && y_forward_var < 101 )// If the player touches the second obstacle
   {
    resetVar = true;
   }
  
   //Victory
   if ( 82 < x_forward_var && x_forward_var < 101 && 92 < y_forward_var && y_forward_var < 101 )//If the player enter the green zone
   {
    victory_var = true;
   }
  
   //Display
   if ( resetVar == true )
   { 
    analogWrite(red_led_pin, 2500);//Led Red ligthen up
    beep(440, 500);//Buzz
    deaths ++;
    myScreen.setPenSolid(true);
    myScreen.dRectangle(0, 0, 128, 128, whiteColour);//Background
    myScreen.setPenSolid(false);
    myScreen.dRectangle(0, 0, 128, 128, blackColour);//first layer that help to higher the screen limit
    myScreen.dRectangle(1, 1, 127, 127, blackColour);//second layer that help to higher the screen limit
    myScreen.dRectangle(32, 0, 5, 90, blackColour);//first obstacle
    myScreen.dRectangle(92, 32, 5, 105, blackColour);//second obstacle
    
    basex = ((int)analogRead(accelerometer_x_pin)-2048)/maniability;
    basey = -((int)analogRead(accelerometer_y_pin)-2048)/maniability; 
    
    x = ((int)analogRead(accelerometer_x_pin)-2048)/maniability;
    y = -((int)analogRead(accelerometer_y_pin)-2048)/maniability;
    
    x_forward_var = x - basex;
    y_forward_var = y - basey;
  
    myScreen.setPenSolid(true);
    myScreen.dRectangle(97, 107, 30, 20, greenColour);//Victory Zone
    myScreen.dRectangle(15+x_forward_var, 15+y_forward_var, 10, 10, colors[color_cycle]);//Player's Square
    
    analogWrite(red_led_pin, 0);//Red Led get off
    resetVar = false;
    }
   else if ( resetVar == false )
   {
    x_forward_var = x - basex;
    y_forward_var = y - basey;
    
    myScreen.setPenSolid(true);
    myScreen.dRectangle(15+x_forward_var, 15+y_forward_var, 10, 10, whiteColour);//White square to erase player's position and prevent screen flashing
    
    x = ((int)analogRead(accelerometer_x_pin)-2048)/maniability;
    y = -((int)analogRead(accelerometer_y_pin)-2048)/maniability;
    
    x_forward_var = x - basex;
    y_forward_var = y - basey;
      
    myScreen.setPenSolid(true);
    myScreen.dRectangle(97, 107, 30, 20, greenColour);
    myScreen.dRectangle(15+x_forward_var, 15+y_forward_var, 10, 10, colors[color_cycle]);
   }
  }
  if (timeUp == false)
  {
   time_var=millis();
   time_var=time_var-time_var_init;
   timeUp = true;
  }
  if (gameover_displayVar == false)
  {
   myScreen.setPenSolid(true);
   myScreen.dRectangle(0, 0, 128, 128, blackColour); //Background
   myScreen.setFontSize(1);
   myScreen.gText(28, 6,"Victory !",greenColour);
   myScreen.setFontSize(0);
   myScreen.gText(38, 28,"Deaths : "+i32toa((int)deaths,1,0,0),redColour);
   myScreen.gText(22, 40,"Time : "+i32toa((long)time_var,1,0,0)+" ms",blueColour);
   if (one_game_done == false) {best_time_var = time_var;}
   else if (best_time_var > time_var) {best_time_var = time_var;}
   if (one_game_done == false) {best_deaths = deaths;}
   else if (best_deaths > deaths) {best_deaths = deaths;}
   one_game_done = true;
   gameover_displayVar = true;
  }
  myScreen.gText(24, 80,"Press a button",whiteColour);
  myScreen.gText(32, 92,"to continue",whiteColour);
  if (!digitalRead(joystick_button) || !digitalRead(button_a) || !digitalRead(button_b))
  {
  menu_displayVar = false;
  gameover_displayVar = false;
  timeUp = false;
  victory_var = false;
  block_cursor = false;
  gameloop = false;
  }
 }
 else if (gameloop == false)
 {
  delay(150);
  if (menu_displayVar == false)
  {
   myScreen.setPenSolid(true);
   myScreen.dRectangle(0, 0, 128, 128, blackColour);
   myScreen.setFontSize(1);
   myScreen.gText(40, 6,"Celero",yellowColour);
   myScreen.setFontSize(0);
   myScreen.gText(48, 38,"Begin",whiteColour);
   myScreen.gText(43, 68,"Options",whiteColour);
   myScreen.gText(45, 98,"Scores",whiteColour);
   menu_displayVar = true;
  }
  if (block_cursor == false)
  {
   switch (menu_choice)
   {
    case 1 :
      myScreen.dRectangle(25, 34, 5, 15, whiteColour);
      myScreen.dRectangle(25, 64, 5, 15, blackColour);
      myScreen.dRectangle(25, 94, 5, 15, blackColour);
      break;
    case 2 :
      myScreen.dRectangle(25, 34, 5, 15, blackColour);
      myScreen.dRectangle(25, 64, 5, 15, whiteColour);
      myScreen.dRectangle(25, 94, 5, 15, blackColour);
      break;
    case 3 :
      myScreen.dRectangle(25, 34, 5, 15, blackColour);
      myScreen.dRectangle(25, 64, 5, 15, blackColour);
      myScreen.dRectangle(25, 94, 5, 15, whiteColour);
      break;
   }
   if (analogRead(joystick_y)<1000)
   {
    if (menu_choice == 3) {menu_choice = 1;}
    else { menu_choice ++; }
   }
   else if (analogRead(joystick_y)>3000)
   {
    if (menu_choice == 1) {menu_choice = 3;}
    else { menu_choice --; }
   }
  }
  
  if (!digitalRead(joystick_button) || !digitalRead(button_a) || !digitalRead(button_b))
  {
   block_cursor = true;
   switch (menu_choice)
   {
    case 1:
      //init screen
      myScreen.setPenSolid(true);
      myScreen.dRectangle(0, 0, 128, 128, whiteColour);
      myScreen.setPenSolid(false);
      myScreen.dRectangle(0, 0, 128, 128, blackColour);
      myScreen.dRectangle(1, 1, 127, 127, blackColour);
      myScreen.dRectangle(32, 0, 5, 90, blackColour);
      myScreen.dRectangle(92, 32, 5, 105, blackColour);
      
      //init var
      basex = ((int)analogRead(accelerometer_x_pin)-2048)/maniability;
      basey = -((int)analogRead(accelerometer_y_pin)-2048)/maniability;
      x = ((int)analogRead(accelerometer_x_pin)-2048)/maniability;
      y = -((int)analogRead(accelerometer_y_pin)-2048)/maniability;
      x_forward_var = x - basex;
      y_forward_var = y - basey;
      deaths = 0;
      time_var_init = millis();
      gameloop = true;
      break;
      
    case 2: 
      if (menu_choice == 2)
      {
       optionloop = true;
       while (optionloop == true)
       {
        delay(100);
        if (option_displayVar == false)
        {
         myScreen.setPenSolid(true);
         myScreen.dRectangle(0, 0, 128, 128, blackColour);
         myScreen.setFontSize(1);
         myScreen.gText(38, 6,"Options",whiteColour);
         myScreen.setFontSize(0);
         myScreen.gText(20, 30,"Maniability",whiteColour);
         myScreen.gText(20, 60,"Colors",whiteColour);
         myScreen.gText(20, 90,"Quit",whiteColour);
         option_displayVar = true;
        }
        myScreen.gText(90, 30,"< "+i32toa((int)maniability,1,0,0)+" >",whiteColour);
        myScreen.gText(65, 60,"<     >",whiteColour);
        myScreen.dRectangle(76, 54, 20, 20, whiteColour);
        myScreen.dRectangle(81, 59, 10, 10, colors[color_cycle]);
        switch (option_choice)
        {
         case 1 :
           myScreen.dRectangle(12, 26, 5, 15, whiteColour);
           myScreen.dRectangle(12, 56, 5, 15, blackColour);
           myScreen.dRectangle(12, 86, 5, 15, blackColour);
           break;
         case 2 :
           myScreen.dRectangle(12, 26, 5, 15, blackColour);
           myScreen.dRectangle(12, 56, 5, 15, whiteColour);
           myScreen.dRectangle(12, 86, 5, 15, blackColour);
           break;
         case 3 :
           myScreen.dRectangle(12, 26, 5, 15, blackColour);
           myScreen.dRectangle(12, 56, 5, 15, blackColour);
           myScreen.dRectangle(12, 86, 5, 15, whiteColour);
           break;
        }
       
        if (analogRead(joystick_y)<1000)
        {
         if (option_choice == 3) {option_choice = 1;}
         else { option_choice ++; }
        }
        else if (analogRead(joystick_y)>3000)
        {
         if (option_choice == 1) {option_choice = 3;}
         else { option_choice --; }
        }

        if (option_choice == 1)
        {
         if (analogRead(joystick_x)<1000)
         {
          if (maniability == 1) {maniability = 1;}
          else { maniability --; }
         }
         else if (analogRead(joystick_x)>3000)
         {
          if (maniability == 7) {maniability = 7;}
          else { maniability ++; }
         }
        }

        if (option_choice == 2)
        {
         if (analogRead(joystick_x)<1000)
         {
          if (color_cycle == 0) {color_cycle = 0;}
          else { color_cycle --; }
         }
         else if (analogRead(joystick_x)>3000)
         {
          if (color_cycle == 5) {color_cycle = 5;}
          else { color_cycle ++; }
         }
        }
        
        if (!digitalRead(joystick_button) || !digitalRead(button_a) || !digitalRead(button_b))
        {
         if (option_choice == 3)
         { 
          menu_displayVar = false;
          option_displayVar = false;
          block_cursor = false;
          optionloop = false;
         }
        }
       }
       break;
      }
    case 3:
      if (menu_choice == 3)
      {
       if (bestscore_displayVar == false)
       {
        myScreen.setPenSolid(true);
        myScreen.dRectangle(0, 0, 128, 128, blackColour);
        myScreen.setFontSize(1);
        myScreen.gText(14, 6,"BEST SCORES !",yellowColour);
        myScreen.setFontSize(0);
        if (one_game_done == false)
        {
         myScreen.gText(26, 28,"Deaths : NONE",yellowColour);
         myScreen.gText(32, 40,"Time : NONE",yellowColour);
        }
        else
        { 
         myScreen.gText(32, 28,"Deaths : "+i32toa((int)best_deaths,1,0,0),yellowColour);
         myScreen.gText(22, 40,"Time : "+i32toa((long)best_time_var,1,0,0)+" ms",yellowColour);
        }
        myScreen.gText(24, 90,"Press a button",whiteColour);
        myScreen.gText(32, 102,"to continue",whiteColour);
        bestscore_displayVar = true;
       }
      
       if (!digitalRead(joystick_button) || !digitalRead(button_a) || !digitalRead(button_b))
       {
        menu_displayVar = false;
        bestscore_displayVar = false;
        block_cursor = false;
        break;
       }
      }
   }
  }
 }
}
