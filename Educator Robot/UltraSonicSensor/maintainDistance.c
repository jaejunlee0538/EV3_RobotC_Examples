#pragma config(Sensor, S1,     touchSensor,    sensorEV3_Touch)
#pragma config(Sensor, S2,     gyroSensor,     sensorEV3_Gyro)
#pragma config(Sensor, S3,     colorSensor,    sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S4,     sonarSensor,    sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,           ,             tmotorEV3_Large, openLoop)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)
#pragma config(Motor,  motorD,           ,             tmotorEV3_Large, openLoop)

#define SAFE_DISTANCE  20.0

int getSpeed1(float distance)
{
	if(distance > SAFE_DISTANCE)
	{
		return 30;
	}
	else if(distance < SAFE_DISTANCE)
	{
		return -30;
	}
	else
	{
		return 0;
	}
}

int getSpeed2(float distance)
{
	int speed =  distance - SAFE_DISTANCE;

	//Bounding speed input.
	if(speed > 100)
	{
		speed = 100;
	}
	else if(speed < -100)
	{
		speed = -100;
	}

	return speed;
}

int getSpeed3(float distance)
{
		int speed =  4.0 * (distance - SAFE_DISTANCE);

		//Bounding speed input.
		if(speed > 100)
		{
			speed = 100;
		}
		else if(speed < -100)
		{
			speed = -100;
		}

		return speed;
}

task main()
{

	while(true){
		float distance = getUSDistance(sonarSensor);

		if(distance > 250)
		{
			setMotorSpeed(leftMotor, 0);
			setMotorSpeed(rightMotor, 0);
		}
		else{
			int speed = getSpeed3(distance);

			setMotorSpeed(leftMotor, speed);
			setMotorSpeed(rightMotor, speed);
		}
	}
}
