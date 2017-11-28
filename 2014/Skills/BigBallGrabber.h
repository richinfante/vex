/*
Big Ball Grabber functions
Copyright 2014 Vexy^2 Masuk Robotics. All Rights Reserved.

  ____  _         ____        _ _    ____           _     _
 | __ )(_) __ _  | __ )  __ _| | |  / ___|_ __ __ _| |__ | |__   ___ _ __
 |  _ \| |/ _` | |  _ \ / _` | | | | |  _| '__/ _` | '_ \| '_ \ / _ \ '__|
 | |_) | | (_| | | |_) | (_| | | | | |_| | | | (_| | |_) | |_) |  __/ |
 |____/|_|\__, | |____/ \__,_|_|_|  \____|_|  \__,_|_.__/|_.__/ \___|_|
          |___/

 */

/**
* Holds 2 big balls in robot assuming one is on, and one is in the claw which is lowered.
* This is a task. call startHoldingBalls(), and stipHoldingBalls()
*/
task HoldBigBalls(){
	while(true)
	{
		if((getPotentiometerDegrees(bigBallP)>upLimit)){
			motor[rightBigBall] = DOWN;
			motor[leftBigBall] = DOWN;
			}else{
			motor[rightBigBall] = OFF;
			motor[leftBigBall] = OFF;
		}
	}

}

/**
* Stop Holding big balls task and make sure big ball grabbers get turned off.
*/
void stopHoldingBalls()
{
	StopTask(HoldBigBalls);
	motor[rightBigBall] = OFF;
	motor[leftBigBall] = OFF;
}


/**
* Start Holding Big balls task
*/
void startHoldingBalls()
{
	motor[rightBigBall] = OFF;
	motor[leftBigBall] = OFF;
	StartTask(HoldBigBalls);
}


/**
* Flip in direction for time
*/
void setFlip(Direction d, int time = 0)
{
	if(time == 0)
	{
		motor[leftBigBall] = -d;
		motor[rightBigBall] = -d;
	}
	else{
		motor[leftBigBall] = -d;
		motor[rightBigBall] = -d;
		wait1Msec(time);
		motor[leftBigBall] = OFF;
		motor[rightBigBall] = OFF;
	}
}

/**
* Flip in direction to degrees
*/
void flipTo(Direction d, int degrees){
	if(d == DOWN)
	{

		while(getPotentiometerDegrees(bigBallP) < degrees)
		{
			motor[leftBigBall] = UP;
			motor[rightBigBall] = UP;
		}
		motor[leftBigBall] = OFF;
		motor[rightBigBall] = OFF;
	}

	if(d == UP)
	{

		while(getPotentiometerDegrees(bigBallP) > degrees)
		{
			motor[leftBigBall] = DOWN;
			motor[rightBigBall] = DOWN;
		}
		motor[leftBigBall] = OFF;
		motor[rightBigBall] = OFF;
	}

	motor[leftBigBall] = OFF;
	motor[rightBigBall] = OFF;
}
