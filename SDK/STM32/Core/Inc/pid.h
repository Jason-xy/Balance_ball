#ifndef __PID_H__
#define __PID_H__

#include "main.h"
#include "math.h"
#include "motor.h"

typedef struct{
    float P;
    float I;
    float D;
}PID;

void DistanceRingOUT(void);
void DistanceCalculate(void);
void MotorOutput(void);

#endif /*__PID_H__ */
