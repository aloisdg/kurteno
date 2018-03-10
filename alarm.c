#include <DS3231_Simple.h>

#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11
#define FULL_ROTATION 4076

DS3231_Simple Clock;

int led = 13;

const int phases1[] = {0, 0, 0, 0, 0, 1, 1, 1};
const int phases2[] = {0, 0, 0, 1, 1, 1, 0, 0};
const int phases3[] = {0, 1, 1, 1, 0, 0, 0, 0};
const int phases4[] = {1, 1, 0, 0, 0, 0, 0, 1};
int Phase = 0;
int Speed = 100; //MUST BE 1 - 100

void setup() {

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
   
  pinMode(led, OUTPUT);
  
  Clock.begin();
  Clock.disableAlarms();
  DateTime MyTimestamp = Clock.read();              

  /*
  MyTimestamp.Hour      = 8;
  MyTimestamp.Minute    = 30;
  MyTimestamp.Second    = 0;*/
  MyTimestamp.Second    = 1;
  
  // And now add the alarm to happen when the second matches
  Clock.setAlarm(MyTimestamp, DS3231_Simple::ALARM_MATCH_SECOND);  
  Serial.begin(115200);
}

void loop() 
{ 
  uint8_t AlarmsFired = Clock.checkAlarms();
  
  // Then can check if either alarm is fired (there are 2 alarms possible in the chip)
  // by using a "bitwise and"
  if(AlarmsFired & 1)
  {
    stepper(FULL_ROTATION); 
    digitalWrite(led, HIGH);
    delay(1000);
  }
  digitalWrite(led, LOW);
}


  
void stepper(int count)
{
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
}

void IncrementPhase(int rotationDirection)
{
  Phase += 8;
  Phase += rotationDirection;
  Phase %= 8;
}
