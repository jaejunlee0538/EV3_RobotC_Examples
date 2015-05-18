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
	//Desired Values
	int deg = 180.0; //How much degrees you want the robot to turn.
	float speed = 20;	//Desired wheel speed during turnning motion.

	//Contants
	float R_wheel = 0.056 * 0.5; //radius of wheel in meters
	float track = 0.117; //length from left wheel to right wheel in meters

	//Calculation
	float rad = abs(deg) / 180.0 * PI;		//Convert degrees to radians.
	float distance = rad * (track*0.5);	//Distance each wheels should travel.
	float deg_of_wheel = distance / R_wheel * 180.0 / PI;	//Conversion from distance unit to angular unit.

	if(deg > 0)
	{
		//Left Turn. Forward(right), Backward(left)
		moveMotorTarget(leftMotor, -deg_of_wheel, -speed);
		moveMotorTarget(rightMotor, deg_of_wheel, speed);
	}
	else if(deg < 0)
	{
		//Right Turn. Forward(left), Backward(right)
		moveMotorTarget(leftMotor, deg_of_wheel, speed);
		moveMotorTarget(rightMotor, -deg_of_wheel, -speed);
	}
	else
	{
		//Don't move
		setMotorSpeed(leftMotor,0);
		setMotorSpeed(rightMotor,0);
	}
	waitUntilMotorStop(leftMotor);
	waitUntilMotorStop(rightMotor);
}