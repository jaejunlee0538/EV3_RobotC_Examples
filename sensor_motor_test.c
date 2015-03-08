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
/*
Check sensors through Sensor Window.
Sonar : Try blocking the front of sonar sensor
Color : Take the sensor on the white object and black object.
Touch : Press and release the button.
Gyro  : Rotate the robot.
*/
	resetGyro(gyroSensor);

	displayBigTextLine(2,"Hello World");

	/*
	Go forward
	*/
	while(!getButtonPress(buttonEnter));
	wait1Msec(500);
	setMotorSpeed(leftMotor, 30);
	setMotorSpeed(rightMotor, 30);
	setLEDColor(ledRed);

	/*
	Go backward
	*/
	while(!getButtonPress(buttonEnter));
	wait1Msec(500);
	setMotorSpeed(leftMotor, -30);
	setMotorSpeed(rightMotor, -30);
	setLEDColor(ledRedFlash);

	/*
	Turn left
	*/
	while(!getButtonPress(buttonEnter));
	wait1Msec(500);
	setMotorSpeed(leftMotor, -30);
	setMotorSpeed(rightMotor, 30);
	setLEDColor(ledGreenPulse);

	/*
	Turn right
	*/
	while(!getButtonPress(buttonEnter));
	wait1Msec(500);
	setMotorSpeed(leftMotor, 30);
	setMotorSpeed(rightMotor, -30);
	setLEDColor(ledOrange);

	/*
	Terminating Sound
	*/
	while(!getButtonPress(buttonEnter));
	setMotorSpeed(leftMotor, 0);
	setMotorSpeed(rightMotor, 0);
	playSoundFile("Dog growl");
	while(bSoundActive);
	setLEDColor(ledRedFlash);

}
