
#include "lib(i2c).c"
#include "libh.h"

#include "common.h"

task main()
{

	initSensors();
	int s=1;
	turnleft2(170);
	delay(1000);
	if (getSensorData(enUSL)<500.6) //getSensorData(enUSL)
	{
		s=-1;

	}
	else
	{
		s= 1;
	}

	if(getSensorData(enIR)<850) //if(getSensorData(enIR)<711 && getSensorData(enIR)> 633)
	{
		int x = getSensorData(enIR);
		turnright2(75*s);
		delay(200);
		if(getSensorData(enIR)<1250 && getSensorData(enIR)>850) //if(getSensorData(enIR)<1041 && getSensorData(enIR)>970)
		{

			playSound(soundBlip);//diagonal
			turnright2(90*s);
		}
		else if(getSensorData(enIR)<850)
		{
			goStraight(-6);
			turnleft2(90*s);
			if(abs(x - getSensorData(enIR)) > 30)
			{
				turnleft2(75*s);
				while(getSensorData(enUSF) > 15)
				{
					motor[motorA]=50;
					motor[motorB]=50;
				}
				motor[motorA]=0;
			motor[motorB]=0;
			turnleft2(170);
			}
			else
			{
				goStraight(-70);
				goStraight(5);

				turnleft2(90*s);
				goStraight(6);
				turnright2(90*s);
			}
		}
	}
	else if(getSensorData(enIR)<1250 && getSensorData(enIR)>850) //else if(getSensorData(enIR)<1041 && getSensorData(enIR)>970)
	{
		turnright2(90*s);
		delay(1000);
		if(getSensorData(enIR)<850 && getSensorData(enIR)> 600)
		{
			playSound(soundBeepBeep);
			turnright2(180);
		}
		else
		{
			turnleft2(90*s);
			delay(200);
			while (getsensordata(enUSF)  > 15) //Us
			{
				motor[motorA]=50;
				motor[motorB]=50;
			}
			motor[motorA]=0;
			motor[motorB]=0;
			turnleft2(90);
			delay(200);
		}
	}
	else
	{
		turnleft2(90*s);
		delay(200);
		while ( getsensordata(enUSF) > 15) //Us
		{
			motor[motorA]=50;
			motor[motorB]=50;
		}
		motor[motorA]=0;
			motor[motorB]=0;
	}
	//start routine(positive)
	playSound(soundBeepBeep);
	nxtDisplayTextLine(1, "done");
	delay(20000000000000000000000000000000000000000000000000000);
}
