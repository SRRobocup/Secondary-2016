//PUT FUNCTIONS IN HERE
#include "libh.h"

// get data from sensors connected via the 2 splitters, S2 & S4
// one IR Dist is by itself
// one NXT sonar is on the splitter by itself
// all others are connected via Mindsensors i2c adaptor
//
int getSensorData(enSplit prt)
{
	char msg[6];
	tSensors link = Ports[prt];  //prt stands for port
	char reply[4];

	SensorType[link] = sensorI2CCustom9V;  //If you want to call a sensor or tell it to do something, you would say
	//Ports[and the enum]  ex: if (SensorValue[Ports[enUSF]]<80)
	memset(msg,0,6);
	memset(reply,0,4);
	msg[0] = 2;
	msg[1] = i2cID[prt];
	if (prt == enIR||prt == enUSF)
		msg[2] = 0x42;  // read command for the mindsensor IR
	else
		msg[2] = 0x54;  // read command for the mindsensors i2c adaptor

	writeI2C(link, (tByteArray)msg, (tByteArray)reply, 2);


	if (prt == enLight|| prt == enUSF)
	{// EV3 Light
		return reply[0];
	}

	else
	{
		return (reply[1]<<8  | reply[0]);   // EV3 US
	}// reply[1]*256 + reply[0]

}

void initSensors()
{
	SensorType[Lc] =  sensorColorNxtFULL;
	SensorType[Rc] =  sensorColorNxtFULL;
	short color[3] = {1, 1, 1};
	for( int i=0; i<2; i++)
	{
		getColorSensorData(Rc, colorRaw, color);
		writeDebugStreamLine("%d   %d  %d", color[0], color[1], color[2]);
		wait10Msec(1);
	}


	SensorType[Ports[enUSF]] = sensorSONAR;
	playSound(soundException);
  SensorType[Ports[enLight]] = sensorLightActive;

}

// go straight : cm > 0 : forward
void goStraight (float cm)
{

	int encoders= cm*EncoderPerCm;
	nMotorEncoder[motorA]=0;
	nMotorEncoder[motorB]=0;
#ifdef NXT
	nMotorEncoderTarget[Lm] = encoders;
	nMotorEncoderTarget [Rm] = encoders;
	if (cm < 0)
	{
		motor[Lm]=-50;
		motor[Rm]=-50;
	}
	else
	{
		motor[Lm]=50;
		motor[Rm]=50;
	}
#else
	setMotorTarget(Lm, encoders, 50);
	setMotorTarget(Rm, encoders, 50);
#endif

#ifdef NXT
	while ( !(nMotorRunState[Lm] == runStateIdle &&  nMotorRunState[Rm] == runStateIdle ))
#else
	while (getMotorRunning(Lm) || getMotorRunning(Rm))
#endif
	delay(10);

}

void turnright(float deGrees)
{
	int encoders = EncPerDeg * deGrees;
	//	displayBigTextLine(2,"%d", encoders);

#ifdef NXT
	nMotorEncoderTarget[Lm] = encoders;
	nMotorEncoderTarget [Rm] = -encoders;
	motor[Lm]=50;
	motor[Rm]=-50;

#else
	setMotorTarget(Lm, encoders, 50);
#endif

#ifdef NXT
	while ( !(nMotorRunState[Lm] == runStateIdle &&  nMotorRunState[Rm] == runStateIdle ))
#else
	while (getMotorRunning(Lm) || getMotorRunning(Rm))
#endif
	delay(10);

}


void turnleft(float deGrees)
{
	int encoders = EncPerDeg * deGrees;
	displayTextLine(2,"%d", encoders);

#ifdef NXT
	nMotorEncoderTarget[Lm] = encoders;
	nMotorEncoderTarget [Rm] = -encoders;
	motor[Lm]=-50;
	motor[Rm]=50;

#else
	setMotorTarget(Lm, encoders, 50);
#endif

#ifdef NXT
	while ( !(nMotorRunState[Lm] == runStateIdle &&  nMotorRunState[Rm] == runStateIdle ))
#else
	while (getMotorRunning(Lm) || getMotorRunning(Rm))
#endif
	delay(10);


}
void SMASH(float degrees)
{

	int direction = 1;
	if((degrees/abs(degrees)) == -1)
	{
		int direction = -1;
	}

	nMotorEncoder[motorC] = 0;
	int md = degrees * 3;
	if(direction=-1)
	{
		while(nMotorEncoder[motorC] > (md))
		{
			motor[motorC]= -50;

		}
	}
	if(direction=1)
	{
		while	(nMotorEncoder[motorC] < (md))
		{
			motor[motorC]=100;
		}
	}
}
void turnleft2(int deGrees)
{
	nMotorEncoder[motorA] = 0;
	nMotorEncoder[motorB] = 0;
	int encoders = EncPerDeg * deGrees*1.0555555555555555555555555555556;
	if(encoders/(abs(encoders)) == 1)
	{
		while (nMotorEncoder[motorB]<encoders)
		{
			motor[motorA]=-50;
			motor[motorB]=50;
		}
		motor[motorA]=0;
		motor[motorB]=0;
	}
	else if(encoders/abs(encoders) == -1)
	{
		while (nMotorEncoder[motorA]<abs(encoders))
		{
			motor[motorA]=50;
			motor[motorB]=-50;
		}
		motor[motorA]=0;
		motor[motorB]=0;
	}
}
void turnright2(int deGrees)
{
	nMotorEncoder[motorA] = 0;
	nMotorEncoder[motorB] = 0;
	int encoders = EncPerDeg * deGrees*1.0555555555555555555555555555556;
	if(encoders/abs(encoders) == 1)
	{
		while (nMotorEncoder[motorB]>-encoders)
		{
			motor[motorA]=50;
			motor[motorB]=-50;
		}
		motor[motorA]=0;
		motor[motorB]=0;
	}
	else if(encoders/abs(encoders) == -1)
	{
		while (nMotorEncoder[motorB]<abs(encoders))
		{
			motor[motorA]=-50;
			motor[motorB]=50;
		}
		motor[motorA]=0;
		motor[motorB]=0;
	}
}

//task main()
//{
//playSound(SoundBeepBeep);
// }
