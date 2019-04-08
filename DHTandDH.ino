#include "DHT.h"

int ledPin = 7;        // choose the pin for the LED
int inputPin = 2;       // choose the input pin (for PIR sensor)

int pirState = LOW;     // we start, assuming no motion detected
int val = 0;            // variable for reading the pin status
 
int DHTPIN = 3;         // Digital pin connected to the DHT sensor
   
#define DHTTYPE DHT11   // Sensor type DHT 11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
  
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  Serial.println(F("PIR sensor test!"));

  dht.begin();
}

void loop() {

  // Need delay becouse DH11 has long loop for measurement
  for(int i=0; i<500; i++){
    PIRSensorHandler();
    delay(2);
  }

  measurementHumidityAndTemp();
}

/**
 * Measurement Air parametrs
 */
void measurementHumidityAndTemp(){
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.println("");
  
}

void PIRSensorHandler(){
  val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    logPIRBehaviorDetectMotion();
  } else {
    digitalWrite(ledPin, LOW); // turn LED OFF
    logPIRBehaviorDontDetectMotion();
  }
}

void logPIRBehaviorDetectMotion(){
  if (pirState == LOW) {
    Serial.println("Motion detected!");
    pirState = HIGH; //Set detect motion status
  }
}
void logPIRBehaviorDontDetectMotion(){
  if(pirState == HIGH){
    Serial.println("Motion ended!");
    pirState = LOW; //Set no motion status
  }
}
