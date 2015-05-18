#pragma config(Sensor, S1,     touchSensor,    sensorEV3_Touch)
#pragma config(Sensor, S2,     gyroSensor,     sensorEV3_Gyro)
#pragma config(Sensor, S3,     colorSensor,    sensorEV3_Color)
#pragma config(Sensor, S4,     sonarSensor,    sensorEV3_Ultrasonic)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

void stop_left_right_motor()
{
	setMotorSpeed(leftMotor, 0);
	setMotorSpeed(rightMotor, 0);
}

unsigned int motor_stop_duration = 0;
task task_left_right_motor_stop()
{
	clearTimer(T4);
	while(time1[T4] < motor_stop_duration)
	{
	}

	stop_left_right_motor();
}

void steering_robot(int steering, int motor_power, unsigned int duration_ms=0, TMotorBrakeModes brake=motorBrake)
{
	stopTask(task_left_right_motor_stop);

	if(getMotorBrakeMode(leftMotor)!=motorBrake)
		setMotorBrakeMode(leftMotor, motorBrake);
	if(getMotorBrakeMode(rightMotor)!=motorBrake)
		setMotorBrakeMode(rightMotor, motorBrake);

	int left_motor_power, right_motor_power;

	if(abs(motor_power) > 100)
		motor_power = sgn(motor_power)*100;
	if(abs(steering) > 100)
		steering = sgn(steering)*100;	//limitting steering within -100~100

	if(steering > 0)
	{
		left_motor_power = motor_power;
		right_motor_power = motor_power * (1 - steering*2/100.0);
	}
	else if(steering < 0)
	{
		left_motor_power = motor_power * (1 + steering*2/100.0);
		right_motor_power = motor_power;
	}
	else
	{
		left_motor_power = motor_power;
		right_motor_power = motor_power;
	}

	setMotorSpeed(leftMotor, left_motor_power);
	setMotorSpeed(rightMotor, right_motor_power);

	motor_stop_duration = duration_ms;
	if(duration_ms > 0)
	{
		startTask(task_left_right_motor_stop);
	}
}

task main()
{
	steering_robot(30, 60);
	wait1Msec(1000);
	steering_robot(-30, 60);
	while(1);
}
