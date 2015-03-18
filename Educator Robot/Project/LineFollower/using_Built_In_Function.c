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

/*
(Primary , Second)
50, 10 : I think it's ok. But sometime at a curve, it went out of the track.

100, 40 : Unstable. It couldn't handle curve at all.

80, 40 : Didn't work at curve. Turning speed is too low.

80, 20 : Didn't work at curve. Turning speed is low.
				 And I think proceeding speed is too high considering the track size and the curvature.

60, 10 : Seems ok. Almost similar to the result of (50,10).

70, 15 : Didn't work at the curve.
				 If the angle between the proceeding direction and the track direction is higher than some value,
				 the robot went out the track.
				 When speed is low, it can cover stiff curve. But otherwise it cannot.

*/
	while(1)
	{
		lineTrackRight(colorSensor, 50, 70,15);
	}
}
