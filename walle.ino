#include <Adafruit_MotorShield.h>
#include <LiquidCrystal.h>  
  
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);  
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *mY = AFMS.getMotor(3);
Adafruit_DCMotor *mX = AFMS.getMotor(2);
boolean loopLock;

#define MAXSPEED 65535

class Movement{
  public:
    Adafruit_DCMotor* motor;
    uint16_t force;
    uint8_t mode;
    int delaytime;

    Movement(Adafruit_DCMotor* motor, uint16_t force, uint8_t mode, int delaytime);
    void execute(void);
};

Movement::Movement(Adafruit_DCMotor* motor, uint16_t force, uint8_t mode, int delaytime){
  this->motor = motor;
  this->force = force;
  this->mode = mode;
  this->delaytime = delaytime;
};

void Movement::execute(void){
  this->motor->setSpeed(this->force);
  this->motor->run(this->mode);
  delay(this->delaytime);
};

void ledPrint(int x, int y, char message[]){
    lcd.setCursor(x,y);
    lcd.print(message);
}

void printUfmg(){
 Movement(mY, 65, BACKWARD, 160).execute(); // U 1 (baixo)
 Movement(mY, 0, RELEASE, 1000).execute();
 
 Movement(mX, 65, FORWARD  , 220).execute(); // U 2 (direita)
 Movement(mX, 0, RELEASE, 1000).execute();

 Movement(mY, 65, FORWARD, 170).execute(); // U 3 (cima)
 Movement(mY, 0, RELEASE, 1000).execute();

 Movement(mX, 65, FORWARD  , 300).execute();// U -> F
 Movement(mX, 0, RELEASE, 1000).execute();

 Movement(mX, 65, BACKWARD  , 200).execute(); // F 1 (esquerda)
 Movement(mX, 0, RELEASE, 1000).execute();

 Movement(mY, 65, BACKWARD, 75).execute(); // F 2 (baixo)
 Movement(mY, 0, RELEASE, 1000).execute();

 Movement(mX, 65, FORWARD  , 200).execute();// F 3 (direita)
 Movement(mX, 0, RELEASE, 1000).execute();
 
 Movement(mX, 65, BACKWARD  , 150).execute();//F 4 (esquerda)
 Movement(mX, 0, RELEASE, 1000).execute();

 Movement(mY, 65, BACKWARD, 115).execute(); // F 5 (baixo)
 Movement(mY, 0, RELEASE, 1000).execute();

 Movement(mY, 65, FORWARD, 190).execute(); // F 6 (cima)
 Movement(mY, 0, RELEASE, 1000).execute();

 Movement(mX, 65, FORWARD  , 300).execute(); // F -> M
 Movement(mX, 0, RELEASE, 1000).execute();

 Movement(mY, 65, BACKWARD, 180).execute(); // M 1 (baixo)
 Movement(mY, 0, RELEASE, 1000).execute();

 Movement(mY, 65, FORWARD, 180).execute(); // M 2 (cima)
 Movement(mY, 0, RELEASE, 1000).execute();

 Movement(mY, 60, BACKWARD, 0).execute(); // M 3 (baixo)
 Movement(mX, 65, FORWARD  , 160).execute();// (direita)

 Movement(mY, 0, RELEASE, 0).execute(); // Parar
 Movement(mX, 0, RELEASE, 1000).execute();//

 Movement(mY, 60, FORWARD, 0).execute(); // M 4 (baixo)
 Movement(mX, 65, FORWARD, 160).execute();// (direita)

 Movement(mY, 0, RELEASE, 0).execute(); // Parar
 Movement(mX, 0, RELEASE, 1000).execute();//

 Movement(mY, 65, BACKWARD, 160).execute(); // M 5 (baixo)
 Movement(mY, 0, RELEASE, 1000).execute(); 

 Movement(mY, 65, FORWARD, 160).execute(); // M 6 (cima)
 Movement(mY, 0, RELEASE, 1000).execute(); 

 Movement(mX, 65, FORWARD  , 300).execute();// M -> G
 Movement(mX, 0, RELEASE, 1000).execute();

 Movement(mX, 65, BACKWARD  , 170).execute(); // G 1 (esquerda)
 Movement(mX, 0, RELEASE, 1000).execute();

 Movement(mY, 65, BACKWARD, 190).execute(); // G 2 (baixo)
 Movement(mY, 0, RELEASE, 1000).execute();

 Movement(mX, 65, FORWARD  , 220).execute();// G 3 (direita)
 Movement(mX, 0, RELEASE, 1000).execute();

 Movement(mY, 65, FORWARD, 80).execute(); // G 4 (cima)
 Movement(mY, 0, RELEASE, 1000).execute();

 Movement(mX, 55, BACKWARD, 110).execute();// G 5 (esquerda)
 Movement(mX, 0, RELEASE, 1000).execute();
}

void setup()
{
  AFMS.begin(); // create with the default frequency 1.6KHz
  lcd.begin(16, 2);
  ledPrint(0,0, "Destroyer v1.0"); 
  ledPrint(0,1, "ufmg");
  loopLock = false;
}

void loop()
{
  if(!loopLock){
    ledPrint(5,1, "(EXEC)");
    printUfmg();
    loopLock = true;
    ledPrint(5,1, "(FIM) ");
  }
  delay(1000);
}
