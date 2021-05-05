#include "screen.h"

//���ͽ���
void sendEnd(void){
	HAL_UART_Transmit(&USART_SCREEN, hexEND, 3, 0xfff);
}

//���ͽǶ�
void sendDegree(void){
	memset(usartScreenSend, 0, 50*sizeof(char));
	if(Degree_Mutex){
		Degree_Mutex = 0;
		sprintf(usartScreenSend,"t1.txt=\"Deg: %.1f\"", Degree);
		Degree_Mutex = 1;
		HAL_UART_Transmit(&USART_SCREEN, (uint8_t*)usartScreenSend, strlen(usartScreenSend), 0xfff);
		sendEnd();
	}
}

//���;���
void sendDistance(void){
	memset(usartScreenSend, 0, 50*sizeof(char));
	if(Distance_Mutex){
		Distance_Mutex = 0;
		sprintf(usartScreenSend,"t2.txt=\"%dmm\"", Distance);
		Distance_Mutex = 1;
		HAL_UART_Transmit(&USART_SCREEN, (uint8_t*)usartScreenSend, strlen(usartScreenSend), 0xfff);
		sendEnd();
	}
}

//����Ŀ�����
void sendSetDistance(void){
	memset(usartScreenSend, 0, 50*sizeof(char));
	if(SetDistance_Mutex){
		SetDistance_Mutex = 0;
		sprintf(usartScreenSend,"t3.txt=\"%dmm\"", SetDistance);
		SetDistance_Mutex = 1;
		HAL_UART_Transmit(&USART_SCREEN, (uint8_t*)usartScreenSend, strlen(usartScreenSend), 0xfff);
		sendEnd();
	}
}

//��ʾ����
void drawWaves(void){
	memset(usartScreenSend, 0, 50*sizeof(char));
	if(SetDistance_Mutex){
		SetDistance_Mutex = 0;
		sprintf(usartScreenSend,"add 1,0,%d", (int)((SetDistance+50)/300.0f*200));
		SetDistance_Mutex = 1;
		HAL_UART_Transmit(&USART_SCREEN, (uint8_t*)usartScreenSend, strlen(usartScreenSend), 0xfff);
		sendEnd();
	}
	memset(usartScreenSend, 0, 50*sizeof(char));
	if(Distance_Mutex){
		Distance_Mutex = 0;
		sprintf(usartScreenSend,"add 1,1,%d", (int)((Distance+50)/300.0f*200));
		Distance_Mutex = 1;
		HAL_UART_Transmit(&USART_SCREEN, (uint8_t*)usartScreenSend, strlen(usartScreenSend), 0xfff);
		sendEnd();
	}
}
