
#include "lib(i2c).c"

task main()
{
	initSensors();

	playSound(soundBeepBeep);
	//wait10Msec(1000);
	while(true)
	{

		short color[3] = {1, 1, 1};
		getColorSensorData(Rc, colorRaw,color);
		float ratio = ((float)color[1]/(float) color[2]);
		if(ratio > 1.19)
		{
			nxtDisplayBigTextLine(2,"GREEN");
			nxtDisplayBigTextLine(1, "%f", ratio);
		}
	}
}
