/******************************************************
 * FileName:      main.c
 * Company:       �����ֻ������Ƽ�
 * Date:          2017/02/18  17:50
 * Description:   LX-16ϵ�д��ڶ������ʾ��
 *****************************************************/
#include "STC12C5A60S2.H"
#include "typedef.h"
#include "intrins.h"
#include "uart.h"
#include "LobotSerialServo.h"

void Delay1000ms()		//@11.0592MHz ��ʱ1000ms
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

#define ID1 1
#define ID2 2

int main()
{
	uartInit(); //��ʼ�� ���� ������ҪΪ 115200
	while(1)
	{
		LobotSerialServoMove(ID1, 100, 500); //ID1�Ŷ��500msת���� 100λ��
		LobotSerialServoMove(ID2, 200, 500); //ID2�Ŷ��500msת���� 200λ��
		Delay1000ms();
		LobotSerialServoMove(ID1, 500, 500); //ID1�Ŷ��500msת���� 500λ��
		LobotSerialServoMove(ID2, 600, 500); //ID2�Ŷ��500msת���� 600λ��
		Delay1000ms();
		LobotSerialServoMove(ID1, 900, 500); //ID1�Ŷ��500msת���� 900λ��
		LobotSerialServoMove(ID2, 1000, 500);//ID2�Ŷ��500msת���� 1000λ��
		Delay1000ms();
		LobotSerialServoMove(ID1, 500, 500); //ID1�Ŷ��500msת���� 500λ��
		LobotSerialServoMove(ID2, 600, 500); //ID2�Ŷ��500msת���� 600λ��
		Delay1000ms();
	}
}
