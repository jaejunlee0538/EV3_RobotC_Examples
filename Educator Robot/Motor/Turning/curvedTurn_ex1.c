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
	//Curved Turn hard coding version.
	//track : 0.117m, wheel diameter : 0.056m
	//Turning Raius : 0.1m, left wheel speed : 15

	float R = 0.10;
	float track = 0.117;
	short speed_left = 15;
	short speed_right = (R+track)/R * speed_left;

	float distance = R * 180.0 * (PI/180.0);
	float degrees = distance / 0.028 * (180.0/PI);

	setMotorSpeed(rightMotor, speed_right);
	moveMotorTarget(leftMotor, degrees, speed_left);

	waitUntilMotorStop(leftMotor);

}
