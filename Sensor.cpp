
#include "WHSR.h"

void WHSR::InitSensors(void)
{
	pinMode(LineFollower_LED, OUTPUT);
	digitalWrite(LineFollower_LED, LED_Sensor_Pegel_Off);
	
	pinMode(ACS_IrLED, OUTPUT);
	digitalWrite(ACS_IrLED, LED_Sensor_Pegel_Off);
}

/* ******************************************************************************************
 * 
 * Diese Funktionen beschäftigen sich mit dem Einlesen
 * der Batteriespannung und der Referenzspannung
 * 
 * ****************************************************************************************** */

unsigned int WHSR::readReferenz(void)
{
	DoCheckADCMode(Referenz);
	return mySensorValues[Referenz];
}

float WHSR::readVref(void)
{
	float result = (InternalReferenceVoltage * (1023.0 / readReferenz())) / 1000;
	
	DebugSerial_print(" Vref: ");
	DebugSerial_print(result);
	DebugSerial_print(F("; "));
	
	return result;
}

float WHSR::readBattery(void)
{
	float vref = readVref();
	
	DoCheckADCMode(Batterie);
	float VAdc = (vref/1023) * mySensorValues[Batterie];
	float result = VAdc * ((ResistorOben + ResistorUnten)/ResistorUnten); 
	
	DebugSerial_print(F(" B1: "));
	DebugSerial_print(mySensorValues[Batterie]);
	DebugSerial_print(F(" B2: "));
	DebugSerial_print(VAdc);
	DebugSerial_print(F(" ->: "));
	DebugSerial_print(result);
	DebugSerial_print(F("; "));
	
	return (result);
}

/* ******************************************************************************************
 * 
 * Diese Funktionen lesen den Lienienfolger aus
 * 
 * ****************************************************************************************** */

void WHSR::readLinesensor(int *data, unsigned char LightStatus)
{
	if(LightStatus == LEDOn)
	{
		setFrontLED(LightStatus);
		delay(1);
	}
	
	readLinesensor(data);

	setFrontLED(LEDOff);
}
void WHSR::readLinesensor(int *data)
{
	DoCheckADCMode(LineFollower_Left);
	DoCheckADCMode(LineFollower_Right);
	
	data[Sensor_Left] = mySensorValues[LineFollower_Left];
	data[Sensor_Right] = mySensorValues[LineFollower_Right];
}

unsigned int WHSR::readLinesensor(char Side, unsigned char LightStatus)
{
	int data[2];
	readLinesensor(*data, LightStatus);
		
	if(Side == Sensor_Left)
		return mySensorValues[LineFollower_Left];
	else
		return mySensorValues[LineFollower_Right];
}

unsigned int WHSR::readLinesensor(char Side)
{
	int data[2];
	readLinesensor(*data);
		
	if(Side == Sensor_Left)
		return mySensorValues[LineFollower_Left];
	else
		return mySensorValues[LineFollower_Right];
}

/* ******************************************************************************************
 * 
 * Diese Funktionen lesen den ACS aus (Kolisionsfrühwarnung)
 * 
 * ****************************************************************************************** */

void WHSR::readACS(int *data, unsigned char LightStatus)
{
	if(LightStatus == LEDOn)
	{
		setIrLEDs(LightStatus);
		delay(100);
	}
	
	readACS(data);
	
	setIrLEDs(LEDOff);
}

void WHSR::readACS(int *data)
{	
	DoCheckADCMode(ACS_Left);
	DoCheckADCMode(ACS_Right);
	
	data[Sensor_Left] = mySensorValues[ACS_Left];
	data[Sensor_Right] = mySensorValues[ACS_Right];
}


unsigned int WHSR::readACS(char Side, unsigned char LightStatus)
{
	int data[2];
	readACS(*data, LightStatus);
		
	if(Side == Sensor_Left)
		return mySensorValues[ACS_Left];
	else
		return mySensorValues[ACS_Right];
}

unsigned int WHSR::readACS(char Side)
{	
	int data[2];
	readACS(*data);
		
	if(Side == Sensor_Left)
		return mySensorValues[ACS_Left];
	else
		return mySensorValues[ACS_Right];
}


/* ******************************************************************************************
 * 
 * Diese Funktionen lesen die beiden Lichtsensoren aus
 * 
 * ****************************************************************************************** */

void WHSR::readAmbientLight(int *data)
{
	DoCheckADCMode(LDR_Left);
	DoCheckADCMode(LDR_Right);
	
	data[Sensor_Left] = mySensorValues[LDR_Left];
	data[Sensor_Right] = mySensorValues[LDR_Right];
}

unsigned int WHSR::readAmbientLight(char Side)
{
	if(Side == Sensor_Left)
	{
		DoCheckADCMode(LDR_Left);
		return mySensorValues[LDR_Left];
	}
	else
	{
		DoCheckADCMode(LDR_Right);
		return mySensorValues[LDR_Right];
	}
}
