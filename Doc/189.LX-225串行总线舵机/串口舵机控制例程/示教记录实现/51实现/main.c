/******************************************************
 * FileName:      main.c
 * Company:       �����ֻ������Ƽ�
 * Date:          2017/02/20  10:24
 * Description:  
 *****************************************************/
#include "STC12C5A60S2.H"
#include "typedef.h"
#include "intrins.h"
#include "uart.h"
#include "LobotSerialServo.h"

void Delay1000ms()		//@11.0592MHz  ��ʱ1000ms
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 43;
	j = 6;
	k = 203;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay500ms()		//@11.0592MHz  ��ʱ500ms
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 22;
	j = 3;
	k = 227;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay10ms()		//@11.0592MHz   ��ʱ10ms
{
	unsigned char i, j;

	i = 108;
	j = 145;
	do
	{
		while (--j);
	} while (--i);
}


sbit Key1 = P3^2;  //��ť1  //ģʽ�л�
sbit Key2 = P3^3;  //��ť2  //����ģʽ�£����ж����� ¼��ģʽ�£���¼����

#define ID1 1
#define ID2 2

int main()
{
	bool run = false;
	char step = 0;
	char mode = 0;

	uint16_t pos[4] = {100,200,300,400};
	uint16_t pos1[4] = {100,200,300,400};

	Key1 = 1;
	Key2 = 1;

	uartInit();
	LobotSerialServoMove(ID1, 500, 100);
	LobotSerialServoMove(ID2, 500, 100);

  while (1) {
    if (mode == 0)
    {
      if (run)   //���run��ʶΪtrue��������
      {
        LobotSerialServoMove(ID1, pos[step], 500);     //�˶�����¼��λ��
				LobotSerialServoMove(ID2, pos1[step++], 500);
        if (step == 4)
        {
          step = 0;
          run = false;
        }
        Delay1000ms();
      }
      if (!Key2)    //���°���2����run��Ϊtrue
      {
        Delay10ms();   
        if (!Key2)
        {
          run = true;
          step = 0;
          Delay500ms();
        }
      }
      if (!Key1)    //���°���1 ж�ض�������أ�ת�Ƶ�ģʽ1 ������¼ģʽ
      {
        Delay10ms();
        if (!Key1)
        {
          LobotSerialServoUnload(ID1);   //ж�ض��1
					LobotSerialServoUnload(ID2);   //ж�ض��2
          mode = 1;
          step = 0;
          Delay500ms();
        }
      }
    }
    if (mode == 1)
    {
      if (!Key2)   //���°���2����ȡ�����ǰλ�ã�����¼����
      {
        Delay10ms();
        if (!Key2)
        {
          pos[step] = LobotSerialServoReadPosition(ID1);
					pos1[step++] = LobotSerialServoReadPosition(ID2);
          if (step == 4)
            step = 0;
          Delay500ms();
        }
      }
      if (!Key1)   //������°���1�����ض�����أ�ת�Ƶ�ģʽ0
      {
        Delay10ms();
        if (!Key1)
        {
          LobotSerialServoMove(ID1, LobotSerialServoReadPosition(ID1), 200);
					LobotSerialServoMove(ID2, LobotSerialServoReadPosition(ID2), 200);
          mode = 0;
          Delay500ms();
        }
      }
    }
  }
}
