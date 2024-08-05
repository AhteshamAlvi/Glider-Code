#include <Servo.h>    
Servo servo1;  
Servo servo2;  
Servo servo3;  
Servo servo4;  

const int ch1Pin = 2;
const int ch2Pin = 3;
const int ch3Pin = 4;
const int ch4Pin = 5;
const int ch5Pin = 6;

/*
const int servo1 = 8;
const int servo1 = 9;
const int servo1 = 10;
const int servo1 = 11;
*/

const int servoRange = 180;

void setup() {
  Serial.begin(9600);
  
  pinMode(ch1Pin, INPUT);
  pinMode(ch2Pin, INPUT);
  pinMode(ch3Pin, INPUT);
  pinMode(ch4Pin, INPUT);
  pinMode(ch5Pin, INPUT);

  servo1.attach(8);
  servo2.attach(9);
  servo3.attach(10);
  servo4.attach(11);
}

void loop() {
  // Read the pulse width for each channel
  unsigned long ch1Val = pulseIn(ch1Pin, HIGH);
  unsigned long ch2Val = pulseIn(ch2Pin, HIGH);
  unsigned long ch3Val = pulseIn(ch3Pin, HIGH);
  unsigned long ch4Val = pulseIn(ch4Pin, HIGH);
  unsigned long ch5Val = pulseIn(ch5Pin, HIGH);

  servo1.write(upDownPercent(1084, 1893, ch2Val) * servoRange);
  servo2.write(leftRightPercent(1844, 1039, ch3Val) * servoRange);
  servo3.write(upDownPercent(1207, 2000, ch4Val) * servoRange);
  servo4.write(leftRightPercent(1950, 1144, ch5Val) * servoRange);
/*
  Serial.print("Channel: ");
  Serial.print(ch2Pin);
  Serial.print(", Current: ");
  Serial.print(ch2Val);
  Serial.print(", Value: ");
  Serial.println(upDownPercent(1084, 1893, ch2Val));
*/
  // Small delay to avoid spamming the serial monitor
  //delay(5);
}

double upDownPercent(long min, long max, long reading){
  long digitalMin = min + 100;
  long digitalMax = max - 100;

  if(reading < digitalMin){
    reading = digitalMin;
  }
  
  if(reading > digitalMax){
    reading = digitalMax;
  }

  return (1.00)*(reading-digitalMin)/(digitalMax-digitalMin);

}

double leftRightPercent(long max, long min, long reading){
  long digitalMin = min + 100;
  long digitalMax = max - 100;

  if(reading < digitalMin){
    reading = digitalMin;
  }
  
  if(reading > digitalMax){
    reading = digitalMax;
  }

  return (1.00)*(digitalMax-reading)/(digitalMax-digitalMin);
}