#include <Servo.h>    
Servo myservo;      

void setup() {
  myservo.attach(9);
}

void loop() {
  myservo.write(-10);
  delay(1000);
  
  myservo.write(0);
  delay(1000);

  myservo.write(10);
  delay(1000);

  myservo.write(170);
  delay(1000);

  myservo.write(180);
  delay(1000);
  
  myservo.write(190);
  delay(1000);
  
}


