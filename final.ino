// Constants
const int ultrasonicTriggerPin = 2;    // Ultrasonic sensor trigger pin
const int ultrasonicEchoPin = 3;      // Ultrasonic sensor echo pin
const int frontIRPin = 4;             // Front IR sensor pin
const int rightIRPin = 5;             // Right IR sensor pin
const int leftIRPin = 6;              // Left IR sensor pin
const int elevatedIR1Pin = A0;        // Elevated IR sensor 1 pin (analog pin)
const int elevatedIR2Pin = A1;        // Elevated IR sensor 2 pin (analog pin)
const int waterSensorPin = A2;        // Water sensor pin (analog pin)
const int flameSensorPin = A3;        // Flame sensor pin (analog pin)
const int isd1820PlayPin = 9;         // ISD1820 module PLAY pin
const int downwardUltrasonicTriggerPin = 10;  // Downward ultrasonic sensor trigger pin
const int downwardUltrasonicEchoPin = 11;     // Downward ultrasonic sensor echo pin
const int buzzerPin = 12;             // Buzzer pin

// Variables
long ultrasonicDuration;               // Time taken for ultrasonic pulse to return
int ultrasonicDistance;                // Distance measured by the ultrasonic sensor

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Configure pin modes
  pinMode(ultrasonicTriggerPin, OUTPUT);
  pinMode(ultrasonicEchoPin, INPUT);
  pinMode(frontIRPin, INPUT);
  pinMode(rightIRPin, INPUT);
  pinMode(leftIRPin, INPUT);
  pinMode(elevatedIR1Pin, INPUT);
  pinMode(elevatedIR2Pin, INPUT);
  pinMode(waterSensorPin, INPUT);
  pinMode(flameSensorPin, INPUT);
  pinMode(isd1820PlayPin, OUTPUT);
  pinMode(downwardUltrasonicTriggerPin, OUTPUT);
  pinMode(downwardUltrasonicEchoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // Ultrasonic sensor
  digitalWrite(ultrasonicTriggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(ultrasonicTriggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrasonicTriggerPin, LOW);
  ultrasonicDuration = pulseIn(ultrasonicEchoPin, HIGH);
  ultrasonicDistance = ultrasonicDuration * 0.034 / 2;
  Serial.print("Ultrasonic Distance: ");
  Serial.print(ultrasonicDistance);
  Serial.println(" cm");
  if (ultrasonicDistance <= 40) {
    digitalWrite(buzzerPin, HIGH);
    delay(200);
    digitalWrite(buzzerPin, LOW);
  }

  // Front, Right, and Left IR sensors
  int frontIRValue = digitalRead(frontIRPin);
  int rightIRValue = digitalRead(rightIRPin);
  int leftIRValue = digitalRead(leftIRPin);
  if (frontIRValue == LOW) {
    Serial.println("Front obstacle detected");
    digitalWrite(buzzerPin, HIGH);
  }
  else if (rightIRValue == LOW) {
    Serial.println("Right obstacle detected");
    digitalWrite(buzzerPin, HIGH);
  }
  else if (leftIRValue == LOW) {
    Serial.println("Left obstacle detected");
    digitalWrite(buzzerPin, HIGH);
  }
  else {
    digitalWrite(buzzerPin, LOW);
  }

  // Elevated IR sensors
  int elevatedIR1Value = analogRead(elevatedIR1Pin);
  int elevatedIR2Value = analogRead(elevatedIR2Pin);
  if (elevatedIR1Value < 200 && elevatedIR2Value > 800) {
    Serial.println("Upstairs detected!");
  }

  // Water sensor
  int waterValue = analogRead(waterSensorPin);
  Serial.print("Water value: ");
  Serial.println(waterValue);
  if (waterValue > 450 && waterValue < 790) {
    Serial.println("Water detected!");
    playLastRecordedModule();
  }

  // Flame sensor
  int flameValue = analogRead(flameSensorPin);
  Serial.print("Flame Sensor Value: ");
  Serial.println(flameValue);
  if (flameValue < 610) {
    Serial.println("Flame detected!");
    digitalWrite(buzzerPin, HIGH);
    // Take necessary actions here
  }
  else {
    digitalWrite(buzzerPin, LOW);
  }

  // Downward ultrasonic sensor
  digitalWrite(downwardUltrasonicTriggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(downwardUltrasonicTriggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(downwardUltrasonicTriggerPin, LOW);
  long downwardUltrasonicDuration = pulseIn(downwardUltrasonicEchoPin, HIGH);
  int downwardUltrasonicDistance = downwardUltrasonicDuration * 0.034 / 2;
  Serial.print("Downward Ultrasonic Distance: ");
  Serial.print(downwardUltrasonicDistance);
  Serial.println(" cm");

  delay(1000);
}

void playLastRecordedModule() {
  digitalWrite(isd1820PlayPin, HIGH);
  delay(100);
  digitalWrite(isd1820PlayPin, LOW);
}
