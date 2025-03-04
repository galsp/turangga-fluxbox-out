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
            Serial.println("{ \"ultrasonik\" : true }");
        }
    }
    else if (sensore > 100)
    {
        millise1 = millis();
        if (millis() - millise2 > 1500 && detected == true)
        {
            detected = false;
            Serial.println("{ \"ultrasonik\" : false }");
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
            Serial.println("{ \"pb1\" : true }");
        }
    }
    else
    {
        if (status1 == false)
        {
            status1 = true;
            Serial.println("{ \"pb1\" : false }");
        }
        delayR1 = millis();
    }

    if (digitalRead(relay2) == LOW)
    {
        if (millis() - delayR2 > 500 && status2 == true)
        {
            status2 = false;
            Serial.println("{ \"pb2\" : true }");
        }
    }
    else
    {
        if (status2 == false)
        {
            status2 = true;
            Serial.println("{ \"pb2\" : false }");
        }
        delayR2 = millis();
    }

    if (digitalRead(relay3) == LOW)
    {
        if (millis() - delayR3 > 500 && status3 == true)
        {
            status3 = false;
            Serial.println("{ \"pb3\" : true }");
        }
    }
    else
    {
        if (status3 == false)
        {
            status3 = true;
            Serial.println("{ \"pb3\" : false }");
        }
        delayR3 = millis();
    }

    if (digitalRead(relay4) == LOW)
    {
        if (millis() - delayR4 > 500 && status4 == true)
        {
            status4 = false;
            Serial.println("{ \"pb4\" : true }");
        }
    }
    else
    {
        if (status4 == false)
        {
            status4 = true;
            Serial.println("{ \"pb4\" : false }");
        }
        delayR4 = millis();
    }
}

void printping()
{
    unsigned long millise = millis();
    int sensore = sonar.ping_cm();
    String statusPing = "false";
    String feedback;
    // Serial.println("ping");
    // Serial.print("Jarak: ");
    // feedback = Serial2.readString();
    if (Serial2.availableForWrite() > 0)
    {
        Serial2.print("(ping)");
    }
    while (Serial2.available() == 0)
    {
        if (millis() - millise > 5000)
        {
            statusPing = "false";
            Serial.println("{ \"jarak\" : " + (String)sensore + ", \"status\" : " + statusPing + " }");
            return;
        }
    }
    feedback = Serial2.readString();

    if (feedback.indexOf("Matrix") != -1)
    {
        statusPing = "true";
    }
    Serial.println("{ \"jarak\" : " + (String)sensore + ", \"status\" : " + statusPing + " }");
    delay(50);
}
