#include <Arduino.h>
#include <NewPing.h>

#define trigPin 33
#define echoPin 32
#define MAX_DISTANCE 400

NewPing sonar(trigPin, echoPin, MAX_DISTANCE);

unsigned long delayR1;
unsigned long delayR2;
unsigned long delayR3;
unsigned long delayR4;

bool status1 = false;
bool status2 = false;
bool status3 = false;
bool status4 = false;

#define relay1 19
#define relay2 18
#define relay3 26
#define relay4 27

unsigned long millise1;
unsigned long millise2;
bool detected = false;
void setup2()
{
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    pinMode(relay1, INPUT_PULLUP);
    pinMode(relay2, INPUT_PULLUP);
    pinMode(relay3, INPUT_PULLUP);
    pinMode(relay4, INPUT_PULLUP);
}

void printSensor()
{
    int sensore = sonar.ping_cm();
    if (sensore <= 100 && sensore > 0)
    {
        millise2 = millis();
        if (millis() - millise1 > 200 && detected == false)
        {
            detected = true;
            Serial.println("detected");
        }
    }
    else if (sensore > 100)
    {
        millise1 = millis();
        if (millis() - millise2 > 1500 && detected == true)
        {
            detected = false;
            Serial.println("not detected");
        }
    }
}

void errRelay()
{

    if (digitalRead(relay1) == LOW)
    {
        if (millis() - delayR1 > 500 && status1 == true)
        {
            status1 = false;
            Serial.println("Relay1:1");
        }
    }
    else
    {
        if (status1 == false)
        {
            status1 = true;
            Serial.println("Relay1:0");
        }
        delayR1 = millis();
    }

    if (digitalRead(relay2) == LOW)
    {
        if (millis() - delayR2 > 500 && status2 == true)
        {
            status2 = false;
            Serial.println("Relay2:1");
        }
    }
    else
    {
        if (status2 == false)
        {
            status2 = true;
            Serial.println("Relay2:0");
        }
        delayR2 = millis();
    }

    if (digitalRead(relay3) == LOW)
    {
        if (millis() - delayR3 > 500 && status3 == true)
        {
            status3 = false;
            Serial.println("Relay3:1");
        }
    }
    else
    {
        if (status3 == false)
        {
            status3 = true;
            Serial.println("Relay3:0");
        }
        delayR3 = millis();
    }

    if (digitalRead(relay4) == LOW)
    {
        if (millis() - delayR4 > 500 && status4 == true)
        {
            status4 = false;
            Serial.println("Relay4:1");
        }
    }
    else
    {
        if (status4 == false)
        {
            status4 = true;
            Serial.println("Relay4:0");
        }
        delayR4 = millis();
    }
}

void printping()
{
    Serial.println("ping");
    Serial.print("Jarak: ");
    delay(50);
    Serial.println(sonar.ping_cm());
}
