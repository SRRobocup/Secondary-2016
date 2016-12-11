//#include "C:\Users\Shaurya\Dropbox\Robotics2016\b\lib"
#include "common.h"
#include "libh.h"
#include "lib(i2c).c"


void obstacle( float dia)
{

	float buf = 2;//buffer
	float knob = 1.0;
	float id = dia+(2*buf);//inner diameter
	float od = (id+(Wb*2))*knob;//outer diameter
	float ra = id/od;//radius
	int op = 80;//outer power
	float ip = (op*ra)-1.5;//inner power

	turnleft(90);
	//wait1Msec(1000);
	if (SensorValue[Ports[enUSF]] >= 30)
	{

		displayTextLine(1,"dist=%d",SensorValue[Ports[enUSF]]);
		//while(SensorValue[LLight]>Lthreshhold || SensorValue[RLight]>Rthreshhold)
		while(getSensorData(enLight)>MThreshold)
		{
			motor(Rm)= ip;
			motor(Lm)= op;
		}
		while(getSensorData(enLight)>MBlack)
			//{
		wait1Msec(10);
		//}
		goStraight(6);
		turnleft(90);
	}
	else
	{
		turnright (175);
		//while(SensorValue[LLight]>Lthreshhold || SensorValue[RLight]>Rthreshhold)
		while(getSensorData(enLight)>MThreshold)
	 {
			motor[Rm]= op;   // change to Lm and Rm
			motor[Lm]= ip;
		}
		//while(SensorValue[RLight]>44)
		//{
		wait1Msec(10);
		//}
		//}

		turnright(90);
	}
}
//#define  TESTDRive


/*task main()
{

	SensorType[S2]=sensorSONAR;
	//setupSensors();
	while(1)
	{
		if(SensorValue[S2]< 8)
		{
			obstacle( 8.0 );
		}
	}
}*/
