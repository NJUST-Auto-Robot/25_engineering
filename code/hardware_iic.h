#include "stm32f4xx_hal.h"
#include "i2c.h"
#include "gw_color_sensor.h"
#include "gw_grayscale_sensor.h"
extern uint8_t gray_digital[16];
unsigned char Pingcolor(void);
unsigned char Pinggrayscale(void);
unsigned char IIC_Get_HSL(unsigned char * Result,unsigned char len);
unsigned char IIC_Get_RGB(unsigned char * Result,unsigned char len);
unsigned char IIC_Get_Digtal(void);
unsigned char IIC_Get_Anolog(unsigned char * Result,unsigned char len);
unsigned char IIC_Get_Single_Anolog(unsigned char Channel);
unsigned char IIC_Anolog_Normalize(uint8_t Normalize_channel);
unsigned short IIC_Get_Offset(void );
unsigned char IIC_ReadByte(unsigned char Salve_Adress);
unsigned char IIC_ReadBytes(unsigned char Salve_Adress,unsigned char Reg_Address,unsigned char *Result,unsigned char len);
unsigned char IIC_WriteByte(unsigned char Salve_Adress,unsigned char Reg_Address,unsigned char data);
unsigned char IIC_WriteBytes(unsigned char Salve_Adress,unsigned char Reg_Address,unsigned char *data,unsigned char len);
unsigned char IIC_Get_Error(void);
void Read_All_GRAY_Digital(void);