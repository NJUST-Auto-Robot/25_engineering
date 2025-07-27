/*
 * @Author: skybase
 * @Date: 2024-12-18 21:43:51
 * @LastEditors: skybase
 * @LastEditTime: 2025-03-21 00:57:06
 * @Description:  á•?(â— Ú¼â— )á•—â€?
 * @FilePath: \luntui_feika\code\m_math.h
 */
#ifndef M_MATH_H
#define M_MATH_H

#include "stdio.h"
#include "math.h"
#include "string.h"

float remap(float x, float y, float x1, float y1, float value);
float remap_stage(float x, float y, float x1, float y1, float stage, float value);
float fast_sqrt(float number);

#define LIMIT_MIN_MAX(x, min, max) (x) = (((x) <= (min)) ? (min) : (((x) >= (max)) ? (max) : (x)))
#define IN_RANGE(x, min, max) (((x) >= (min) && (x) <= (max)) ? 1 : 0)

typedef struct _mathtype
{
    float init_val;
    float target_val;
    float now_val;

} mathtype;

typedef void (*mathCalUpdate)(mathtype *, float, float);

void mathtypeSetVal(mathtype *obj, float init_val, float target_val);
void mathtypeUpdate(mathtype *obj, mathCalUpdate call, float timebase, float spd);

void linearCalculation(mathtype *obj, float timebase, float spd);

#endif
