
#include "libh.h"
#include "lib(i2c).c"
#include "Obs_simple.c"
#include "caselt.c"


task main()
{

	initSensors();
	while (true)  // do not see silver
	{
		if (getSensorData(enUSF) < 8)
			obstacle(8.0);

		else
			doLT();
	}
	// evacuation

}
