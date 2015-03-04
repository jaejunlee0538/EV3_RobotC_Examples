#pragma config(Sensor, S1,     touchSensor,    sensorEV3_Touch)
#pragma config(Sensor, S2,     gyroSensor,     sensorEV3_Gyro)
#pragma config(Sensor, S3,     colorSensor,    sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S4,     sonarSensor,    sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,           ,             tmotorEV3_Large, openLoop)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)
#pragma config(Motor,  motorD,           ,             tmotorEV3_Large, openLoop)

task main()
{
	const float SAFE_DISTANCE = 20.0;

	while(true){
		float distance = getUSDistance(sonarSensor);
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
		wait10Msec(10);
	}
}
