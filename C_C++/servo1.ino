#include <Servo.h>

Servo myServo;
int const potPin = A0;
int potVal;
int angle;
const int interval = 60;

void setup()
{
    Serial.begin(9600);
    myServo.attach(9);
    myServo.write(map(0, 0, interval, 0, 179));
}

void loop()
{
    for (int interval_counter = interval; interval_counter > 0; interval_counter--) {
        angle = map(interval_counter, 0, interval, 0, 179);
        myServo.write(angle);

        Serial.print("Angle: ");
        Serial.println(angle);

        delay(500);
    }
}


