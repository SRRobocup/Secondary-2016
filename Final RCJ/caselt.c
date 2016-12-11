#pragma DebuggerWindows ("debugStream")

#ifndef _LIBH_
#include "libh.h"
#endif

#include "lib(i2c).c"


enum enColorType {enWhite = 0, enBlack = 1, enGreen = 2};
enum enDirection {enGoRight = 0, enGoLeft = 1};

const int frontPower = 40;
const int backPower = -30;
int copyVal;

// return:
// enGreen | enBlack | enWhite
//

enColorType ogCookedData()
{
	enColorType enColor;
	switch (SensorValue[S1])
	{
	case 1: enColor = enBlack; break;
	case 3: enColor = enGreen; break;
	case 6: enColor = enWhite; break;
	}
	return enColor;
}

enColorType getSensorColor(int threshold, int typeOfSensor)//thresh sensor
{
	//playSound(soundBlip);
	short color[3]={1,1,1};
	float ratio;
	enColorType sensorcolor;
	getColorSensorData(typeOfSensor, colorRaw, color);
	if(color[1] == 0 || color[2] == 0)
	{
		writeDebugStreamLine("%d   %d  %d", color[0], color[1], color[2]);
		wait10Msec(1);
	}

	ratio =((float)color[1]/(float)color[2]);

	if (ratio > 1.4)//if green
	{
		sensorcolor = enGreen;
	}
	else//if not green
	{
		if(color[2] > threshold)//white
		{
			sensorcolor = enWhite;
		}
		else// black
		{
			sensorcolor = enBlack;
		}
	}
	//nxtDisplayBigTextLine(1,"%d",sensorcolorL);
	return sensorcolor;
}

enColorType getLightValueForColor(int threshold)
{
	enColorType lightval = enBlack;
	int data = getSensorData(enLight);
	if(data > threshold)
	{
		lightval = enWhite;
	}

	return lightval;
}

void goUntilNoGreen( enColorType colorValue, int threshold, int sensor)
{
	while(colorValue == enGreen)
	{
		motor[Lm] = motor[Rm] = 30;
		colorValue = getSensorColor(threshold, sensor);
	}
}

void onSensorSeeGreen(enDirection direction)
{
	playSound(soundFastUpwardTones);
	int threshold = RThreshold;
	int sensor = Rc;
	if( direction == enGoLeft)
	{
		threshold = LThreshold;
		sensor = Lc;
		playSound(soundBeepBeep);
	}

	enColorType checkValue = getSensorColor(threshold, sensor);
	goUntilNoGreen(checkValue, threshold, sensor);
	motor[Lm] = motor[Rm] = 0;
	wait10Msec(200);
	checkValue = getSensorColor(threshold, sensor);
	if( checkValue == enBlack)
	{
		playSound(soundDownwardTones);
		goStraight(3.0);
		int rpower = -30;
		int lpower = 30;
		if( direction == enGoRight)
		{
			turnright(30);
		}
		else
		{
			turnleft(30);
			rpower *= -1;
			lpower *= -1;
		}
		while(getSensorData(enLight)> MThreshold)
		{
			motor[Rm] = rpower;
			motor[Lm] = lpower;
		}

		if( direction == enGoRight)
		{
			turnright(8);
		}
		else
		{
			turnleft(8);
		}
		checkValue = getSensorColor(threshold, sensor);
		goUntilNoGreen(checkValue, threshold, sensor);
	}
	else if( checkValue == enWhite)//if see white
	{
		playSound(soundBeepBeep);
	}

}

int ZigZag(int sensor)
{
	int err, currentValue, power;
	short color[3] = {1, 1, 1};
	if(sensor == Lc)
	{
		getColorSensorData(Lc, colorRaw, color);
		currentValue = color[2];
		err = LWhite - currentValue;
		power = frontPower - err;

	}

	if(sensor == Rc)
	{
		getColorSensorData(Rc, colorRaw, color);
		currentValue = color[2];
		err = RWhite - currentValue;
		power = frontPower - err;
	}
	if(power < -100)
	{
		power = -100;
	}
	return power;

}



void lineTrace(int val)
{
	switch (val)
	{
	case 1: int newPowerRight = ZigZag(Rc); motor[Lm] = frontPower; motor[Rm] = backPower; copyVal = val; break;
	case 10: motor[Lm] = motor[Rm] = frontPower; break;
	case 100: int newPowerLeft = ZigZag(Lc); motor[Lm] = backPower; motor[Rm] = frontPower; copyVal = val; break;

	}
	writeDebugStreamLine("%d", val);

}


/*

val == 001  | 000 | 010 | 100
middle "NEVER" == enGreen (2)
enBlack == 1
enWhite == 0
*/
void doLT()
{
	enColorType  left = getSensorColor(LThreshold, Lc);
	enColorType  right = getSensorColor(RThreshold, Rc);
	enColorType middle = getLightValueForColor(MThreshold);
	int val= (100*left)+ (10*middle) + (right);

	if(val == 101)
	{
		playSound(soundBlip)
		val = copyVal;
	}

	switch (val)
	{
	case 200: case 201: case 210: case 211: onSensorSeeGreen(enGoLeft); break;
	case 2: case 12: case 102: case 112: onSensorSeeGreen(enGoRight); break;
	case 110: case 11: case 111: case 000:  motor[Lm] = motor[Rm] = 40; break;
	case 101: playSound(soundBlip);/* int rightPower = ZigZag(Rm); int leftPower = ZigZag(Lm); nxtDisplayTextLine(1, "YOU'RE DOING SOMETHING WRONG"); motor[Rm] = rightPower; motor[Lm] = leftPower; */ break;
	default: lineTrace(val); break;

	}
	writeDebugStreamLine("%d", val);

}
task main()
{
	initSensors();
	while(true)
	{
		doLT();
		motor[motorC] = 0;
	}
}
