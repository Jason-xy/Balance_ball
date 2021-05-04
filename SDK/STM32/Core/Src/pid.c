#include "pid.h"

//全局变量
PID DistanceRingPID = {1, 0.1, 0.1};

//PID更新参数
float ErrorDistance = 0;
float NowDistance = 0;
float PreDistance = 0;
float DistanceOUT = 0;
float Speed = 0;
float TimeCycle = 20;
float MotorOUT = 0;
float MotorTime = 0;
float PreMotorOUT = 0;

void DistanceCalculate(void){
	ErrorDistance = Distance - SetDistance;
	NowDistance = ErrorDistance * 0.7f + PreDistance * 0.3f;
	Speed = (PreDistance - NowDistance)/TimeCycle;
	
}

void DistanceRingOUT(void){
    DistanceOUT = 710.0f - (NowDistance * DistanceRingPID.P + Speed * DistanceRingPID.D); 
}

void MotorOutput(void){
	MotorOUT = DistanceOUT;
	MotorTime = 10.0f - Speed;
	if(abs((int)PreMotorOUT - (int)MotorOUT) < 50){
		
		if(MotorOUT > 830)MotorOUT = 830;
		else if(MotorOUT < 590)MotorOUT = 590;
		
		if(MotorTime < 1)MotorTime = 1;
		else if(MotorTime > 5)MotorTime = 5;
		
		moveServo(1, MotorOUT, MotorTime);
	}
	PreMotorOUT = MotorOUT;
}
