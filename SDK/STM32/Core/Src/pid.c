#include "pid.h"

//全局变量
PID DistanceRingPID = {1, 0.1, 0.1};

//PID更新参数
float Error = 0;
float NowDistance = 0;
float PreDistance = 0;
float DistanceOUT = 0;
float Speed = 0;
float TimeCycle = 0;
float MotorOUT = 0;
float MotorTime = 0;

void DistanceCalculate(void){
    NowDistance = Distance * 0.7f + PreDistance * 0.3f;
	Speed = (PreDistance - NowDistance)/TimeCycle;
	
}

void DistanceRingOUT(void){
    DistanceOUT = NowDistance * DistanceRingPID.P + Speed * DistanceRingPID.D; 
}

void MotorOutput(void){
	MotorOUT = DistanceOUT;
	MotorTime = 10.0f - Speed;
	
	if(MotorOUT > 1000)MotorOUT = 1000;
	else if(MotorOUT < 0)MotorOUT = 0;
	
	if(MotorTime < 1)MotorTime = 1;
	else if(MotorTime > 20)MotorTime = 20;
	
	moveServo(1, MotorOUT, MotorTime);
}
