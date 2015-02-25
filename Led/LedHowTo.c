task main()
{
	/*
	If you want to know what colors EV3 can express,
	go to the definition of TEV3LEDPatterns.
	*/
  for(int i=0;i<10;i++)
  {
  	setLEDColor(i);
  	wait1Msec(1000);
  }

}
