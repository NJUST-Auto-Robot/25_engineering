#include "stm32f4xx_hal.h"
#include "i2c.h"
#include "gw_color_sensor.h"
#include "gw_grayscale_sensor.h"
#define BLUEFLAG    1
#define REDFLAG     2
#define YELLOWFLAG  3
extern uint8_t gray_digital[16];
extern uint8_t RGBwithHSL[6];
extern uint8_t color_flag;
unsigned char Pingcolor(void);
unsigned char Pinggrayscale(void);
unsigned char IIC_Get_HSL(unsigned char * Result,unsigned char len);
unsigned char IIC_Get_RGB(unsigned char * Result,unsigned char len);
unsigned char IIC_Get_Digtal(void);
unsigned char IIC_Get_Anolog(unsigned char * Result,unsigned char len);
unsigned char IIC_Get_Single_Anolog(unsigned char Channel);
unsigned char IIC_Anolog_Normalize(uint8_t Normalize_channel);
unsigned short IIC_Get_Offset(void );
unsigned char IIC_Get_Error(void);
void Read_All_GRAY_Digital(void);
void Read_RGB_HSL(void);
void Update_Color_Flag(void);
void Sensor_All_Update(void);