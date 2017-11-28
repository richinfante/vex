/**

___       _                       _           _   __  __       _               _____                     _
|_ _|_ __ | |_ ___  __ _ _ __ __ _| |_ ___  __| | |  \/  | ___ | |_ ___  _ __  | ____|_ __   ___ ___   __| | ___ _ __
| || '_ \| __/ _ \/ _` | '__/ _` | __/ _ \/ _` | | |\/| |/ _ \| __/ _ \| '__| |  _| | '_ \ / __/ _ \ / _` |/ _ \ '__|
| || | | | ||  __/ (_| | | | (_| | ||  __/ (_| | | |  | | (_) | || (_) | |    | |___| | | | (_| (_) | (_| |  __/ |
|___|_| |_|\__\___|\__, |_|  \__,_|\__\___|\__,_| |_|  |_|\___/ \__\___/|_|    |_____|_| |_|\___\___/ \__,_|\___|_|
|___/

functions and Conversions
Copyright 2014 Vexy^2 Masuk Robotics. All Rights Reserved.

Revision .016

.015
-----------------
Added Slow Speeds.

.016
-----------------
Added Better debug statements


**/
#ifndef _SensorModule_H_
#define _SensorModule_H_
//#define _Sensor_Debug_
#define _LCD_Feedback_
#pragma systemFile



/*
____                _              _
/ ___|___  _ __  ___| |_ __ _ _ __ | |_ ___
| |   / _ \| '_ \/ __| __/ _` | '_ \| __/ __|
| |__| (_) | | | \__ \ || (_| | | | | |_\__ \
\____\___/|_| |_|___/\__\__,_|_| |_|\__|___/

*/


/**
Easy access motor values
Using slower values make encoder programs more accurate.
**/
typedef enum Direction{
	UP = 127,
	DOWN = -127,
	LEFT=-127,
	RIGHT = 127,
	FORWARD =127,
	REVERSE = -127,
	UP_SLOW = 40,
	DOWN_SLOW = -40,
	LEFT_SLOW = -40,
	RIGHT_SLOW = 40,
	FORWARD_SLOW = 40,
	REVERSE_SLOW = -40,
	OFF = 0
};

/*
* Robot interface descriptions
*/
static float wheelCircumference = 12.96;
static float fieldTileSize = 24.50;
static float turnDiameter = 14.5; // used to be 19.5

/*

__  __       _                ___     ____                              _____                 _   _
|  \/  | ___ | |_ ___  _ __   ( _ )   / ___|  ___ _ __  ___  ___  _ __  |  ___|   _ _ __   ___| |_(_) ___  _ __  ___
| |\/| |/ _ \| __/ _ \| '__|  / _ \/\ \___ \ / _ \ '_ \/ __|/ _ \| '__| | |_ | | | | '_ \ / __| __| |/ _ \| '_ \/ __|
| |  | | (_) | || (_) | |    | (_>  <  ___) |  __/ | | \__ \ (_) | |    |  _|| |_| | | | | (__| |_| | (_) | | | \__ \
|_|  |_|\___/ \__\___/|_|     \___/\/ |____/ \___|_| |_|___/\___/|_|    |_|   \__,_|_| |_|\___|\__|_|\___/|_| |_|___/


*/

/**
Get PetentiometerDegrees
**/
int getPotentiometerDegrees(tSensors sensor)
{

	return (int) ((float) SensorValue(sensor) / (float) 4075 * (float) 270);
	//float analog = SensorValue(sensor);
	//return ((float) analog / (float) 4095) * 270;
}

/**
Stop all drive motors.
**/
void stopDriveMotors()
{
	motor[rightMotor] =  OFF;
	motor[leftMotor] =  OFF;
	motor[leftFrontMotor] = OFF;
	motor[rightFrontMotor] = OFF;
}

/**
Sets the motor to a speed for a following time, then resets it to its previous state I SUCK PENIS YA
**/
void _motor(tMotor theMotor, Direction d,int time = 0){
	if(time == 0)
	{
		motor[theMotor] = d;
		}else{
		int lastState = motor[theMotor];
		motor[theMotor] = d;
		wait1Msec(time);
		motor[theMotor] = lastState;
	}
}

/**
Get Integrated Motor Encoder Degrees from ticks
**/
int getEncoderDegrees(tMotor m)
{



	{
		writeDebugStreamLine("%d",nMotorEncoder(m));
	}
	return  nMotorEncoder(m) * 360 / 627.2;
}

/**
Clear Integrated Motor Encoder
**/
void clearEncoder(tMotor m)
{
	nMotorEncoder[m] = 0;
}


/*
____                              _               _____                 _   _
/ ___|___  _ ____   _____ _ __ ___(_) ___  _ __   |  ___|   _ _ __   ___| |_(_) ___  _ __  ___
| |   / _ \| '_ \ \ / / _ \ '__/ __| |/ _ \| '_ \  | |_ | | | | '_ \ / __| __| |/ _ \| '_ \/ __|
| |__| (_) | | | \ V /  __/ |  \__ \ | (_) | | | | |  _|| |_| | | | | (__| |_| | (_) | | | \__ \
\____\___/|_| |_|\_/ \___|_|  |___/_|\___/|_| |_| |_|   \__,_|_| |_|\___|\__|_|\___/|_| |_|___/

*/


