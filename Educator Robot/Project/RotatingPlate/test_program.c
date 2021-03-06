#pragma config(Sensor, S1,     touchSensor,    sensorEV3_Touch)
#pragma config(Sensor, S2,     gyroSensor,     sensorEV3_Gyro)
#pragma config(Sensor, S3,     colorSensor,    sensorEV3_Color)
#pragma config(Sensor, S4,     sonarSensor,    sensorEV3_Ultrasonic)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#include "../Termproject1/robot_motion.h"

void display_current_angle(void)
{
	if(time1[T1] % 200)
	{
		eraseDisplay();
		displayBigTextLine(1,"%d deg", getGyroDegrees(gyroSensor));
	}
}

long low_pass_filter(long current_data)
{
	static bool first_run = true;
	static float filtered = 0;
	const static float alpha = 0.01;
	if(first_run)
	{
		filtered = current_data;
		first_run = false;
	}
	else
	{
		filtered = (1.0 - alpha)*filtered + alpha*current_data;
	}

	return filtered;
}

task main()
{

	resetGyro(gyroSensor);
	wait1Msec(4000);



	robotmotion_move_forward(25);
	while(true)
	{
		if(getColorName(colorSensor) == colorRed)
		{
			break;
		}
		display_current_angle();
	}
	robotmotion_stop_left_right_motor();

	//wait untill the plate starts rotating and stopping.
	wait1Msec(200);
	long gyro_rate_filtered = low_pass_filter(getGyroRate(gyroSensor));
	for(int i=0;i<10;i++)
	{
		gyro_rate_filtered = low_pass_filter(getGyroRate(gyroSensor));
	}
	while(true)
	{
		gyro_rate_filtered = low_pass_filter(getGyroRate(gyroSensor));
		if(abs(gyro_rate_filtered) > 40)
			break;
	}
	while(true)
	{
		gyro_rate_filtered = low_pass_filter(getGyroRate(gyroSensor));
		if(gyro_rate_filtered == 0)
			break;
	}

	//Gyro Rate Recording
	/*
	long rate = 0;
	long file = fileOpenWrite("gyro_rate.txt");
	long t = 0;
	clearTimer(T2);
	clearTimer(T2);
	while(getButtonPress(buttonEnter)==0)
	{
		t = time1[T2];
		rate = getGyroRate(gyroSensor);
		fileWriteFloat(file, t);
		fileWriteFloat(file,getGyroRate(gyroSensor));
		fileWriteFloat(file, low_pass_filter(rate));

	}
	fileClose(file);
	while(getButtonPress(buttonEnter)==1);
	*/

	while(getGyroRate(gyroSensor) == 0);
	while(getGyroRate(gyroSensor) != 0);


	//rotate to the correct direction
	long current_angle = (getGyroDegrees(gyroSensor)+360)%360;//normalize in range of 0~360
	long desired_angle = 90;
	long desired_rotation = (desired_angle - current_angle);

	if(abs(desired_rotation) > 180)
	{
		desired_rotation = (360 - current_angle) + desired_angle;
	}

	displayBigTextLine(4,"=>%d deg", desired_rotation);

	robotmotion_point_turn(20, desired_rotation, true);

	robotmotion_move_forward(20,40, true);
}
