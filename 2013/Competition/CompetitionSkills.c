#pragma systemFile
#ifdef compileCheck
#else
#error "Compile from Header!"
#endif
void doSkills(){
	if(SensorValue[in1] / 275 == 0)
	{
		//do nothing because someone didnt plug in the backup battery.
	}
	else
	{











	lowerArm();
	intakeRelease();
	intakeSp(-127);
	drive(30,750);
	drive(127,2600);
	drive(-127,870);
	intakeSp(0);
	liftArm();
	drive(127,235);
	intakeSp(-127);
	wait1Msec(1000);
	intakeSp(0);

	drive(-127,2500);
	waitForUser();

	drive(127,2500);
	intakeSp(-127);
	drive(-127,2500);

	lowerArm();

	waitForUser();
	intakeSp(-127);
	drive(127,2400);
	drive(-127,2400);
	intakeSp(0);

	waitForUser();
	liftArm();
	drive(127,2400);
	intakeSp(-127);
	wait1Msec(1500);
	intakeSp(0);
	}

}
