//  BYJ48 Stepper motor code
//  Connect :
//  IN1 >> D8
//  IN2 >> D9
//  IN3 >> D10
//  IN4 >> D11
//  VCC ... 5V Prefer to use external 5V Source
//  Gnd

// RTC Code

#include <DS3231_Simple.h>

#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11
#define RUDDY 12
#define GREEN 13
#define FULL_ROTATION 4076

const int phases1[] = {0, 0, 0, 0, 0, 1, 1, 1};
const int phases2[] = {0, 0, 0, 1, 1, 1, 0, 0};
const int phases3[] = {0, 1, 1, 1, 0, 0, 0, 0};
const int phases4[] = {1, 1, 0, 0, 0, 0, 0, 1};
int Phase = 0;
int Speed = 100; //MUST BE 1 - 100

void setup()
{
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(RUDDY, OUTPUT);
  pinMode(GREEN, OUTPUT);
  Serial.begin(115200);
}

void loop()
{
  stepper(FULL_ROTATION);
  stepper(-FULL_ROTATION);
}

void stepper(int count)
{
    digitalWrite(count >= 0 ? RUDDY : GREEN, HIGH);

  int rotationDirection = count < 1 ? -1 : 1;
  count *= rotationDirection;
  for (int x = 0; x < count; x++)
  {
    digitalWrite(IN1, phases1[Phase]);
    digitalWrite(IN2, phases2[Phase]);
    digitalWrite(IN3, phases3[Phase]);
    digitalWrite(IN4, phases4[Phase]);
    IncrementPhase(rotationDirection);
    delay(100 / Speed);
  }

    digitalWrite(count >= 0 ? RUDDY : GREEN, LOW);
}

void IncrementPhase(int rotationDirection)
{
  Phase += 8;
  Phase += rotationDirection;
  Phase %= 8;
}