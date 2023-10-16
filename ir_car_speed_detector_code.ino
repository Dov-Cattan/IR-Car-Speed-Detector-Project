/*Code was made for Arduino by https://github.com/embeddedlab786 
and then edited by me to be used for the ESP32 MCU and TCRT5000 IR Sensor*/
#include <LiquidCrystal.h>
 
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(19, 23, 18, 17, 16, 15);

int clock1;
int clock2;

float Time;

int flag1 = 0;
int flag2 = 0;

float distance = 5.0;
float speed;

int ir1 = 4;
int ir2 = 0;

int buzzer = 5;

void setup(){
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(buzzer, OUTPUT);
  
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" IR Car Speed");
  lcd.setCursor(0,1);
  lcd.print("   Detector");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("By: Dov Cattan");
  delay(2000);
  lcd.clear();
}

void loop() {
if(digitalRead (ir1) == LOW && flag1==0){clock1 = millis(); flag1=1;}

if(digitalRead (ir2) == LOW && flag2==0){clock2 = millis(); flag2=1;}

if (flag1==1 && flag2==1){
     if(clock1 > clock2){Time = clock1 - clock2;}
else if(clock2 > clock1){Time = clock2 - clock1;}
 Time=Time/1000;//convert milliseconds to seconds
 speed=(distance/Time);//v=d/t
 speed=speed*3600;//multiply by seconds per hr
 speed=speed/1000;//division by meters per Km
 speed=speed*0.6213711922;// multiply to get miles per hour
}

if(speed==0){ 
lcd.setCursor(0, 1); 
if(flag1==0 && flag2==0){lcd.print("No car  detected");}
                    else{lcd.print("Searching...    ");} 
}
else{
    lcd.clear(); 
    lcd.setCursor(0, 0); 
    lcd.print("Speed:");
    lcd.print(speed,1);
    lcd.print("MPH");
    lcd.setCursor(0, 1); 
  if(speed > 50){lcd.print("  Over Speeding  "); digitalWrite(buzzer, HIGH);}
            else{lcd.print("  Normal Speed   "); }    
    delay(3000);
    digitalWrite(buzzer, LOW);
    speed = 0;
    flag1 = 0;
    flag2 = 0;    
 }
}