/**
Wheel rotations -> degrees
**/
float deg_rot(float rot)
{
	return rot * 360;
}

/**
Floor inches -> Rotations
**/
float rot_in(float inches)
{
	return inches/wheelCircumference;
}

/**
Floor tiles -> Floor Inches
**/
float in_ti(float tiles)
{
	return tiles * fieldTileSize;
}

/**
Floor tiles -> Wheel degrees
**/
float deg_ti(float tiles)
{
	return ((tiles * fieldTileSize) / wheelCircumference) * 360;
}
/**
Floor inches -> Wheel degrees
**/
float deg_in(float inches)
{
	return (inches/wheelCircumference) * 360;
}

/*

_____ _                   _           _     _   _____                 _   _
|_   _| |__  _ __ ___  ___| |__   ___ | | __| | |  ___|   _ _ __   ___| |_(_) ___  _ __  ___
| | | '_ \| '__/ _ \/ __| '_ \ / _ \| |/ _` | | |_ | | | | '_ \ / __| __| |/ _ \| '_ \/ __|
| | | | | | | |  __/\__ \ | | | (_) | | (_| | |  _|| |_| | | | | (__| |_| | (_) | | | \__ \
|_| |_| |_|_|  \___||___/_| |_|\___/|_|\__,_| |_|   \__,_|_| |_|\___|\__|_|\___/|_| |_|___/

*/

/**
Is the value greater than the thresh in the following direction, det?
**/
bool dGreater(int det, int thresh, int val)
{
	if(det > 0)
	{
		if(val>thresh)
		{
			return true;
		}

		return false;
	}
	else if(det < 0)
	{
		if(val<thresh){
			return true;
		}

		return false;
	}

	return false;
}



bool hasReachedTarget( int targetDegrees, tMotor motor)
{
	if(abs(getEncoderDegrees(motor))<targetDegrees)
	{
		return true;
	}
	return false;
}


/*

____       _     _                        _____                 _   _
/ ___|_   _(_) __| | __ _ _ __   ___ ___  |  ___|   _ _ __   ___| |_(_) ___  _ __  ___
| |  _| | | | |/ _` |/ _` | '_ \ / __/ _ \ | |_ | | | | '_ \ / __| __| |/ _ \| '_ \/ __|
| |_| | |_| | | (_| | (_| | | | | (_|  __/ |  _|| |_| | | | | (__| |_| | (_) | | | \__ \
\____|\__,_|_|\__,_|\__,_|_| |_|\___\___| |_|   \__,_|_| |_|\___|\__|_|\___/|_| |_|___/


*/
/**
Turn in the direction d, for degrees
**/
void turnDegrees(Direction d, float degrees)
{
	//ajust for inertia
	degrees -=12;

	float turnCircumference = PI * turnDiameter;
	float driveDistance = turnCircumference * degrees / 360;
	int targetDriveDegrees = 360 * (driveDistance / wheelCircumference);
	clearEncoder(leftMotor);
	clearEncoder(rightMotor);
	do
	{
		{
#ifdef _Sensor_Debug_
			writeDebugStreamLine("tar:%d",targetDriveDegrees);
			writeDebugStreamLine("enc_r:%d",getEncoderDegrees(rightMotor));
#endif
		}

		//right
		motor[rightMotor] = -d;
		motor[leftFrontMotor] = -d;
		//left
		motor[leftMotor] = d;
		motor[rightFrontMotor] = d;

	}
	while(hasReachedTarget(targetDriveDegrees, rightMotor));
	stopDriveMotors();
}


/**
Drive straight in direction d, for wheel degrees targetDegrees
**/
void driveDegrees(Direction d,float targetDegrees){
	clearEncoder(rightMotor);
while(!dGreater(d,((d < 0) ? -1 : 1) * targetDegrees,-getEncoderDegrees(rightMotor)))
	{
#ifdef _LCD_Feedback_

		int progress =((float) 100* (-getEncoderDegrees(rightMotor)/targetDegrees));
		if(progress%5==0)
		{
			string number;
			clearLCDLine(0);
			displayLCDString(0, 0, "Progress: ");

			sprintf(number, "%f",  progress);
			displayNextLCDString(number);
			displayNextLCDString("%");
		}
#endif


#ifdef _Sensor_Debug_
		writeDebugStreamLine("tar:%d",targetDegrees);
		writeDebugStreamLine("enc_r:%d",-getEncoderDegrees(rightMotor));
#endif
		motor[rightMotor] =  d;
		motor[leftMotor] =  d;
		motor[leftFrontMotor] = d;
		motor[rightFrontMotor] = d;
	}
	stopDriveMotors();
}

/**
Drive straight in direction d, for wheel rotations
**/
void driveRotations(Direction d,float targetRotations)
{
	driveDegrees(d,deg_rot(targetRotations));
}

/**
Drive straight in direction d, for floor inches
**/
void driveInches(Direction d,float targetInches)
{
	driveDegrees(d, deg_in(targetInches));
}

/**
Drive straight in direction d, for floor tiles
**/
void driveTiles(Direction d, float targetTiles)
{
	driveDegrees(d, deg_ti(targetTiles));
}

#endif
