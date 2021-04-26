/*******************************************************************************
* �ļ���: LobotSerial.c
* ����: �������ֻ������Ƽ�
* ����:20170217
* LX����Demo
*******************************************************************************/
#include "uart.h"
#include "LobotSerialServo.h"
#include <stdarg.h>
#include <string.h>


#define LobotSerialWrite  uartWriteBuf /*�޸�uartWriteBufΪ���Լ��Ĵ��ڷ��ͺ���,���ֿ����Զ��壬������ԭ����������ͬ*/
                                       /*uartWriteBuf(uint8_t *buf, uint8_t len); ����ԭ��*/

#define GET_LOW_BYTE(A) ((uint8_t)(A))
//��ȡA�ĵͰ�λ
#define GET_HIGH_BYTE(A) ((uint8_t)((A) >> 8))
//��ȡA�ĸ߰�λ
#define BYTE_TO_HW(A, B) ((((uint16_t)(A)) << 8) | (uint8_t)(B))
//���ߵذ�λ�ϳ�Ϊʮ��λ

uint8_t LobotRxBuf[24];

//У�����
uint8_t LobotCheckSum(uint8_t buf[])
{
  uint8_t i;
  uint16_t temp = 0;
  for (i = 2; i < buf[3] + 2; i++) 
	{
    temp += buf[i];
  }
  temp = ~temp;
  i = (uint8_t)temp;
  return i;
}

//д������ID
void LobotSerialServoSetID(uint8_t oldID, uint8_t newID)
{
	uint8_t buf[7];
  buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
  buf[2] = oldID;
  buf[3] = 4;
  buf[4] = LOBOT_SERVO_ID_WRITE;
  buf[5] = newID;
  buf[6] = LobotCheckSum(buf);
	
  LobotSerialWrite(buf, 7);
}

//�ö����ָ��ʱ��ת��ָ��λ��
void LobotSerialServoMove(uint8_t id, int16_t position, uint16_t time)
{
  uint8_t buf[10];
  if(position < 0)
	position = 0;
  if(position > 1000)
    position = 1000;
  buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
  buf[2] = id;
  buf[3] = 7;
  buf[4] = LOBOT_SERVO_MOVE_TIME_WRITE;
  buf[5] = GET_LOW_BYTE(position);
  buf[6] = GET_HIGH_BYTE(position);
  buf[7] = GET_LOW_BYTE(time);
  buf[8] = GET_HIGH_BYTE(time);
  buf[9] = LobotCheckSum(buf);
	
  LobotSerialWrite(buf, 10);
}

//ж������
void LobotSerialServoUnload(uint8_t id)
{
  uint8_t buf[7];
  buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
  buf[2] = id;
  buf[3] = 4;
  buf[4] = LOBOT_SERVO_LOAD_OR_UNLOAD_WRITE;
  buf[5] = 0;
  buf[6] = LobotCheckSum(buf);
	
  LobotSerialWrite(buf, 7);
}
//��������
void LobotSerialServoLoad(uint8_t id)
{
  uint8_t buf[7];
  buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
  buf[2] = id;
  buf[3] = 4;
  buf[4] = LOBOT_SERVO_LOAD_OR_UNLOAD_WRITE;
  buf[5] = 1;
  buf[6] = LobotCheckSum(buf);
	
  LobotSerialWrite(buf, 7);
}
//��ö����ǰλ��
int LobotSerialServoReadPosition(uint8_t id)
{
  int ret;
  uint8_t buf[6];

  buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
  buf[2] = id;
  buf[3] = 3;
  buf[4] = LOBOT_SERVO_POS_READ;
  buf[5] = LobotCheckSum(buf);
	
	LobotSerialWrite(buf, 6);  //���ͻ�ȡλ�õ�����
	ret = LobotSerialMsgHandle(); //��ȡ���յ�������
	
  return ret; //���ض����λ��
}

int LobotSerialMsgHandle(void)
{
	uint8_t cmd;
	int count = 10000;
	int16_t ret;
	
	while(!isRxCompleted()) //����Ƿ���յ����ݣ�û�еĻ�һֱ�ȴ���֪��countС��0������ -1
	{
		count--;
		if(count < 0)
			return -1;
	}
	
	if(LobotCheckSum(LobotRxBuf) != LobotRxBuf[LobotRxBuf[3]+2])
	{
		return -2;  //����У�飬У�鲻���򷵻�-2
	}
	cmd = LobotRxBuf[4];
	switch(cmd)
	{
		case LOBOT_SERVO_POS_READ:
			ret = (int16_t)BYTE_TO_HW(LobotRxBuf[6], LobotRxBuf[5]); //�ϳ�16λ����
			return ret; //��������
		default:
			break;
	}
	return 0;
}
