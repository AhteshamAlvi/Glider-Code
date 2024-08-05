#include <Servo.h>

// Servo objects
Servo Servo1;
Servo Servo2;

// Reciever pins
const int ch2Pin = 3;
const int ch3Pin = 4;
const int ch4Pin = 5;
const int ch5Pin = 6;

void setup() {
  Serial.begin(9600);
  
  // Attaches servos (output) on pins 11 and 12
  Servo1.attach(8);
  Servo2.attach(9);

  // Sets type of input pins to INPUT
  pinMode(ch2Pin, INPUT);
  pinMode(ch3Pin, INPUT);
  pinMode(ch4Pin, INPUT);
  pinMode(ch5Pin, INPUT);
}

void loop() {
  // Read the pulse width for each channel
  unsigned long ch2Val = pulseIn(ch2Pin, HIGH);
  unsigned long ch3Val = pulseIn(ch3Pin, HIGH);
  unsigned long ch4Val = pulseIn(ch4Pin, HIGH);
  unsigned long ch5Val = pulseIn(ch5Pin, HIGH);
  
  // Flapping or Gliding
  if(ch2Val > 1134) {
    // Frequency
    double freq = upDownPercent(1084, 1893, ch2Val);

    Servo1.write(40);
    delay(1000 * freq);
    Servo1.write(140);
    delay(1000 * freq);

  } else {
    int angle = incrementMap(177, 118, ch3Val);

    Servo1.write(angle);
    delay(20);
  }
}

double upDownPercent(long min, long max, long signal) {
  long digitalMin = min + 100;
  long digitalMax = max - 100;

  if(signal < digitalMin && signal > min + 50){
    signal = digitalMin;
  }

  if(signal < min + 50) {
    return 0;
  }
  
  if(signal > digitalMax){
    signal = digitalMax;
  }

  return 1.00 - (.70)*(signal-digitalMin)/(digitalMax-digitalMin);
}

int incrementMap(int upperLimit, int lowerLimit, int rawSignal) {
  int signal = rawSignal/10;
  double interval = (upperLimit - lowerLimit) / 10.00;
  double check = upperLimit + 0.0;
  int angle = 40;

  while(angle < 140) {
    if(signal <= check) {
      angle += 10;
      check -= interval;
    } else {
      return angle;
    }
  }
  return 140;
}