#include <stdlib.h>
#include <LiquidCrystal.h>
#include "./Motor.hpp"

#define SENSORLEFT 11
#define SENSORRIGHT 15
#define SENSORFRONT 13
#define SENSORBACK 12
#define STARTLIGHT 8

Motor* left;
Motor* right;
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void ledPrint(LiquidCrystal lcd, int x, int y, const char * message) {
  lcd.setCursor(x, y);
  lcd.print((String(message) + "                ").c_str());
}

boolean started;

void setup()   
{  
  started = false;
  lcd.begin(16, 2);
  Serial.begin(9600);
  AFMS.begin();
  left = new Motor(AFMS.getMotor(1));
  right = new Motor(AFMS.getMotor(2));
  left->stop();
  right->stop();
}  

// ===========================================================================================================================================================

int leftSpeed;
int rightSpeed;
int reset = 0;

boolean isBlack(int value){
  return value <= 350;
}

void followBlackLine(){
  if(reset){
    reset = false;
  }
  Serial.println(String("Esquerda :: ") + analogRead(SENSORLEFT));
  Serial.println(String("Direita :: ") + analogRead(SENSORRIGHT));
  if(isBlack(analogRead(SENSORLEFT))){
    Motor::curveForward(left, right, BASESPEED, 40);
  }else if(isBlack(analogRead(SENSORRIGHT))){
    Motor::curveForward(right, left, BASESPEED, 40);
  }else{
    // RETA
  }
  
}

// ===========================================================================================================================================================

int findLight(){
  int found = false;
  int timeLapse = 0;
  int back;
  int front;
  int now;
  int old;
  right->setMode(FORWARD);
  left->setMode(BACKWARD);
  right->motor->setSpeed(CURVESPEED - 50);
  left->motor->setSpeed(CURVESPEED - 50);
  while(!found){
    ledPrint(lcd, 0, 0, (String("BL") + String(analogRead(SENSORFRONT)) + " : " + String(analogRead(SENSORBACK))).c_str());
    ledPrint(lcd, 0, 1, (String("SL") + String(analogRead(STARTLIGHT)) + " L " + String(analogRead(SENSORLEFT)) +  " R " + String(analogRead(SENSORRIGHT))).c_str());
    back = analogRead(SENSORBACK);
    front = analogRead(SENSORFRONT);
    now = abs(back - front);
    if(now > 250 && now > old){
      found = true;
      ledPrint(lcd, 0, 1, "Go!");
      break;
    }
    old = now;
    delay(150);
    timeLapse += 150;
  }
  left->stop();
  right->stop();
  return timeLapse;
}

int maxOfArray(int* arr, int length){
  int max = -4096;
  for(int i = 0; i < length; i++){
    if(arr[i] >= max){
      max = arr[i];
    }
  }
  return max;
}

// ===========================================================================================================================================================

boolean start(){
  return started || analogRead(STARTLIGHT) > 300;
}

void shutdown(){
  while(1){
    left->setSpeed(0);
    right->setSpeed(0);
    left->setMode(RELEASE);
    right->setMode(RELEASE);
    delay(10000);
    
  }
}

void circuit(){
  int timer = findLight();
  while(timer < 60000){
      left->forward(BASESPEED);
      right->forward(BASESPEED);
      followBlackLine();
      delay(50);
      timer += 50;
      ledPrint(lcd, 0, 0, String(timer).c_str());
  }
  shutdown();
}

// ===========================================================================================================================================================

void loop(){
  if(start()){
    started = true; //verifica se acendeu a luz
    circuit();
  }
  delay(100);
}
