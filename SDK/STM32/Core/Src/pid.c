#include "pid.h"

//全局变量
PID DistanceRingPID = {0.8, 0.00, 12};

//PID更新参数
float ErrorDistance = 0;
float SumError = 0;
float NowDistance = 0;
float PreDistance = 0;
float DistanceOUT = 0;
float Speed = 0;
float TimeCycle = 20;
float MotorOUT = 0;
float MotorTime = 0;
float PreMotorOUT = 0;
float PreSetDistance = 0;
float Balance = 675;

//距离环计算
void DistanceCalculate(void){
	ErrorDistance = Distance - SetDistance;
	if(PreSetDistance != SetDistance)SumError =0;
	if(ErrorDistance < 20)SumError = SumError + ErrorDistance;
	if(SumError > 1000)SumError = 1000;
	else if(SumError < -1000)SumError = -1000;
	NowDistance = ErrorDistance * 0.7f + PreDistance * 0.3f;
	Speed = (PreDistance - NowDistance)/TimeCycle;
	PreDistance = NowDistance;
	PreSetDistance = SetDistance;
}

//距离环输出
void DistanceRingOUT(void){
		if(ErrorDistance > 5)
			DistanceOUT = Balance - (NowDistance * DistanceRingPID.P  - 10.0f * Speed * DistanceRingPID.D);
		else
			DistanceOUT = Balance - (NowDistance * DistanceRingPID.P  - 10.0f * Speed * DistanceRingPID.D * 0.3); 
		Degree = DistanceOUT;
}

//电机输出
void MotorOutput(void){
	MotorOUT = DistanceOUT;
	MotorTime = 10.0f - Speed;
	if(abs((int)PreMotorOUT - (int)MotorOUT) < 50){
		
		if(MotorOUT > 770)MotorOUT = 770;
		else if(MotorOUT < 590)MotorOUT = 590;
		
		if(MotorTime > 1)MotorTime = 1;
		
		moveServo(1, MotorOUT, MotorTime);
	}
	PreMotorOUT = MotorOUT;
}
