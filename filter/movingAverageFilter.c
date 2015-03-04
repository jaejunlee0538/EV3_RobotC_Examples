#pragma config(Sensor, S1,     touchSensor,    sensorEV3_Touch)
#pragma config(Sensor, S2,     gyroSensor,     sensorEV3_Gyro)
#pragma config(Sensor, S3,     colorSensor,    sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S4,     sonarSensor,    sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,           ,             tmotorEV3_Large, openLoop)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)
#pragma config(Motor,  motorD,           ,             tmotorEV3_Large, openLoop)


/*
movingAverageFilter

Moving average filter is a variant of average filter.
while average filter uses the whole data for calculating an average,
moving average filter,specifically N moving average filter, uses only latest N data.
Because of this difference, moving average filter is more responsive than average filter.
But in other words, it is more unstable.
But the thing is you can compromise between responsibility and stability by manipulating a parameter.

The only parameter you can play with in movingAverageFilter is N_data.
N_data is about how many data you will use for calulating average.

#See what happens when you give 1, 20 for N_data#
The bigger N_data is, the more stable to sensor noise.
But the system becomes less reponsive to change of sensor value.
*/
float movingAverageFilter(float data)
{
	const static int N_data = 1;

	static unsigned int count = 0;
	static float filtered_data = 0.0;
	static float data_array[N_data];

	if(count < N_data)
	{
		filtered_data = (count * filtered_data + data) / ++count;
		data_array[count-1] = data;
	}
	else{
		filtered_data = (N_data * filtered_data - data_array[0] + data) / N_data;

		//shift data array, excepting an oldest data, to 1 left.
		for(int i=1;i<N_data;i++)
		{
			data_array[i-1] = data_array[i];
		}

		data_array[N_data-1] = data;
	}
	return filtered_data;
}


task main()
{
	const float SAFE_DISTANCE = 20.0;

	while(true){
		float distance = getUSDistance(sonarSensor);
		wait10Msec(10);
		distance = movingAverageFilter(distance);
		int speed = 0;

		speed =  3.0 * (distance - SAFE_DISTANCE);

		//Bounding speed input.
		if(speed > 100)
		{
			speed = 100;
		}
		else if(speed < -100)
		{
			speed = -100;
		}
		setMotorSpeed(leftMotor, speed);
		setMotorSpeed(rightMotor, speed);
		writeDebugStreamLine("%f",distance);
	}
}
