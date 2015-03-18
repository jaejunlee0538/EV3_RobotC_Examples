#pragma config(Sensor, S1,     touchSensor,    sensorEV3_Touch)
#pragma config(Sensor, S2,     gyroSensor,     sensorEV3_Gyro)
#pragma config(Sensor, S3,     colorSensor,    sensorEV3_Color)
#pragma config(Sensor, S4,     sonarSensor,    sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,           ,             tmotorEV3_Large, openLoop)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)
#pragma config(Motor,  motorD,           ,             tmotorEV3_Large, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	float distance;
	while(true)
	{
		/*
		Measuring distance to front object in cm unit.
		*/
		distance = getUSDistance(sonarSensor);

		if(distance < 15.0){
			/*
			If object comes in range of collision,
			push sound command to Queue by calling playSound function.
			*/
			if(bSoundQueueAvailable){
				playSound(soundBeepBeep);
			}
		}
		else{
			/*
			Once object is out of collision range,
			clear sound Queue immediately.
			*/
			clearSounds();
		}
	}
}