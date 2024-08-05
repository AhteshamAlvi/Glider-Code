#include <Servo.h>
#include <Adafruit_LSM6DSOX.h>

// Servo objects
Servo Servo1; // Left Wing
Servo Servo2; // Right Wing

// Reciever pins
const int ch2Pin = 3;
const int ch3Pin = 4;

int servo1Write;
int servo2Write;

// For SPI mode, we need a CS pin
#define LSM_CS 10
// For software-SPI mode we need SCK/MOSI/MISO pins
#define LSM_SCK 13
#define LSM_MISO 12
#define LSM_MOSI 11

Adafruit_LSM6DSOX sox;

void setup(void) {
  Serial.begin(115200);
  
  // Attaches servos (output) on pins 8 and 9
  Servo1.attach(8);
  Servo2.attach(9);

  // Sets type of input pins to INPUT
  pinMode(ch2Pin, INPUT);
  pinMode(ch3Pin, INPUT);

  while (!Serial) {
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
  }

  if (!sox.begin_SPI(LSM_CS, LSM_SCK, LSM_MISO, LSM_MOSI)) {
    Serial.println("Failed to find LSM6DSOX chip");
    while (1) {
      delay(10);
    }
  }

  Serial.println("LSM6DSOX Found!");

  // sox.setAccelRange(LSM6DS_ACCEL_RANGE_2_G);
  Serial.print("Accelerometer range set to: ");
  switch (sox.getAccelRange()) {
  case LSM6DS_ACCEL_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case LSM6DS_ACCEL_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case LSM6DS_ACCEL_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case LSM6DS_ACCEL_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }

  // sox.setGyroRange(LSM6DS_GYRO_RANGE_250_DPS );
  Serial.print("Gyro range set to: ");
  switch (sox.getGyroRange()) {
  case LSM6DS_GYRO_RANGE_125_DPS:
    Serial.println("125 degrees/s");
    break;
  case LSM6DS_GYRO_RANGE_250_DPS:
    Serial.println("250 degrees/s");
    break;
  case LSM6DS_GYRO_RANGE_500_DPS:
    Serial.println("500 degrees/s");
    break;
  case LSM6DS_GYRO_RANGE_1000_DPS:
    Serial.println("1000 degrees/s");
    break;
  case LSM6DS_GYRO_RANGE_2000_DPS:
    Serial.println("2000 degrees/s");
    break;
  case ISM330DHCX_GYRO_RANGE_4000_DPS:
    break; // unsupported range for the DSOX
  }

  // sox.setAccelDataRate(LSM6DS_RATE_12_5_HZ);
  Serial.print("Accelerometer data rate set to: ");
  switch (sox.getAccelDataRate()) {
  case LSM6DS_RATE_SHUTDOWN:
    Serial.println("0 Hz");
    break;
  case LSM6DS_RATE_12_5_HZ:
    Serial.println("12.5 Hz");
    break;
  case LSM6DS_RATE_26_HZ:
    Serial.println("26 Hz");
    break;
  case LSM6DS_RATE_52_HZ:
    Serial.println("52 Hz");
    break;
  case LSM6DS_RATE_104_HZ:
    Serial.println("104 Hz");
    break;
  case LSM6DS_RATE_208_HZ:
    Serial.println("208 Hz");
    break;
  case LSM6DS_RATE_416_HZ:
    Serial.println("416 Hz");
    break;
  case LSM6DS_RATE_833_HZ:
    Serial.println("833 Hz");
    break;
  case LSM6DS_RATE_1_66K_HZ:
    Serial.println("1.66 KHz");
    break;
  case LSM6DS_RATE_3_33K_HZ:
    Serial.println("3.33 KHz");
    break;
  case LSM6DS_RATE_6_66K_HZ:
    Serial.println("6.66 KHz");
    break;
  }

  // sox.setGyroDataRate(LSM6DS_RATE_12_5_HZ);
  Serial.print("Gyro data rate set to: ");
  switch (sox.getGyroDataRate()) {
  case LSM6DS_RATE_SHUTDOWN:
    Serial.println("0 Hz");
    break;
  case LSM6DS_RATE_12_5_HZ:
    Serial.println("12.5 Hz");
    break;
  case LSM6DS_RATE_26_HZ:
    Serial.println("26 Hz");
    break;
  case LSM6DS_RATE_52_HZ:
    Serial.println("52 Hz");
    break;
  case LSM6DS_RATE_104_HZ:
    Serial.println("104 Hz");
    break;
  case LSM6DS_RATE_208_HZ:
    Serial.println("208 Hz");
    break;
  case LSM6DS_RATE_416_HZ:
    Serial.println("416 Hz");
    break;
  case LSM6DS_RATE_833_HZ:
    Serial.println("833 Hz");
    break;
  case LSM6DS_RATE_1_66K_HZ:
    Serial.println("1.66 KHz");
    break;
  case LSM6DS_RATE_3_33K_HZ:
    Serial.println("3.33 KHz");
    break;
  case LSM6DS_RATE_6_66K_HZ:
    Serial.println("6.66 KHz");
    break;
  }
}

