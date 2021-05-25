#include "motor.h"
#include <stdarg.h>
#include <string.h>

#define GET_LOW_BYTE(A) ((uint8_t)(A))
//�꺯�� ���A�ĵͰ�λ
#define GET_HIGH_BYTE(A) ((uint8_t)((A) >> 8))
//�꺯�� ���A�ĸ߰�λ

extern bool isUartRxCompleted;

uint8_t LobotTxBuf[128];  //���ͻ���
uint8_t LobotRxBuf[16];
uint16_t batteryVolt;

/*********************************************************************************
 * Function:  moveServo
 * Description�� ���Ƶ������ת��
 * Parameters:   sevoID:���ID��Position:Ŀ��λ��,Time:ת��ʱ��
                    ���IDȡֵ:0<=���ID<=31,Timeȡֵ: Time > 0
 * Return:       �޷���
 * Others:
 **********************************************************************************/
void moveServo(uint8_t servoID, uint16_t Position, uint16_t Time)
{
	if (servoID > 31 || !(Time > 0)) {  //���ID���ܴ���31,�ɸ��ݶ�Ӧ���ư��޸�
		return;
	}
	LobotTxBuf[0] = LobotTxBuf[1] = FRAME_HEADER;    //���֡ͷ
	LobotTxBuf[2] = 8;
	LobotTxBuf[3] = CMD_SERVO_MOVE;           //���ݳ���=Ҫ���ƶ����*3+5���˴�=1*3+5//������ƶ�ָ��
	LobotTxBuf[4] = 1;                        //Ҫ���ƵĶ������
	LobotTxBuf[5] = GET_LOW_BYTE(Time);       //ȡ��ʱ��ĵͰ�λ
	LobotTxBuf[6] = GET_HIGH_BYTE(Time);      //ȡ��ʱ��ĸ߰�λ
	LobotTxBuf[7] = servoID;                  //���ID
	LobotTxBuf[8] = GET_LOW_BYTE(Position);   //ȡ��Ŀ��λ�õĵͰ�λ
	LobotTxBuf[9] = GET_HIGH_BYTE(Position);  //ȡ��Ŀ��λ�õĸ߰�λ

	//uartWriteBuf(LobotTxBuf, 10);
	HAL_UART_Transmit(&huart3, LobotTxBuf, 10, 0xf);
}

void getBatteryVoltage(void)
{
//	uint16_t Voltage = 0;
	LobotTxBuf[0] = FRAME_HEADER;  //���֡ͷ
	LobotTxBuf[1] = FRAME_HEADER;
	LobotTxBuf[2] = 2;             //���ݳ��ȣ�����֡��֡ͷ���������ֽ�����������̶�Ϊ2
	LobotTxBuf[3] = CMD_GET_BATTERY_VOLTAGE;  //����ȡ��ص�ѹ����

	HAL_UART_Transmit(&huart3, LobotTxBuf, 4, 0xff);
}

