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
	setSoundVolume(20);
	while(true)
	{
		long color = getColorName(colorSensor);
		switch(color)
		{
			case colorNone:
			break;

			case colorBlack:
			playSoundFile("Black");
			break;

			case colorBlue:
			playSoundFile("Blue");
			break;

			case colorGreen:
			playSoundFile("Green");
			break;

			case colorYellow:
			playSoundFile("Yellow");
			break;

			case colorRed:
			playSoundFile("Red");

			break;

			case colorWhite:
			playSoundFile("White");
			break;

			case colorBrown:
			playSoundFile("Brown");
			break;
		}
		while(bSoundActive);

		//wait 500ms
		wait10Msec(50);

	}
}
