#pragma config(Sensor, S1,     touchSensor,    sensorEV3_Touch)
#pragma config(Sensor, S2,     gyroSensor,     sensorEV3_Gyro)
#pragma config(Sensor, S3,     colorSensor,    sensorEV3_Color)
#pragma config(Sensor, S4,     sonarSensor,    sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,           ,             tmotorEV3_Large, openLoop)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)
#pragma config(Motor,  motorD,           ,             tmotorEV3_Large, openLoop)

task main()
{
	//Point Turn hard coding version.
	//track : 0.117m, wheel diameter : 0.056m
	//left turn 180deg.
	float distance = (0.117/2) * 180.0 * (PI/180.0);
	float degrees = (distance / 0.028) * (180.0/PI);

	moveMotorTarget(leftMotor, -degrees, -20);
	moveMotorTarget(rightMotor, degrees, 20);

	waitUntilMotorStop(leftMotor);
	waitUntilMotorStop(rightMotor);
}
