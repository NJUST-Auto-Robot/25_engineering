#include "hardware_iic.h"

uint8_t gray_front[8] = {0}; // 16个灰度传感器数值，先是正前方的八个从数组0号位开始开始，
uint8_t gray_right[8] = {0}; // 然后是右侧的八个
							 // 然后是侧面的八个从数组8号开始
uint8_t RGBwithHSL[6] = {0}; // 存储颜色传感器的RGB和HSL数据
uint8_t color_flag = 0;		 // 颜色标志位，1是蓝色，2是红色，3是黄色，0是未知
/********************************************************************************************************************************* */
/********************************************************************************************************************************* */
/********************************************************************************************************************************* */
/********************************************************************************************************************************* */
/********************************************************************************************************************************* */
/// 以下是灰度传感器的I2C通信，用I2C3
unsigned char IIC3_ReadByte(unsigned char Salve_Adress)
{
	unsigned char dat;
	HAL_I2C_Master_Receive(&hi2c3, Salve_Adress, &dat, 1, 1000);
	return dat;
}
unsigned char IIC3_ReadBytes(unsigned char Salve_Adress, unsigned char Reg_Address, unsigned char *Result, unsigned char len)
{
	return HAL_I2C_Mem_Read(&hi2c3, Salve_Adress, Reg_Address, I2C_MEMADD_SIZE_8BIT, Result, len, 1000) == HAL_OK;
}
unsigned char IIC3_WriteByte(unsigned char Salve_Adress, unsigned char Reg_Address, unsigned char data)
{
	unsigned char dat[2] = {Reg_Address, data};
	return HAL_I2C_Master_Transmit(&hi2c3, Salve_Adress, dat, 2, 1000) == HAL_OK;
}
unsigned char IIC3_WriteBytes(unsigned char Salve_Adress, unsigned char Reg_Address, unsigned char *data, unsigned char len)
{
	return HAL_I2C_Mem_Write(&hi2c3, Salve_Adress, Reg_Address, I2C_MEMADD_SIZE_8BIT, data, len, 1000) == HAL_OK;
}
/********************************************************************************************************************************* */
/********************************************************************************************************************************* */
/********************************************************************************************************************************* */
/********************************************************************************************************************************* */
/********************************************************************************************************************************* */
/// 以下是颜色传感器的I2C通信，用I2C2

unsigned char IIC2_ReadByte(unsigned char Salve_Adress)
{
	unsigned char dat;
	HAL_I2C_Master_Receive(&hi2c2, Salve_Adress, &dat, 1, 1000);
	return dat;
}
unsigned char IIC2_ReadBytes(unsigned char Salve_Adress, unsigned char Reg_Address, unsigned char *Result, unsigned char len)
{
	return HAL_I2C_Mem_Read(&hi2c2, Salve_Adress, Reg_Address, I2C_MEMADD_SIZE_8BIT, Result, len, 1000) == HAL_OK;
}
unsigned char IIC2_WriteByte(unsigned char Salve_Adress, unsigned char Reg_Address, unsigned char data)
{
	unsigned char dat[2] = {Reg_Address, data};
	return HAL_I2C_Master_Transmit(&hi2c2, Salve_Adress, dat, 2, 1000) == HAL_OK;
}
unsigned char IIC2_WriteBytes(unsigned char Salve_Adress, unsigned char Reg_Address, unsigned char *data, unsigned char len)
{
	return HAL_I2C_Mem_Write(&hi2c2, Salve_Adress, Reg_Address, I2C_MEMADD_SIZE_8BIT, data, len, 1000) == HAL_OK;
}
/********************************************************************************************************************************* */
/********************************************************************************************************************************* */
/********************************************************************************************************************************* */
/********************************************************************************************************************************* */
/********************************************************************************************************************************* */
/// 以下是对两种传感器的I2C通信的封装函数
unsigned char Pingcolor(void)
{
	unsigned char dat;
	IIC2_ReadBytes(Color_Adress << 1, PING, &dat, 1);
	if (dat == PING_OK)
	{
		return 0;
	}
	else
		return 1;
}
unsigned char Pinggrayscale(void)
{
	unsigned char dat;
	IIC3_ReadBytes(GW_GRAY_ADDR_DEF << 1, GW_GRAY_PING, &dat, 1);
	if (dat == GW_GRAY_PING_OK)
	{
		return 0;
	}
	else
		return 1;
}
unsigned char IIC_Get_Error(void)
{
	unsigned char dat;
	IIC2_ReadBytes(Color_Adress << 1, Error, &dat, 1);
	return dat;
}
unsigned char IIC_Get_RGB(unsigned char *Result, unsigned char len)
{
	if (IIC2_ReadBytes(Color_Adress << 1, RGB_Reg, Result, len))
		return 1;
	else
		return 0;
}
unsigned char IIC_Get_HSL(unsigned char *Result, unsigned char len)
{
	if (IIC2_ReadBytes(Color_Adress << 1, HSL_Reg, Result, len))
		return 1;
	else
		return 0;
}
unsigned char IIC_Get_Digtal(void)
{
	unsigned char dat;
	IIC3_ReadBytes(GW_GRAY_ADDR_DEF << 1, GW_GRAY_DIGITAL_MODE, &dat, 1);
	return dat;
}

