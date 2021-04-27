#ifndef __SCREEN_H__
#define __SCREEN_H__
#include "usart.h"

#define USART_SCREEN huart1


//发送结束
void sendEnd(void);
//发送距离
void sendDistance(void);
//目标距离
void sendSetDistance(void);
//显示波形
void drawWaves(void);
//发送角度
void sendDegree(void);

#endif /* __SCREEN_H__ */
