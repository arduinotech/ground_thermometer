#include <Arduino.h>
#include <Streaming.h>

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    Serial << "loop()" << endl;
    delay(1000);
}
