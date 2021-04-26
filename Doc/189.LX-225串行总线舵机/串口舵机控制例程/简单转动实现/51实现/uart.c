/******************************************************
 * FileName:      uart.c
 * Company:       �����ֻ������Ƽ�
 * Date:           2017/02/18  18:02
 * Description:   ��������
 *****************************************************/
#include "uart.h"
#include "LobotSerialServo.h"

#include <string.h>
void uartInit() //������115200
{
	PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x04;		//���������ʷ�����ʱ��ΪFosc,��1T
	BRT = 0xFD;		  //�趨���������ʷ�������װֵ
	AUXR |= 0x01;		//����1ѡ����������ʷ�����Ϊ�����ʷ�����
	AUXR |= 0x10;		//�������������ʷ�����
	ES = 1;         //ʹ�ܴ����ж�
	EA = 1;         //ʹ��ȫ���ж�
}


uint8_t busy = 0;   //����æ��ʶ

/*********************************************************************************
 * Function:    uartWriteByte
 * Description:�򴮿�д��һ���ֽ�
 * Parameters:   dat:��д�������
 * Return:       �޷���
 * Others:
 **********************************************************************************/
void uartWriteByte(uint8_t dat)
{
	while (busy);
	busy = 1;
	SBUF = dat;
}

/*********************************************************************************
 * Function:    uartWriteBuf
 * Description:�򴮿�д������
 * Parameters:   buf:��д������ݵ�ָ��,len:��д������ݵĳ���
 * Return:       �޷���
 * Others:
 **********************************************************************************/
void uartWriteBuf(uint8_t *buf, uint8_t len)
{
	ES = 1;
	while (len--) {
		while (busy);
		busy = 1;
		SBUF = *buf++;
	}
}

/*********************************************************************************
 * Function:  receiveHandle
 * Description: �����жϺ���
 * Parameters:   �޲���
 * Return:       �޷���
 * Others:
 **********************************************************************************/

uint8_t UART_RX_BUF[24]; //���ڽ��ջ���
bool isUartRxCompleted = false; //���ڽ���������֡��ʶ

void receiveHandle(void) interrupt 4
{
	uint8_t rx;  //���ڽ����ֽ�
	static bool isGotFrameHeader = false; //���֡ͷ��ʶ  
	static uint8_t frameHeaderCount = 0;  //֡ͷ����
	static uint8_t dataLength = 3;        //���ݳ���
	static uint8_t dataCount = 0;         //���ռ��������������ջ���������±꣬���Դ�0��ʼ
	
	if (RI) {  //�����ж�
		RI = 0;  //�����ʶ
		rx = SBUF;   //��ȡ���ռĴ���
		
		if(!isGotFrameHeader)   //û�л��֡ͷ
		{
			if(rx == 0x55)  //����������֡ͷ��ͬ
			{
				frameHeaderCount++;  //֡ͷ������һ
				if(frameHeaderCount == 2) //����������յ�����0x55
				{
					frameHeaderCount = 0; //֡ͷ��������
					isGotFrameHeader = true; //�����֡ͷ
					dataCount = 1;  //���ռ���Ϊ1
				}
			}
			else //����������֡ͷ����Ͷ
			{
				isGotFrameHeader = false; //û�л��֡ͷ
				dataCount = 0;   //��������
				frameHeaderCount = 0; //��������
			}
		}
		if(isGotFrameHeader) //�����֡ͷ
		{
			UART_RX_BUF[dataCount] = rx; //�����յ������ݷ�����ջ���
			if(dataCount == 3)  //��������3��ʱ�򣬾�������֡�ĵ���λ����λΪ������֡ͷ��ID�ŵ��������ݳ���
			{
				dataLength= UART_RX_BUF[dataCount];  //��ȡ���ݳ���
				if(dataLength < 3 || dataLength > 8) //�ж������Ƿ�������߹��̣����������̶��Ǵ�������
				{
					dataLength = 3;
					isGotFrameHeader = false; //����ѻ��֡ͷ��ʶ�����¿�ʼ
				}
			}
			dataCount++;  //���ռ���+1
			if(dataCount == dataLength + 3) //����������� ���ݳ��� + 3 ��ô���ǽ��ܵ�������������֡
			{
				if(isUartRxCompleted == false)  
				{
					isUartRxCompleted = true;  //��λ������ɱ�ʶ
					memcpy(LobotRxBuf, UART_RX_BUF, dataCount+2); //������֡���Ƶ� LobotRxBuf�������մ���������
				}
				isGotFrameHeader = false; //�����ʶ������������һ֡
			}
		}
	}
	if (TI) {    //��������ж�
		TI = 0;  //�����ʶ
		busy = 0;  //�������æ��ʶ
	}
}

/*********************************************************************************
 * Function:  receiveHandle
 * Description: �ж��Ƿ���յ�����
 * Parameters:   �޲���
 * Return:       trueΪ���յ����ݣ�falseΪû�н��յ�����
 * Others:  ���յ����ݷ���true��ͬʱisUartCompleted ��ʶ�ᱻ���
 **********************************************************************************/
 
bool isRxCompleted(void)
{
	if(isUartRxCompleted)
	{
		isUartRxCompleted = false;
		return true;
	}
	else
	{
		return false;
	}
}
