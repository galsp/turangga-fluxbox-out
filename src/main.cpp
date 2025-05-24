#include <Arduino.h>
#include "gall.h"
#include <errOTA.h>

void setup()
{
  Serial.begin(9600);
  Serial2.begin(9600);
  setup2();
  setupOTA();
}

void loop()
{
  
  server.handleClient();
  ElegantOTA.loop();
  if (Serial.available())
  {
    byte bufer[64];
    int len = Serial.readBytes(bufer, 64);
    if (Serial2.available())
    {
      Serial2.read();
    }
    uint8_t matrik = 0;
    for (int i = 0; i < len; i++)
    {
      if (bufer[i] == 40)
      {
        matrik = 1;
        for (int j = i - 1; bufer[j] != 41; j++)
        {
          if (Serial2.availableForWrite() > 0){
          Serial2.write(bufer[j + 1]);
          }
        }
      }

      if (bufer[i] == 112 && bufer[i + 1] == 105 && bufer[i + 2] == 110 && bufer[i + 3] == 103 && bufer[i + 4] != 41)
      {
        matrik = 2;
        printping();
      }
    }

    if (matrik == 0)
    {
      Serial.println("{ \"Error\" : Command not found }");
      return;
    }

    if (matrik == 1)
    {
      unsigned long millise = millis();
      bool bole = false;
      while (!Serial2.available())
      {
        if (millis() - millise > 5000)
        {
          Serial.println("{ \"led\" : false }");
          return;
        }
      }
      Serial.println(Serial2.readString());
      return;
    }
  }
  delay(50);
  errRelay();
  printSensor();
}