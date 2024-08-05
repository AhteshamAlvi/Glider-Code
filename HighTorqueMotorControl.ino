#include <Servo.h>    
Servo myservo;  
    
int value = 0;
int value_convert = 0;  

// Servo objects
Servo Servo1; // Left Wing
Servo Servo2; // Right Wing
int servoMin = 700;
int servoMax = 2294;

int servo1Input = 0;
int servo2Input = 0;

// Reciever pins
const int ch2Pin = 3;
const int ch4Pin = 5;

unsigned long ch2Val;
unsigned long ch2Min = 1084;
unsigned long ch2Max = 1893;


unsigned long ch4Val;
unsigned long ch4Min = 1207;
unsigned long ch4Max = 2000;


void setup() {
  Serial.begin(9600);
  
  // Attaches servos (output) on pins 11 and 12
  Servo1.attach(8);
  Servo2.attach(9);

  // Sets type of input pins to INPUT
  pinMode(ch2Pin, INPUT);
  pinMode(ch4Pin, INPUT);
}

void loop() {
  // Read the pulse width for each channel
  ch2Val = pulseIn(ch2Pin, HIGH);
  ch4Val = pulseIn(ch4Pin, HIGH);

  constrain(ch2Val, ch2Min+100, ch2Max-100);
  constrain(ch4Val, ch4Min+100, ch4Max-100);

  servo1Input = map(ch2Val, ch2Min+100, ch2Max-100, servoMin, servoMax);
  servo2Input = map(ch2Val, ch2Min+100, ch2Max-100, servoMin, servoMax);

  Servo1.writeMicroseconds(servo1Input);
  Servo2.writeMicroseconds(servo2Input);
}