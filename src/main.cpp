#include <Arduino.h>

int tempPin = A0;
int sensorInput;
double currentTemp;
double currentVoltage;
double accuracyOffset = -2.8;

// REMEMBER TO CHANGE TEMP RANGE VALUES BEFORE USING
// ADJUST LED PIN NUMBERS IF NECESSARY
int redLED = 12;
double redMin = 0.00;
double redMax = 15.00;
bool isInRedRange;

int greenLED = 11;
double greenMin = 15.1;
double greenMax = 35.00;
bool isInGreenRange;

int blueLED = 10;
double blueMin = 55.00;
double blueMax = 100.00;
bool isInBlueRange;

bool checkIsInTempRange(double tempMin, double tempMax, double currentTemp) {
  /* 
   * Checks if current temperature is within the range of min and max values.
   */ 
  if (currentTemp > tempMin && currentTemp < tempMax) return true;
  else return false;
}

void toggleLED(int ledPin, bool isInRange) {
  /*
   * Turns on an LED if the temperature is within the LEDs respective range.
   */
  if (isInRange) digitalWrite(ledPin, HIGH);
  else digitalWrite(ledPin, LOW);
}

double convertInputToDegrees(double input) {
  /*
   * Converts temperature sensor input into degrees celsius.
   */
  return ((((input / 1024) * 5) - 0.5) * 100) - accuracyOffset;
}

double convertInputToVoltage(double input) {
  /*
   * Converts temperature sensor input into volts.
   */
  return (input / 1024) * 5;
}

void setup() {
  pinMode(redLED, OUTPUT); //pinMode(pinNumber, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  sensorInput = (double)analogRead(tempPin);
  currentTemp = convertInputToDegrees(sensorInput);
  currentVoltage = convertInputToVoltage(sensorInput);

  isInRedRange = checkIsInTempRange(redMin, redMax, currentTemp);
  isInGreenRange = checkIsInTempRange(greenMin, greenMax, currentTemp);
  isInBlueRange = checkIsInTempRange(blueMin, blueMax, currentTemp);

  toggleLED(redLED, isInRedRange);
  toggleLED(greenLED, isInGreenRange);
  toggleLED(blueLED, isInBlueRange);

  // Serial Output: "Temperature: NN.NN°C"
  Serial.print("Temperature: ");
  Serial.print(currentTemp);
  Serial.println("°C");

  Serial.print("Voltage: ");
  Serial.print(currentVoltage);
  Serial.println("V");

  Serial.print("Voltage (Offset Adjusted): ");
  Serial.print(currentVoltage - 0.5);
  Serial.println("V\n");

  delay(2000);
}