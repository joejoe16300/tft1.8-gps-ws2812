/*
 Name:		tft1.ino
 Created:	2020/1/13 21:21:27
 Author:	joe
*/
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 2, TXPin = 3;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);
// the setup function runs once when you press reset or power the board
void setup() {
    Serial.begin(9600);
    ss.begin(GPSBaud);
}

// the loop function runs over and over again until power down or reset
void loop() 
{
    while (ss.available() > 0) {
        gps.encode(ss.read());
        if (gps.location.isUpdated()) {
            Serial.print("Latitude= ");
            Serial.print(gps.location.lat(), 6);
            Serial.print(" Longitude= ");
            Serial.println(gps.location.lng(), 6);
        }
    }
}
