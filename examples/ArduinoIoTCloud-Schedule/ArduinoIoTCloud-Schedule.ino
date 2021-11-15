/*
  This sketch demonstrates how to use cloud schedule data type.

  This sketch is compatible with:
   - MKR 1000
   - MKR WIFI 1010
   - MKR GSM 1400
   - MKR NB 1500
   - MKR WAN 1300/1310
   - Nano 33 IoT
   - ESP 8266
*/

#include "arduino_secrets.h"
#include "thingProperties.h"

#if defined(ESP32)
static int const LED_BUILTIN = 2;
#endif

void setup() {
  /* Initialize serial and wait up to 5 seconds for port to open */
  Serial.begin(9600);
  for(unsigned long const serialBeginTime = millis(); !Serial && (millis() - serialBeginTime > 5000); ) { }

  /* Configure LED pin as an output */
  pinMode(LED_BUILTIN, OUTPUT);

  /* This function takes care of connecting your sketch variables to the ArduinoIoTCloud object */
  initProperties();

  /* Initialize Arduino IoT Cloud library */
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  setDebugMessageLevel(DBG_INFO);
  ArduinoCloud.printDebugInfo();

  /* Configure a schedule for LED. This should be done with Arduino create Scheduler widget */
  unsigned int startingFrom = Schedule::getTimeFromString("2021 Nov 01 17:00:00");      /* From 01/11/2021 17:00 */
  unsigned int untilTo = startingFrom + ( DAYS * 28 );                                  /* To   29/11/2021 17:00 */
  unsigned int executionPeriod = MINUTES * 6;                                           /* For         6 minutes */
  ScheduleWeeklyMask WeeklyMask = {
    ScheduleState::Inactive,                                                            /* Sunday    -> Inactive */
    ScheduleState::Active,                                                              /* Monday    -> Active   */
    ScheduleState::Inactive,                                                            /* Tuesday   -> Inactive */
    ScheduleState::Active,                                                              /* Wednesday -> Active   */
    ScheduleState::Inactive,                                                            /* Thursday  -> Inactive */
    ScheduleState::Active,                                                              /* Friday    -> Active   */
    ScheduleState::Inactive,                                                            /* Saturday  -> Inactive */
  };
  unsigned int scheduleConfiguration =  Schedule::createWeeklyScheduleConfiguration(WeeklyMask);

  led = Schedule(startingFrom, untilTo, executionPeriod, scheduleConfiguration);

  led.onScheduleEventStart(onLedEventStart);
  led.onScheduleEventEnd(onLedEventEnd);
}

void loop() {
  ArduinoCloud.update();

  /* Activate LED when schedule is active */
  digitalWrite(LED_BUILTIN, led.isActive());
  
}

void onLedEventStart()
{
  Serial.println("LED event start");
}

void onLedEventEnd()
{
  Serial.println("LED event stop");
}

