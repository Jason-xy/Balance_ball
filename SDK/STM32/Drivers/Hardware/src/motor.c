#include "motor.h"
#include <stdarg.h>
#include <string.h>

#define GET_LOW_BYTE(A) ((uint8_t)(A))
//宏函数 获得A的低八位
#define GET_HIGH_BYTE(A) ((uint8_t)((A) >> 8))
//宏函数 获得A的高八位

extern bool isUartRxCompleted;

uint8_t LobotTxBuf[128];  //发送缓存
uint8_t LobotRxBuf[16];
uint16_t batteryVolt;

/*********************************************************************************
 * Function:  moveServo
 * Description： 控制单个舵机转动
 * Parameters:   sevoID:舵机ID，Position:目标位置,Time:转动时间
                    舵机ID取值:0<=舵机ID<=31,Time取值: Time > 0
 * Return:       无返回
 * Others:
 **********************************************************************************/
void moveServo(uint8_t servoID, uint16_t Position, uint16_t Time)
{
	if (servoID > 31 || !(Time > 0)) {  //舵机ID不能打于31,可根据对应控制板修改
		return;
	}
	LobotTxBuf[0] = LobotTxBuf[1] = FRAME_HEADER;    //填充帧头
	LobotTxBuf[2] = 8;
	LobotTxBuf[3] = CMD_SERVO_MOVE;           //数据长度=要控制舵机数*3+5，此处=1*3+5//填充舵机移动指令
	LobotTxBuf[4] = 1;                        //要控制的舵机个数
	LobotTxBuf[5] = GET_LOW_BYTE(Time);       //取得时间的低八位
	LobotTxBuf[6] = GET_HIGH_BYTE(Time);      //取得时间的高八位
	LobotTxBuf[7] = servoID;                  //舵机ID
	LobotTxBuf[8] = GET_LOW_BYTE(Position);   //取得目标位置的低八位
	LobotTxBuf[9] = GET_HIGH_BYTE(Position);  //取得目标位置的高八位

	//uartWriteBuf(LobotTxBuf, 10);
	HAL_UART_Transmit(&huart3, LobotTxBuf, 10, 0xff);
}

void getBatteryVoltage(void)
{
//	uint16_t Voltage = 0;
	LobotTxBuf[0] = FRAME_HEADER;  //填充帧头
	LobotTxBuf[1] = FRAME_HEADER;
	LobotTxBuf[2] = 2;             //数据长度，数据帧除帧头部分数据字节数，此命令固定为2
	LobotTxBuf[3] = CMD_GET_BATTERY_VOLTAGE;  //填充获取电池电压命令

	HAL_UART_Transmit(&huart3, LobotTxBuf, 4, 0xff);
}

