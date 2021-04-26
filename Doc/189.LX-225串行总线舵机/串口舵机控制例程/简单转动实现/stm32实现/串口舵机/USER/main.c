#include "delay.h"
#include "uart.h"
#include "LobotSerialServo.h"
#include "bool.h"

#define ID1 1
#define ID2 2

 int main(void)
 {	
 	SystemInit();   //ϵͳʱ�ӵȳ�ʼ��
	delay_init(72);	//��ʱ��ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uartInit(115200);//���ڳ�ʼ��Ϊ115200

	while(1)
	{
			LobotSerialServoMove(ID1, 100, 500);  //���1��500msת����100λ��
			LobotSerialServoMove(ID2, 300, 500);  //���2��500msת����300λ��
			delay_ms(1000);
			LobotSerialServoMove(ID1, 500, 500);  //���1��500msת����500λ��
			LobotSerialServoMove(ID2, 600, 500);  //���2��500msת����600λ��
			delay_ms(1000);
			LobotSerialServoMove(ID1, 900, 800);  //���1��800msת����900λ��
			LobotSerialServoMove(ID2, 700, 800);  //���2��800msת����700λ��
			delay_ms(1000);
			LobotSerialServoMove(ID1, 500, 500);  //���1��800msת����700λ��
			LobotSerialServoMove(ID2, 600, 500);  //���2��800msת����700λ��
			delay_ms(1000);
	}
}
