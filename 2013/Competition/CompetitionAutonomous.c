#pragma systemFile
#ifdef compileCheck
#else
#error "Compile from Header!"
#endif
typedef enum{LEFT = 1, RIGHT = 2, NONE = 0}Side;

int flag;

void execute(tMotor excmotor,int speed, int time)
{
motor[excmotor]= speed;
wait1Msec(time);
motor[excmotor] = 0;
}

/**
*Stop the drive
*/
void stopDrive()
{
	motor[rightMotor]=0;
	motor[leftMotor]=0;
}

/**
* Wait for the user to press the autonomous button.
*/
void waitForUser(){
	while(SensorValue[auto_wait]!=1){}
}

/**
* Lift Arm.
*/
void liftArm(){
	motor[ARM_1]=127;
	motor[ARM_2]=127;
	while(SensorValue[LIMIT_UP]!=1 && SensorValue[LIMIT_UP_1]!=1){}
	motor[ARM_1]=0;
	motor[ARM_2]=0;
}

/**
* Set arm to lowering if it won't break
*/
void maybyeLowerArmNEXP(){
	if(SensorValue[LIMIT_DOWN]!=1){
		motor[ARM_1]=-127;
		motor[ARM_2]=-127;
	}
	else{
		motor[ARM_1]=0;
		motor[ARM_2]=0;
	}
}

/**
* Lower Arm.
*/
void lowerArm(){
	motor[ARM_1]=-127;
	motor[ARM_2]=-127;
	while(SensorValue[LIMIT_DOWN]!=1){}
	motor[ARM_1]=0;
	motor[ARM_2]=0;
}


/**
* Pre-Autonomous code -- clear encoders, etc.
*/
void pre_auton(){
	clearDebugStream();
}

void drive(int speed, int time)
{
	motor[rightMotor] = speed;
	motor[leftMotor] = speed;
	wait1Msec(time);
	stopDrive();
}



void drive(int speedL, int speedR, int time)
{
	motor[rightMotor] = speedR;
	motor[leftMotor] = speedL;
	wait1Msec(time);
	stopDrive();
}
/**
*	Non-Expiring drive.
*/
void driveNEXP(int speed)
{
	motor[rightMotor] = speed;
	motor[leftMotor] = speed;
}


/**
* Move Intake
*/
void intakeSp(int speed)
{
	motor[INTAKE]= speed;
}


/**
*Release the Arm
*/
void intakeRelease()
{
	intakeSp(127);
	wait1Msec(750);
}

/**
* Score into the trough from the square
*/
void scoreFromSquare(bool returns)
{

	//	intakeRelease();
	intakeSp(0);
	liftArm();
	drive(127,1700);
	intakeSp(-127);
	wait1Msec(1000);
	intakeSp(0);

	if(returns)
	{

		drive(-127,2500);
	}
	else
	{
		drive(-127,2500);
	}
}

/**
* Grab the yellow. Score it? Return and lower? Return then lower?
*/
void grabYellowFromSquare(bool shouldScore, bool lowerArmOnRetreat, bool lowersAtAll)
{
	lowerArm();
	intakeRelease();
	intakeSp(-127);
	drive(30,750);
	drive(127,2500);
	if(lowersAtAll)
	{
		if(shouldScore)
		{
			drive(-127,870);
			intakeSp(0);
			liftArm();
			drive(127,330);
			intakeSp(-127);
			wait1Msec(1000);
			intakeSp(0);
			if(!lowerArmOnRetreat)
			{
				drive(-127,2500);
			}
			else
			{
				ClearTimer(T1);
				while(time1[T1]<2500)
				{
					driveNEXP(-127);
					maybyeLowerArmNEXP();
				}
				maybyeLowerArmNEXP();
				driveNEXP(0);
			}
		}
	}
}




/**
* Grab the center yellow bag from the center of your side
*/
void grabMiddleYellow(bool scores, Side side)
{
	waitForUser();
	intakeSp(-127);
	drive(127,2400);
	if(!scores)
	{
		drive(-127,2200);
	}
	else
	{
		drive(-127,500);
		drive(127,1200);
		if(side == LEFT)
		{

		}
		else if(side== RIGHT)
		{

		}
	}
	intakeSp(0);
}

int getAutonomousFlag()
{
	if(SensorValue[auto_01]==1)
	{
		return 1;
	}
	if(SensorValue[auto_02]==1)
	{
		return 2;
	}
	if(SensorValue[auto_03]==1)
	{
		return 3;
	}
	if(SensorValue[auto_04]==1)
	{
		return 4;
	}
	if(SensorValue[auto_05]==1)
	{
		return 5;
	}
	if(SensorValue[auto_06]==1)
	{
		return 6;
	}
	return 0;
}
void doAutonomous(){
	if(SensorValue[in1] / 275 == 0)
	{
		//do nothing because someone didnt plug in the backup battery.
	}
	else
	{
		flag = getAutonomousFlag();
		writeDebugStreamLine("AutoSelect:%d",flag);
		switch(flag)
		{
		case 1:
			//'default' autonomous
			lowerArm();
			intakeRelease();
			intakeSp(-127);
			grabYellowFromSquare(true,true,true);
			lowerArm();
			grabMiddleYellow(false,NONE);
			break;
		case 2:
			lowerArm();
			grabMiddleYellow(false, NONE);
			break;
		case 3:
			grabMiddleYellow(true,  LEFT);
			break;
		case 4:
			scoreFromSquare(true);
			break;
		case 5:
			intakeRelease();
			intakeSp(-127);
			wait10Msec(1000);
			intakeSp(0);
			break;
		case 6:
			break;

		}
	}

	stopDrive();
	allMotorsOff();
	lowerArm();
}
