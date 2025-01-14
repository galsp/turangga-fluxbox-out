#include <Arduino.h>
#include "gall.h"

void setup()
{
  Serial.begin(9600);
  Serial2.begin(9600);
  setup2();
}

void loop()
{
  if (Serial2.available())
  {
    Serial.write(Serial2.read());
  }

  if (Serial.available())
  {
    byte bufer[64];
    int len = Serial.readBytes(bufer, 64);
    for (int i = 0; i < len; i++)
    {
      if (bufer[i] == 40)
      {
        for (int j = i - 1; bufer[j] != 41; j++)
        {
          Serial2.write(bufer[j+1]);
        }
      }

      if (bufer[i] == 112 && bufer[i + 1] == 105 && bufer[i + 2] == 110 && bufer[i + 3] == 103 && bufer[i + 4] != 41)
      {
        printping();
      }
    }
  }
  delay(50);
  errRelay();
  printSensor();
}