#ifndef __SCREEN_H__
#define __SCREEN_H__
#include "usart.h"

#define USART_SCREEN huart1


//���ͽ���
void sendEnd(void);
//���;���
void sendDistance(void);
//Ŀ�����
void sendSetDistance(void);
//��ʾ����
void drawWaves(void);
//���ͽǶ�
void sendDegree(void);

#endif /* __SCREEN_H__ */
