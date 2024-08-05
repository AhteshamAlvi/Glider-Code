const int ch1Pin = 2;
const int ch2Pin = 3;
const int ch3Pin = 4;
const int ch4Pin = 5;
const int ch5Pin = 6;

void setup() {
  Serial.begin(9600);
  
  pinMode(ch1Pin, INPUT);
  pinMode(ch2Pin, INPUT);
  pinMode(ch3Pin, INPUT);
  pinMode(ch4Pin, INPUT);
  pinMode(ch5Pin, INPUT);
}

void loop() {
  // Read the pulse width for each channel
  unsigned long ch1Val = pulseIn(ch1Pin, HIGH);
  unsigned long ch2Val = pulseIn(ch2Pin, HIGH);
  unsigned long ch3Val = pulseIn(ch3Pin, HIGH);
  unsigned long ch4Val = pulseIn(ch4Pin, HIGH);
  unsigned long ch5Val = pulseIn(ch5Pin, HIGH);
  
  // Print the values to the Serial Monitor
  Serial.print("Channel 1: ");
  Serial.print(ch1Val);
  Serial.print(" Channel 2: ");
  Serial.print(ch2Val);
  Serial.print(" Channel 3: ");
  Serial.print(ch3Val);
  Serial.print(" Channel 4: ");
  Serial.print(ch4Val);
  Serial.print(" Channel 5: ");
  Serial.println(ch5Val);
  
  // Small delay to avoid spamming the serial monitor
  delay(100);
}