unsigned char IIC_Get_Anolog(unsigned char *Result, unsigned char len)
{
	if (IIC3_ReadBytes(GW_GRAY_ADDR_DEF << 1, GW_GRAY_ANALOG_BASE_, Result, len))
		return 1;
	else
		return 0;
}
unsigned char IIC_Get_Single_Anolog(unsigned char Channel)
{
	unsigned char dat;
	IIC3_ReadBytes(GW_GRAY_ADDR_DEF << 1, GW_GRAY_ANALOG(Channel), &dat, 1);
	return dat;
}
unsigned char IIC_Anolog_Normalize(uint8_t Normalize_channel)
{
	return IIC3_WriteBytes(GW_GRAY_ADDR_DEF << 1, 0xCF, &Normalize_channel, 1);
}
unsigned short IIC_Get_Offset(void)
{
	unsigned char dat[2] = {0};
	IIC3_ReadBytes(GW_GRAY_ADDR_DEF << 1, Offset, dat, 2);
	return (unsigned short)dat[0] | (unsigned short)dat[1] << 8;
}
/*
 * 灰度传感器16路读取函数
 * 读取灰度传感器的数字值，存储在全局变量gray_digital中
 * 前8个灰度传感器从数组0号位开始，后8个从数组8号位开始
 */
void Read_All_GRAY_Digital(void)
{
	uint8_t dat[2] = {0};
	IIC3_ReadBytes((GW_GRAY_ADDR_DEF << 1), GW_GRAY_DIGITAL_MODE, &dat[0], 1);
	IIC3_ReadBytes((GW_GRAY_ADDR_DEF1 << 1), GW_GRAY_DIGITAL_MODE, &dat[1], 1);
	for (int i = 0; i < 8; i++)
	{
		gray_front[i] = (dat[0] >> i) & 0x01;
		gray_right[i] = (dat[1] >> i) & 0x01;
	}	
}
/*
 * 颜色传感器读取函数
 * 读取颜色传感器的数字值，存储在全局变量RGBwithHSL[6]中
 * 前三个为RGB值，后三个为HSL值
 */
void Read_RGB_HSL(void)
{
	// 先读取RGB（3字节），再读取HSL（3字节），依次存入RGBwithHSL数组
	IIC2_ReadBytes(Color_Adress << 1, RGB_Reg, &RGBwithHSL[0], 3);
	IIC2_ReadBytes(Color_Adress << 1, HSL_Reg, &RGBwithHSL[3], 3);
}
/*
 * 颜色识别
 * 读取颜色传感器的数字值，然后进行颜色识别，存入Color_flag中
 */
void Update_Color_Flag(void)
{
	uint8_t H = RGBwithHSL[3];
	if (H >= 195 && H <= 255)
		color_flag = BLUEFLAG;
	else if (H >= 0 && H <= 25)
		color_flag = REDFLAG;
	else if (H >= 45 && H <= 75)
		color_flag = YELLOWFLAG;
	else
		color_flag = 0; // 未知
}
/*
集成所有识别
*/
void Sensor_All_Update(void)
{
		Read_All_GRAY_Digital(); // 读取灰度 
		HAL_Delay(2);
		Read_RGB_HSL();
		HAL_Delay(2);
		Update_Color_Flag();
}
// void Sensor_All_Update(void)
// {
// 	static uint8_t flag = 0;
// 	if (flag == 0)
// 	{
// 		Read_All_GRAY_Digital(); // 读取灰度
// 	}
// 	// HAL_Dela
// 	else if (flag == 1)
// 	{
// 		Read_RGB_HSL(); // 读取颜色
// 		Update_Color_Flag();
// 	}
// 	flag = (flag + 1) % 2;
// 	// HAL_Delay(1);
// }
/********************************************************************************************************************************* */
/********************************************************************************************************************************* */
/********************************************************************************************************************************* */
/********************************************************************************************************************************* */
/********************************************************************************************************************************* */
