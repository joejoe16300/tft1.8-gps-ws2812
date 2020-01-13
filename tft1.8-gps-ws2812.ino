#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <UTFT.h>
#define PIN      4
#define NUMPIXELS 24


Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels
static const int RXPin = 2, TXPin = 3;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;
extern uint8_t SmallFont[];
// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);
// the setup function runs once when you press reset or power the board

// Declare an instance of the class
//UTFT myGLCD(QD_TFT180A,A2,A1,A5,A4,A3);  // Remember to change the model parameter to suit your display module!
UTFT myGLCD(QD_TFT180A, A4, A5, A1, A2, A3);
void setup() 
{
    Serial.begin(9600);
    ss.begin(GPSBaud);
    pixels.begin();
    myGLCD.InitLCD(PORTRAIT);
    myGLCD.setFont(SmallFont);
}

// the loop function runs over and over again until power down or reset
void loop() 
{
    while (ss.available() > 0)
    {
        gps.encode(ss.read());
        if (gps.location.isUpdated())
        {
            Serial.print("Latitude= ");
            Serial.print(gps.location.lat(), 6);
            Serial.print(" Longitude= ");
            Serial.println(gps.location.lng(), 6);
            String lat = String(gps.location.lat());
            String lng = String(gps.location.lng());
            // Clear the screen and draw the frame
            myGLCD.clrScr();
            myGLCD.setContrast(64);

            myGLCD.setColor(255, 0, 0);
           
            myGLCD.print(lat, CENTER, 0);
            myGLCD.setBackColor(64, 64, 64);
            myGLCD.setColor(255, 255, 0);
            myGLCD.print(lng, LEFT, 116);
            pixels.clear();
            pixels.setBrightness(10);
            pixels.setPixelColor(0, pixels.Color(255, 255, 255));
            pixels.setPixelColor(1, pixels.Color(255, 0, 0));
           

        }
    }
}
