#pragma config(Sensor, in1,    PowerExpander,  sensorNone)
#pragma config(Sensor, dgtl1,  auto_01,        sensorTouch)
#pragma config(Sensor, dgtl2,  auto_02,        sensorTouch)
#pragma config(Sensor, dgtl3,  auto_03,        sensorTouch)
#pragma config(Sensor, dgtl4,  auto_04,        sensorTouch)
#pragma config(Sensor, dgtl5,  auto_05,        sensorTouch)
#pragma config(Sensor, dgtl6,  auto_06,        sensorTouch)
#pragma config(Sensor, dgtl7,  auto_wait,      sensorTouch)
#pragma config(Sensor, dgtl10, LIMIT_UP_1,     sensorTouch)
#pragma config(Sensor, dgtl11, LIMIT_UP,       sensorTouch)
#pragma config(Sensor, dgtl12, LIMIT_DOWN,     sensorTouch)
#pragma config(Motor,  port1,           rightMotor,    tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port4,           INTAKE,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port5,           ARM_1,         tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port6,           ARM_2,         tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port10,          leftMotor,     tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)
#define compileCheck
//Enable CompetitionMode (autonomous not skills)
#define CompetitionModeEnabled;
//Disable Autonomous
//#define DisableAutonomous

#pragma DebuggerWindows("vexCompetitionControl")
#pragma competitionControl(Competition)
#include "Vex_Competition_Includes.c"
#include "Vex_Competition_Utilities.c"
#include "CompetitionAutonomous.c"
#include "CompetitionSkills.c"

/*****************************************************************************************************************
This is the cleaned up, and efficient program for Worlds.
It has encoder support.
This utilizes an "Xbox" Controller Configuration
the left joystick is drive.
the right joystick is steering. Next time close out your stuff breh.
****************************************************************************************************************/

/**
* Makes Sure speed is between -127 and 127
*/
int i27(int speed){
return (speed>127) ? 127 : (speed<-127) ? -127 : speed;
}

/**
* Threshold makes values >-20 & <20 = 0
*/
int thresh(int speed) {
return (speed < 20 && speed > -20) ? 0 : speed;
}

void pre_auton(){}
task autonomous(){
#ifdef DisableAutonomous
#warn "Autonomous is disabled! Are you sure you want this?"
#else
#ifdef CompetitionModeEnabled
	doAutonomous();
#else
	doSkills();
#endif
#endif
}

/**
* User Control
*/
task usercontrol(){
	while(true)
	{
		int speed = thresh(vexRT[Ch3]);
		int steer = thresh(vexRT[Ch1]);
		motor[rightMotor] = i27(speed - steer);
		motor[leftMotor] = i27(speed + steer);
		motor[INTAKE] = (vexRT[Btn6U] == 1) ? 127 : (vexRT[Btn6D] ==1) ? -127 : 0;
		int armSpeed = ((vexRT[Btn8UXmtr2]==1 || vexRT[Btn8U]==1) && SensorValue[LIMIT_UP]!=1 && SensorValue[LIMIT_UP_1]!=1) ? 127 : ((vexRT[Btn8DXmtr2]==1 || vexRT[Btn8D]==1) && SensorValue[LIMIT_DOWN]!=1) ? -127 : 0;
		motor[ARM_1] = armSpeed;
		motor[ARM_2] = armSpeed;
	}
}
