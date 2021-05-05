#include "pid.h"

//全局变量
PID DistanceRingPID = {0.4, 0.00, 1};

//PID更新参数
float ErrorDistance = 0;
float SumError = 0;
float NowDistance = 0;
float PreDistance = 0;
float DistanceOUT = 0;
float Speed = 0;
float TimeCycle = 5;
float MotorOUT = 0;
float MotorTime = 0;
float PreMotorOUT = 0;

//距离环计算
void DistanceCalculate(void){
	ErrorDistance = Distance - SetDistance;
	SumError = SumError + ErrorDistance;
	if(SumError > 1000)SumError = 1000;
	else if(SumError < -1000)SumError = -1000;
	NowDistance = ErrorDistance * 0.7f + PreDistance * 0.3f;
	Speed = (PreDistance - NowDistance)/TimeCycle;
	PreDistance = NowDistance;
}

//距离环输出
void DistanceRingOUT(void){
    DistanceOUT = 660.0f - (NowDistance * DistanceRingPID.P + SumError * DistanceRingPID.I - 10.0f * Speed * DistanceRingPID.D); 
}

//电机输出
void MotorOutput(void){
	MotorOUT = DistanceOUT;
	MotorTime = 10.0f - Speed;
	if(abs((int)PreMotorOUT - (int)MotorOUT) < 50){
		
		if(MotorOUT > 690)MotorOUT = 690;
		else if(MotorOUT < 630)MotorOUT = 630;
		
		if(MotorTime < 1)MotorTime = 1;
		else if(MotorTime > 1)MotorTime = 1;
		
		moveServo(1, MotorOUT, MotorTime);
	}
	PreMotorOUT = MotorOUT;
}
