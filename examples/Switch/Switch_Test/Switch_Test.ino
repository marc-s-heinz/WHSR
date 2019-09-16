
#include <WHSR.h>

WHSR robo = WHSR();

void setup()
{
	robo.Init();
	
	Serial.println(F("Switch Test"));
}

void loop()
{
  Serial.println(robo.readSwitches(), BIN);
  delay(100);
}