void loop() {
  // Read the pulse width for each channel
  unsigned long ch2Val = pulseIn(ch2Pin, HIGH);
  unsigned long ch3Val = pulseIn(ch3Pin, HIGH);
  
  // Flapping or Gliding
  if(ch2Val > 1134) {
    // Frequency
    double freq = frequencyCalc(1084, 1893, ch2Val);

    // Right
    if (ch3Val > 1570) {
      servo1Write = map(80, 0, 180, 700, 2294);
      servo2Write = map(140, 0, 180, 700, 2294);
      Servo1.writeMicroseconds(servo1Write);
      Servo2.writeMicroseconds(servo2Write);
      delay(1000 * freq);

      servo1Write = map(100, 0, 180, 700, 2294);
      servo2Write = map(40, 0, 180, 700, 2294);
      Servo1.writeMicroseconds(servo1Write);
      Servo2.writeMicroseconds(servo2Write);
      delay(1000 * freq);

    // Left
    } else if (ch3Val < 1370) {
      servo1Write = map(40, 0, 180, 700, 2294);
      servo2Write = map(100, 0, 180, 700, 2294);
      Servo1.writeMicroseconds(servo1Write);
      Servo2.writeMicroseconds(servo2Write);
      delay(1000 * freq);

      servo1Write = map(140, 0, 180, 700, 2294);
      servo2Write = map(80, 0, 180, 700, 2294);
      Servo1.writeMicroseconds(servo1Write);
      Servo2.writeMicroseconds(servo2Write);
      delay(1000 * freq);

    } else {
      servo1Write = map(40, 0, 180, 700, 2294);
      servo2Write = map(140, 0, 180, 700, 2294);
      Servo1.writeMicroseconds(servo1Write);
      Servo2.writeMicroseconds(servo2Write);
      delay(1000 * freq);

      servo1Write = map(140, 0, 180, 700, 2294);
      servo2Write = map(40, 0, 180, 700, 2294);
      Servo1.writeMicroseconds(servo1Write);
      Servo2.writeMicroseconds(servo2Write);
      delay(1000 * freq);
    }
    
  } else {
    int angle = incrementMap(177, 118, ch3Val);

    servo1Write = map(angle, 0, 180, 700, 2294);
    servo2Write = map(angle, 0, 180, 700, 2294);
    Servo1.writeMicroseconds(servo1Write);
    Servo2.writeMicroseconds(servo2Write);
    delay(20);
  }

  windValues();
}

void windValues() {
  //  /* Get a new normalized sensor event */
  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temp;
  sox.getEvent(&accel, &gyro, &temp);

  Serial.print("\t\tTemperature ");
  Serial.print(temp.temperature);
  Serial.println(" deg C");

  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("\t\tAccel X: ");
  Serial.print(accel.acceleration.x);
  Serial.print(" \tY: ");
  Serial.print(accel.acceleration.y);
  Serial.print(" \tZ: ");
  Serial.print(accel.acceleration.z);
  Serial.println(" m/s^2 ");

  /* Display the results (rotation is measured in rad/s) */
  Serial.print("\t\tGyro X: ");
  Serial.print(gyro.gyro.x);
  Serial.print(" \tY: ");
  Serial.print(gyro.gyro.y);
  Serial.print(" \tZ: ");
  Serial.print(gyro.gyro.z);
  Serial.println(" radians/s ");
  Serial.println();

  // // serial plotter friendly format
  // Serial.print(temp.temperature);
  // Serial.print(",");

  // Serial.print(accel.acceleration.x);
  // Serial.print(","); Serial.print(accel.acceleration.y);
  // Serial.print(","); Serial.print(accel.acceleration.z);
  // Serial.print(",");

  // Serial.print(gyro.gyro.x);
  // Serial.print(","); Serial.print(gyro.gyro.y);
  // Serial.print(","); Serial.print(gyro.gyro.z);
  // Serial.println();
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