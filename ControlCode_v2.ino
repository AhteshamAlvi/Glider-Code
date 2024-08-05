#include <Servo.h>

// Servo objects
Servo Servo1; // Left Wing
Servo Servo2; // Right Wing

// Reciever pins
const int ch2Pin = 3;
const int ch3Pin = 4;

void setup() {
  Serial.begin(9600);
  
  // Attaches servos (output) on pins 11 and 12
  Servo1.attach(8);
  Servo2.attach(9);

  // Sets type of input pins to INPUT
  pinMode(ch2Pin, INPUT);
  pinMode(ch3Pin, INPUT);
}

void loop() {
  // Read the pulse width for each channel
  unsigned long ch2Val = pulseIn(ch2Pin, HIGH);
  unsigned long ch3Val = pulseIn(ch3Pin, HIGH);
  
  // Flapping or Gliding
  if(ch2Val > 1134) {
    // Frequency
    double freq = frequencyCalc(1084, 1893, ch2Val);

    if (ch3Val > 1570) {
      Servo1.write(80);
      Servo2.write(140);
      delay(1000 * freq);
      Servo1.write(100);
      Servo2.write(40);
      delay(1000 * freq);
    } else if (ch3Val < 1370) {
      Servo1.write(40);
      Servo2.write(100);
      delay(1000 * freq);
      Servo1.write(140);
      Servo2.write(80);
      delay(1000 * freq);
    } else {
      Servo1.write(40);
      Servo2.write(140);
      delay(1000 * freq);
      Servo1.write(140);
      Servo2.write(40);
      delay(1000 * freq);
    }
  } else {
    int angle = incrementMap(177, 118, ch3Val);

    Servo1.write(angle);
    Servo2.write(angle);
    delay(20);
  }
}

double frequencyCalc(long min, long max, long signal) {
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
  int angle = 20;

  while(angle < 120) {
    if(signal <= check) {
      angle += 10;
      check -= interval;
    } else {
      return angle;
    }
  }
  return 140;
}