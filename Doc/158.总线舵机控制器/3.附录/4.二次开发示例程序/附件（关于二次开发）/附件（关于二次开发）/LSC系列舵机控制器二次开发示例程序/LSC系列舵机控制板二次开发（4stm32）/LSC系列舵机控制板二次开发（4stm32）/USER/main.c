#include "delay.h"
#include "uart.h"
#include "LobotServoController.h"
#include "bool.h"

 int main(void)
 {
	int i = 0;
 	SystemInit();//ϵͳʱ�ӵȳ�ʼ��
	delay_init(72);	     //��ʱ��ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uartInit(9600);//���ڳ�ʼ��Ϊ9600
	 
	moveServo(1, 2000, 1000); //1���ƶ�1�Ŷ����2000λ��
	delay_ms(3000);
	moveServos(2, 800, 2,1200,9,2300); //800����2�Ŷ����1200λ�ã�9�Ŷ����2300λ��
	delay_ms(2000);
	runActionGroup(1, 1); //����1�Ŷ�����1��
	delay_ms(1500);
  stopActionGroup();  //ֹͣ����������
  setActionGroupSpeed(1, 200);//��1�Ŷ����������ٶ�����Ϊ200%
	runActionGroup(1, 1); //����1�Ŷ�����1��
	delay_ms(1000);
	stopActionGroup();  //ֹͣ����������
	while(1){
		
		receiveHandle(); //���մ���
		delay_ms(1);
		i++;
		if(i ==2000)
			getBatteryVoltage(); //���ͻ�ȡ��ص�ѹָ��
		if(i == 3000) {	
			printf("Bvolt:%d mv\r\n",batteryVolt); //��ӡ��ص�ѹ
			i = 0;
	}
 }
}
