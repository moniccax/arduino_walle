#include <Adafruit_MotorShield.h>

#define BASESPEED 60
#define MAXSPEED 100
#define CURVESPEED 110

class Motor{
  public:
    Adafruit_DCMotor* motor;
    int force;

    Motor(Adafruit_DCMotor* motor);
    void setMode(uint16_t mode);
    void setSpeed(uint16_t force);
	void forward(uint16_t force);
	void stop();
    static void curve(Motor* motor1, Motor* motor2, uint16_t  torque, uint16_t maxTime);
    static void curveForward(Motor* motor1, Motor* motor2, uint16_t  torque, uint16_t maxTime);
};

Motor::Motor(Adafruit_DCMotor* motor){
  this->motor = motor;
  this->force = BASESPEED;
};

void Motor::setMode(uint16_t mode){
  this->motor->run(mode);
};

void Motor::setSpeed(uint16_t force){
  this->force = force;
  this->motor->setSpeed(this->force);
};

void Motor::stop(){
	this->motor->run(RELEASE);
	this->motor->setSpeed(0);	
}

void Motor::forward(uint16_t force){
	this->motor->run(FORWARD);
	this->motor->setSpeed(this->force);
}

void Motor::curve(Motor* motor1, Motor* motor2, uint16_t torque, uint16_t maxTime){
  //motor1->motor->setSpeed(0);
  //motor2->motor->setSpeed(0);
  motor1->setMode(RELEASE);
  motor2->setMode(RELEASE);
  //delay(500);
  motor1->setMode(BACKWARD);
  motor2->setMode(FORWARD);
  motor1->motor->setSpeed(torque);
  motor2->motor->setSpeed(torque);
  delay(maxTime); 
};

void Motor::curveForward(Motor* motor1, Motor* motor2, uint16_t torque, uint16_t maxTime){
  //motor1->motor->setSpeed(0);
  //motor2->motor->setSpeed(0);
  motor1->setMode(RELEASE);
  motor2->setMode(RELEASE);
  //delay(500);
  motor1->setMode(FORWARD);
  motor2->setMode(FORWARD);
  motor1->motor->setSpeed(torque*0.2);
  motor2->motor->setSpeed(torque*1.0);
  delay(maxTime); 
};
