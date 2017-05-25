#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <SD.h>
#define SD_SS_PIN 11

long lat, lon;
String aLat, aLon;

SoftwareSerial gpsSerial(2, 1);
TinyGPS gps;

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);

  // SD Card Initialization
  if (!SD.begin(SD_SS_PIN)) {
    Serial.println("Error: SD card failed to initialise or is missing.");
  } else {
    Serial.println("SD Card has connected.");
  
    if (SD.exists("example.txt")) {
      Serial.println("The file has been found.");
    } else {
      Serial.println("The file does not exist.");
    }
    return;
  }
}

void loop() {
  while (gpsSerial.available()) {
    if (gps.encode(gpsSerial.read())) {
      gps.get_position(&lat, &lon);

      if (String(lat).length() == 8) {
        aLat = String(lat).substring(0, 2) + "." + String(lat).substring(3, 8);
      } else if (String(lat).length() == 7) {
        aLat = String(lat).substring(0, 1) + "." + String(lat).substring(2, 7);
      }
                
      if (String(lon).length() == 8) {
        aLon = String(lon).substring(0, 2) + "." + String(lon).substring(3, 8);
      } else if (String(lon).length() == 7) {
        aLon = String(lon).substring(0, 1) + "." + String(lon).substring(2, 7);
      }

      Serial.print(aLat);
      Serial.print(",");
      Serial.println(aLon);

      File myfile = SD.open("example.txt", FILE_WRITE);

      if (myfile)
      {
        Serial.print("Writing to the text file...");
        myfile.println(aLat + "," + aLon);

        myfile.close(); // close the file:
        Serial.println("done closing.");
      } else
      {
        // if the file didn't open, report an error:
        Serial.println("error opening the text file!");
      }
    }
  }
}
