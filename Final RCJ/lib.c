//PUT FUNCTIONS IN HERE

#ifndef _LIBH_
#include "libh.h"
#endif

#ifndef _LIBC__
#define _LIBC_



//=======================================================

// get data from sensors connected via the 2 splitters, S2 & S4
// one IR Dist is by itself
// one NXT sonar is on the splitter by itserf
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
	if (prt == enIR)
		msg[2] = 0x42;  // read command for the mindsensor IR
	else
		msg[2] = 0x54;  // read command for the mindsensors i2c adaptor

	writeI2C(link, (tByteArray)msg, (tByteArray)reply, 2);
	writeDebugStreamLine("%d  %d ", reply[0], reply[1]);

	if (prt == enLight)
	{// EV3 Light
		return reply[0];
	}

	else
	{
		return (reply[1]<<8  | reply[0]);   // EV3 US
	}// reply[1]*256 + reply[0]

}


//================================================================


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

#endif
