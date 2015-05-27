## Rotating Plate Mission

1. robot start to move forward untill it detects red line on the plate.

2. Robot must wait until the plate starts rotating and then stops completely.

3. After the plate stops, robot should rotate it's body so that it can head for right direction.

4. Move forward and escape the plate.

![](https://github.com/jaejunlee0538/EV3_RobotC_Examples/blob/master/Educator Robot/Project/RotatingPlate/rotating_plate_mission.jpg)


#### Waiting for the plate rotating and stopping

You can use gyro sensor to recognize current state of the plate, rotating or static.

One naive approach is this.

This approach always failed. 

```C
	while(getGyroRate(gyroSensor) == 0); //block while the plate is static
	while(getGyroRate(gyroSensor) != 0); //block while the plate is not static
```

Another method something like this. 
I introduced a low-pass filter. 
And I used a threshold `40` for recognizing rotating of the plate. 
***But as this threshold is hard coded value, it cannot be applied to the case of lower speed.***

```C
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
  
	//...main routine
	wait1Msec(200);
	long gyro_rate_filtered = low_pass_filter(getGyroRate(gyroSensor));
	for(int i=0;i<10;i++)
	{
		gyro_rate_filtered = low_pass_filter(getGyroRate(gyroSensor));
	}
	while(true) //wait until the plate starts rotating
	{
		gyro_rate_filtered = low_pass_filter(getGyroRate(gyroSensor));
		if(abs(gyro_rate_filtered) > 40)
			break;
	}
	while(true) //wait until the plate becomes static
	{
		gyro_rate_filtered = low_pass_filter(getGyroRate(gyroSensor));
		if(gyro_rate_filtered == 0)
			break;
	}
```

I found the ***hard-coded*** threshold by logging gyro sensor data.
By activating the following code and deactivating `//wait untill the plate starts rotating and stopping.` part, you can record the raw sensor data.

``` C
	//Gyro Rate Recording
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
	
```

#### Gyro Rate Sensor Data
The plate was rotated by EV3 Brick.

``` C
	moveMotorTarget(actuator, rotating_deg, sgn(rotating_deg)*30);
	waitUntilMotorStop(actuator);
```

![](https://github.com/jaejunlee0538/EV3_RobotC_Examples/blob/master/Educator Robot/Project/RotatingPlate/gyro_rate_log.jpg)

