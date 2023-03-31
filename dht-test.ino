#include "Adafruit_DHT.h"

// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#define DHTPIN 4    // what pin we're connected to

#define DHTTYPE DHT22		// DHT 22 (AM2302)

// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

DHT dht(DHTPIN, DHTTYPE);
void myHandler(const char *event, const char *data) {
  // Handle the integration response
}
void setup() {
      Particle.subscribe("hook-response/temp", myHandler, MY_DEVICES);
	Serial.begin(9600); 
	Serial.println("DHTxx test!");

	dht.begin();
}

void loop() {
    // Read temperature as Celsius
    float temp = dht.getTempCelcius();

  // Get some data
  String data = String(temp);
  // Trigger the integration
  Particle.publish("temp", data, PRIVATE);

// Wait a few seconds between measurements.
	delay(2000);

// Reading temperature or humidity takes about 250 milliseconds!
// Sensor readings may also be up to 2 seconds 'old' (its a 
// very slow sensor)
	float h = dht.getHumidity();
// Read temperature as Farenheit
	float f = dht.getTempFarenheit();
  
  
// Check if any reads failed and exit early (to try again).
	if (isnan(h) || isnan(temp) || isnan(f)) {
		Serial.println("Failed to read from DHT sensor!");
		return;
	}

// Compute heat index
// Must send in temp in Fahrenheit!
	float hi = dht.getHeatIndex();
	float dp = dht.getDewPoint();
	float k = dht.getTempKelvin();

	Serial.print("Humid: "); 
	Serial.print(h);
	Serial.print("% - ");
	Serial.print("temp: "); 
	Serial.print(temp);
	Serial.print("*C ");
	Serial.print(f);
	Serial.print("*F ");
	Serial.print(k);
	Serial.print("*K - ");
	Serial.print("DewP: ");
	Serial.print(dp);
	Serial.print("*C - ");
	Serial.print("HeatI: ");
	Serial.print(hi);
	Serial.println("*C");
	Serial.println(Time.timeStr());
	  
	  



}

