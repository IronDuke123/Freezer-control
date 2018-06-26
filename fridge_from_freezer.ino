// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain
//added code to turn a freezer on and off at 38 degrees to turn it into a fridge temporarily..
//added code by Thomas Dupras 6/25/2018

#include "DHT.h"
#define DHTPIN 2     // what pin we're connected to
#define RelayPin 13 // pin connected to SSR  High to turn on, other side of SSR to gnd
#define SetTemp 38 // set temperature for SSR control  same default temp as my fridge
// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302)
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
  Serial.begin(9600);   // left serial in for debugging.. removed at completetion of project.. stands alone
  Serial.println("DHTxx test!");
  pinMode(RelayPin, OUTPUT); 

  dht.begin();
}
float tempF = 0 ;

void loop() {
  // Wait a few seconds between measurements.
 
 // Read temperature as Fahrenheit (is Fahrenheit = true)
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
 else if (tempF < (SetTemp-2)) {
  digitalWrite(RelayPin,LOW);  // if temp is 2 degrees colder than setpoint turn off compressor
  delay(300000);  // big 5 minute delay to help prevent slugging compressor from turning back on to rapidly..
 }
  delay(6000);   // Just slowing the whole loop down a little.. helped with serial debugging.. 
}
