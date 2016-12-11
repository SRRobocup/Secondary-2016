
#include "common.h"
#include "libh.h"
#include "lib(i2c).c"

void Box2()
{
	int n=1;
	turnright(88);
	delay(500);
nxtDisplayTextLine(1, "%d", SensorValue(S2))
	if(SensorValue[S2]>=30)
	{
		while(n<=3)
		{
		while(getSensorData(enUSL)<=120)
		{
			motor[Rm]=motor[Lm]=30;
		}
		//else
	 //{
		// turnleft(88);
	 //  goStraight(1);
	 //  turnright(88);
	 //}
		if (getSensorData(enUSL)>120)
		{
			motor[Lm]=motor[Rm]=0;
			playSound(soundBlip);
			delay(500);
				goStraight(7);
			 turnleft(90);
			 goStraight(20);
		}
		n++;
	}
	else
	{
		turnleft(178);
			while(n<=3)
		{
		while(getSensorData(enUSR)<=120)
		{
			motor[Rm]=motor[Lm]=30;
		}
		//else
	 //{
		// turnleft(88);
	 //  goStraight(1);
	 //  turnright(88);
	 //}
		if (getSensorData(enUSR)>120)
		{
			motor[Lm]=motor[Rm]=0;
			playSound(soundBlip);
			delay(500);
				goStraight(7);
			 turnright(90);
			 goStraight(20);
		}
		n++;
	}

	}
}
task main()
{
 SensorType[S2]=sensorSONAR;

 while (1)
 {
    nxtDisplayTextLine(1, "USL: %d", getSensorData(enUSL))
   if (SensorValue[S2]<=8)
   {
     playSound(soundBlip);
     Box2();
   }
 }

}
