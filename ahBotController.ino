#include <Servo.h>
Servo servo1,servo2;
long num;
int state = 0;  
#define E1 10  // Enable Pin for motor 1
#define E2 11  // Enable Pin for motor 2
 
#define I1 34  // Control pin 1 for motor 1
#define I2 35  // Control pin 2 for motor 1
#define I3 40  // Control pin 1 for motor 2
#define I4 41  // Control pin 2 for motor 2
#define ID 13  // Control pin 2 for motor 2
#define pingTrig 9
#define pingEch 8

long duration;
int distance;

void setup() {
    pinMode(E1, OUTPUT);
    pinMode(E2, OUTPUT);
    pinMode(I1, OUTPUT);
    pinMode(I2, OUTPUT);
    pinMode(I3, OUTPUT);
    pinMode(I4, OUTPUT);
    pinMode(ID, OUTPUT);
    pinMode(pingTrig, OUTPUT); 
    pinMode(pingEch, INPUT);
    Serial.begin(9600); 
    servo1.attach(2);
    servo2.attach(5);

}
long modDiff(long a, long b){
  long d = (a-b);
  return (d<0)?(-1*d):d;
}
long getDist(){
  //regression
  int k = 2;
  long stackd[3];
  while(k>=0){
  digitalWrite(pingTrig, LOW);
  delayMicroseconds(2);
  
  digitalWrite(pingTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingTrig, LOW);

  duration = pulseIn(pingEch, HIGH);
  distance= duration*0.034/2;
  stackd[k] = distance;  
  k--;
  }

  if(modDiff(stackd[0],(stackd[1]+stackd[2])/2)>100)
    return (stackd[1]+stackd[2])/2;
  else if(modDiff(stackd[1],(stackd[0]+stackd[2])/2)>100)
    return (stackd[0]+stackd[2])/2;
  else if(modDiff(stackd[2],(stackd[0]+stackd[1])/2)>100)
    return (stackd[0]+stackd[1])/2;
  else
    return (stackd[0]+stackd[1]+stackd[2])/3;
}
void moveFwd(){
    digitalWrite(I1, HIGH);
    digitalWrite(I2, LOW);
    digitalWrite(I3, HIGH);
    digitalWrite(I4, LOW);
    digitalWrite(ID, HIGH);
}
void moveBck(){
    digitalWrite(I1, LOW);
    digitalWrite(I2, HIGH);
    digitalWrite(I3, LOW);
    digitalWrite(I4, HIGH);
}
void moveClk(){
    digitalWrite(I1, LOW);
    digitalWrite(I2, HIGH);
    digitalWrite(I3, HIGH);
    digitalWrite(I4, LOW);
}
void loop() {
  //0 = clockwise
  //1 = forward motion
  //2 = stop
  //3 = main servo low
  //4 = main servo high
  //5 = claw hold
  //6 = claw release
 // if (state != 2)
 while(Serial.available()>0){ 
   state = Serial.parseInt();     //input from raspi
   Serial.print(state); 
 }
 switch(state){
  case 0:
    moveClk();
    break;
  case 1:
    moveClk();break;
  case 2:
    moveClk();break;
  
  }
 
}
