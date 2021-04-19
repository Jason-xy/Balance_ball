#ifndef __SCREEN_H__
#define __SCREEN_H__
#include "usart.h"

#define USART_SCREEN huart1


//发送结束
void sendEnd(void);
//显示波形
void drawWaves(void);
//发送角度
void sendDegree(void);

#endif /* __SCREEN_H__ */
