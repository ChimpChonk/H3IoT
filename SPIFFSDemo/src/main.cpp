#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>


void setup() {
  Serial.begin(115200);
  Serial.println("Open LittleFS");

  bool success = LittleFS.begin();

  if(!success)
  {
    Serial.println("Error mounting file");
    return;
  }

  File file = LittleFS.open("/config.txt", "r");
  if(!file) 
  {
    Serial.println("Error opening file for reading");
    return;
  }

  Serial.println("File content:");

  while (file.available())
  {
    Serial.write(file.read());
  }

  file.close();
  
}

void loop() {
  // put your main code here, to run repeatedly:
}
