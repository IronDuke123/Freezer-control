// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain
//added code to turn a freezer on and off at 38 degrees to turn it into a fridge temporarily..
#include "DHT.h"

#define DHTPIN 2     // what pin we're connected to
#define RelayPin 4 // pin connected to SSR  High to turn on, other side of SSR to gnd
#define SetTemp 38 // set temperature for SSR control
// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  pinMode(RelayPin, OUTPUT); 

  dht.begin();
}
float tempF = 0 ;

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);   // Will have to change this to something like 30 seconds or so?? Maybe a minute
 // Read temperature as Fahrenheit (isFahrenheit = true)
   tempF = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if ( isnan(tempF)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

   
  Serial.print("Temperature: ");
  Serial.print(tempF);
  Serial.println(" *F\t");
 if ( tempF > SetTemp)  digitalWrite(RelayPin,HIGH);  // if too warm then turn on compressor
 else if (tempF < (SetTemp-2)) digitalWrite(RelayPin,LOW);  // if temp is 2 degrees colder than setpoint turn off compressor
 
}
