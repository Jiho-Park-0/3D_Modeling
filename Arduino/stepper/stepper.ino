#include <Stepper.h>
#include <SoftwareSerial.h>

#define sm1_pin1 2
#define sm1_pin2 3
#define sm1_pin3 4
#define sm1_pin4 5

#define sm2_pin1 6
#define sm2_pin2 7
#define sm2_pin3 8
#define sm2_pin4 9

Stepper stepper1(2048 , sm1_pin4, sm1_pin2, sm1_pin3, sm1_pin1);
Stepper stepper2(2048, sm2_pin4, sm2_pin2, sm2_pin3, sm2_pin1);


void setup() {
  Serial.begin(9600);
}

void loop() {
  Go();
  delay(2000);
}

void Go(){
  stepper1.setSpeed(10);
  stepper2.setSpeed(10);
  stepper1.step(-1);
  stepper2.step(1);;
}

void RightRound(){
  stepper1.setSpeed(10);
  stepper2.setSpeed(10);
  stepper1.step(-1);
  stepper2.step(-1);;
}

void LeftRound(){
  stepper1.setSpeed(10);
  stepper2.setSpeed(10);
  stepper1.step(1);
  stepper2.step(1);;
}
