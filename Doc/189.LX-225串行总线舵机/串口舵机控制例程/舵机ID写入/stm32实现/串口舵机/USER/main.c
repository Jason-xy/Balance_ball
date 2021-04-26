#include "delay.h"
#include "uart.h"
#include "LobotSerialServo.h"
#include "bool.h"

 int main(void)
 {	
 	SystemInit();   //ϵͳʱ�ӵȳ�ʼ��
	delay_init(72);	//��ʱ��ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uartInit(115200);//���ڳ�ʼ��Ϊ115200

	while(1)
	{
		LobotSerialServoSetID(254, 1);
		delay_ms(1000);
	}
}
