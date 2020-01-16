#include <Arduino.h>

int tempPin = A0;
int sensorInput;
double currentTemp;
double currentVoltage;

// REMEMBER TO CHANGE TEMP RANGE VALUES BEFORE USING
// ADJUST LED PIN NUMBERS IF NECESSARY
int redLED = 8;
double redMin = 18.00;
double redMax = 22.99;
bool isInRedRange;

int greenLED = 9;
double greenMin = 23.0;
double greenMax = 27.99;
bool isInGreenRange;

int blueLED = 10;
double blueMin = 28.00;
double blueMax = 30.00;
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
  return (((input / 1024) * 5) - 0.5) * 100;
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
  Serial.println(currentVoltage);

  Serial.print("Voltage (Offset Adjusted): ");
  Serial.println(currentVoltage - 0.5);

  delay(500);
}