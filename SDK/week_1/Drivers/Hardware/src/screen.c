#include "screen.h"

//发送结束
void sendEnd(void){
	HAL_UART_Transmit(&USART_SCREEN, hexEND, 3, 0xfff);
}

//发送角度
void sendDegree(void){
	memset(usartScreenSend, 0, 50*sizeof(char));
	if(Degree_Mutex){
		Degree_Mutex = 0;
		sprintf(usartScreenSend,"t1.txt=\"Degree: %.4f\"", Degree);
		Degree_Mutex = 1;
		HAL_UART_Transmit(&USART_SCREEN, (uint8_t*)usartScreenSend, strlen(usartScreenSend), 0xfff);
		sendEnd();
	}
}

//显示波形
void drawWaves(void){
	memset(usartScreenSend, 0, 50*sizeof(char));
	if(Degree_Mutex){
		Degree_Mutex = 0;
		sprintf(usartScreenSend,"add 1,0,%d", (int)Degree+100);
		Degree_Mutex = 1;
		HAL_UART_Transmit(&USART_SCREEN, (uint8_t*)usartScreenSend, strlen(usartScreenSend), 0xfff);
		sendEnd();
	}
}
