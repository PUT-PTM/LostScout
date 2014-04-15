/**
******************************************************************************
* @file    main.c
* @author  MCD Application Team
* @version V1.0.0
* @date    19-September-2011
* @brief   Main program body
******************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
******************************************************************************
*/



/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usbd_hid_core.h"
#include "usbd_usr.h"
#include "usbd_desc.h"


#include <stdlib.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "misc.h"
#include "stm32f4xx_spi.h"




/* LIS302DL struct */
typedef struct
{
	uint8_t Power_Mode;                         /* Power-down/Active Mode */
	uint8_t Output_DataRate;                    /* OUT data rate 100 Hz / 400 Hz */
	uint8_t Axes_Enable;                        /* Axes enable */
	uint8_t Full_Scale;                         /* Full scale */
	uint8_t Self_Test;                          /* Self test */
}LIS302DL_InitTypeDef;

/* LIS302DL High Pass Filter struct */
typedef struct
{
	uint8_t HighPassFilter_Data_Selection;      /* Internal filter bypassed or data from internal filter send to output register*/
	uint8_t HighPassFilter_CutOff_Frequency;    /* High pass filter cut-off frequency */
	uint8_t HighPassFilter_Interrupt;           /* High pass filter enabled for Freefall/WakeUp #1 or #2 */
}LIS302DL_FilterConfigTypeDef;

/* LIS302DL Interrupt struct */
typedef struct
{
	uint8_t Latch_Request;                      /* Latch interrupt request into CLICK_SRC register*/
	uint8_t SingleClick_Axes;                   /* Single Click Axes Interrupts */
	uint8_t DoubleClick_Axes;                   /* Double Click Axes Interrupts */
}LIS302DL_InterruptConfigTypeDef;



#define LIS302DL_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define LIS302DL_SPI                       SPI1
#define LIS302DL_SPI_CLK                   RCC_APB2Periph_SPI1

#define LIS302DL_SPI_SCK_PIN               GPIO_Pin_5                  /* PA.05 */
#define LIS302DL_SPI_SCK_GPIO_PORT         GPIOA                       /* GPIOA */
#define LIS302DL_SPI_SCK_GPIO_CLK          RCC_AHB1Periph_GPIOA
#define LIS302DL_SPI_SCK_SOURCE            GPIO_PinSource5
#define LIS302DL_SPI_SCK_AF                GPIO_AF_SPI1

#define LIS302DL_SPI_MISO_PIN              GPIO_Pin_6                  /* PA.6 */
#define LIS302DL_SPI_MISO_GPIO_PORT        GPIOA                       /* GPIOA */
#define LIS302DL_SPI_MISO_GPIO_CLK         RCC_AHB1Periph_GPIOA
#define LIS302DL_SPI_MISO_SOURCE           GPIO_PinSource6
#define LIS302DL_SPI_MISO_AF               GPIO_AF_SPI1

#define LIS302DL_SPI_MOSI_PIN              GPIO_Pin_7                  /* PA.7 */
#define LIS302DL_SPI_MOSI_GPIO_PORT        GPIOA                       /* GPIOA */
#define LIS302DL_SPI_MOSI_GPIO_CLK         RCC_AHB1Periph_GPIOA
#define LIS302DL_SPI_MOSI_SOURCE           GPIO_PinSource7
#define LIS302DL_SPI_MOSI_AF               GPIO_AF_SPI1

#define LIS302DL_SPI_CS_PIN                GPIO_Pin_3                  /* PE.03 */
#define LIS302DL_SPI_CS_GPIO_PORT          GPIOE                       /* GPIOE */
#define LIS302DL_SPI_CS_GPIO_CLK           RCC_AHB1Periph_GPIOE

#define LIS302DL_SPI_INT1_PIN              GPIO_Pin_0                  /* PE.00 */
#define LIS302DL_SPI_INT1_GPIO_PORT        GPIOE                       /* GPIOE */
#define LIS302DL_SPI_INT1_GPIO_CLK         RCC_AHB1Periph_GPIOE
#define LIS302DL_SPI_INT1_EXTI_LINE        EXTI_Line0
#define LIS302DL_SPI_INT1_EXTI_PORT_SOURCE EXTI_PortSourceGPIOE
#define LIS302DL_SPI_INT1_EXTI_PIN_SOURCE  EXTI_PinSource0
#define LIS302DL_SPI_INT1_EXTI_IRQn        EXTI0_IRQn

#define LIS302DL_SPI_INT2_PIN              GPIO_Pin_1                  /* PE.01 */
#define LIS302DL_SPI_INT2_GPIO_PORT        GPIOE                       /* GPIOE */
#define LIS302DL_SPI_INT2_GPIO_CLK         RCC_AHB1Periph_GPIOE
#define LIS302DL_SPI_INT2_EXTI_LINE        EXTI_Line1
#define LIS302DL_SPI_INT2_EXTI_PORT_SOURCE EXTI_PortSourceGPIOE
#define LIS302DL_SPI_INT2_EXTI_PIN_SOURCE  EXTI_PinSource1
#define LIS302DL_SPI_INT2_EXTI_IRQn        EXTI1_IRQn


#define LIS302DL_WHO_AM_I_ADDR                  0x0F
#define LIS302DL_CTRL_REG1_ADDR                 0x20
#define LIS302DL_CTRL_REG2_ADDR              0x21
#define LIS302DL_CTRL_REG3_ADDR              0x22
#define LIS302DL_HP_FILTER_RESET_REG_ADDR     0x23
#define LIS302DL_STATUS_REG_ADDR             0x27
#define LIS302DL_OUT_X_ADDR                  0x29
#define LIS302DL_OUT_Y_ADDR                  0x2B
#define LIS302DL_OUT_Z_ADDR                  0x2D
#define LIS302DL_FF_WU_CFG1_REG_ADDR         0x30
#define LIS302DL_FF_WU_SRC1_REG_ADDR           0x31
#define LIS302DL_FF_WU_THS1_REG_ADDR          0x32
#define LIS302DL_FF_WU_DURATION1_REG_ADDR     0x33
#define LIS302DL_FF_WU_CFG2_REG_ADDR         0x34
#define LIS302DL_FF_WU_SRC2_REG_ADDR           0x35
#define LIS302DL_FF_WU_THS2_REG_ADDR          0x36
#define LIS302DL_FF_WU_DURATION2_REG_ADDR     0x37
#define LIS302DL_CLICK_CFG_REG_ADDR     0x38
#define LIS302DL_CLICK_SRC_REG_ADDR        0x39
#define LIS302DL_CLICK_THSY_X_REG_ADDR        0x3B
#define LIS302DL_CLICK_THSZ_REG_ADDR         0x3C
#define LIS302DL_CLICK_TIMELIMIT_REG_ADDR        0x3D
#define LIS302DL_CLICK_LATENCY_REG_ADDR        0x3E
#define LIS302DL_CLICK_WINDOW_REG_ADDR        0x3F
#define LIS302DL_SENSITIVITY_2_3G                         18  /* 18 mg/digit*/
#define LIS302DL_SENSITIVITY_9_2G                         72  /* 72 mg/digit*/
#define LIS302DL_DATARATE_100                             ((uint8_t)0x00)
#define LIS302DL_DATARATE_400                             ((uint8_t)0x80)
#define LIS302DL_LOWPOWERMODE_POWERDOWN                   ((uint8_t)0x00)
#define LIS302DL_LOWPOWERMODE_ACTIVE                      ((uint8_t)0x40)
#define LIS302DL_FULLSCALE_2_3                            ((uint8_t)0x00)
#define LIS302DL_FULLSCALE_9_2                            ((uint8_t)0x20)
#define LIS302DL_SELFTEST_NORMAL                          ((uint8_t)0x00)
#define LIS302DL_SELFTEST_P                               ((uint8_t)0x10)
#define LIS302DL_SELFTEST_M                               ((uint8_t)0x08)
#define LIS302DL_X_ENABLE                                 ((uint8_t)0x01)
#define LIS302DL_Y_ENABLE                                 ((uint8_t)0x02)
#define LIS302DL_Z_ENABLE                                 ((uint8_t)0x04)
#define LIS302DL_XYZ_ENABLE                               ((uint8_t)0x07)
#define LIS302DL_SERIALINTERFACE_4WIRE                    ((uint8_t)0x00)
#define LIS302DL_SERIALINTERFACE_3WIRE                    ((uint8_t)0x80)
#define LIS302DL_BOOT_NORMALMODE                          ((uint8_t)0x00)
#define LIS302DL_BOOT_REBOOTMEMORY                        ((uint8_t)0x40)
#define LIS302DL_FILTEREDDATASELECTION_BYPASSED           ((uint8_t)0x00)
#define LIS302DL_FILTEREDDATASELECTION_OUTPUTREGISTER     ((uint8_t)0x20)
#define LIS302DL_HIGHPASSFILTERINTERRUPT_OFF              ((uint8_t)0x00)
#define LIS302DL_HIGHPASSFILTERINTERRUPT_1                ((uint8_t)0x04)
#define LIS302DL_HIGHPASSFILTERINTERRUPT_2                ((uint8_t)0x08)
#define LIS302DL_HIGHPASSFILTERINTERRUPT_1_2              ((uint8_t)0x0C)
#define LIS302DL_HIGHPASSFILTER_LEVEL_0                   ((uint8_t)0x00)
#define LIS302DL_HIGHPASSFILTER_LEVEL_1                   ((uint8_t)0x01)
#define LIS302DL_HIGHPASSFILTER_LEVEL_2                   ((uint8_t)0x02)
#define LIS302DL_HIGHPASSFILTER_LEVEL_3                   ((uint8_t)0x03)
#define LIS302DL_INTERRUPTREQUEST_NOTLATCHED              ((uint8_t)0x00)
#define LIS302DL_INTERRUPTREQUEST_LATCHED                 ((uint8_t)0x40)
#define LIS302DL_CLICKINTERRUPT_XYZ_DISABLE               ((uint8_t)0x00)
#define LIS302DL_CLICKINTERRUPT_X_ENABLE                  ((uint8_t)0x01)
#define LIS302DL_CLICKINTERRUPT_Y_ENABLE                  ((uint8_t)0x04)
#define LIS302DL_CLICKINTERRUPT_Z_ENABLE                  ((uint8_t)0x10)
#define LIS302DL_CLICKINTERRUPT_XYZ_ENABLE                ((uint8_t)0x15)
#define LIS302DL_DOUBLECLICKINTERRUPT_XYZ_DISABLE         ((uint8_t)0x00)
#define LIS302DL_DOUBLECLICKINTERRUPT_X_ENABLE            ((uint8_t)0x02)
#define LIS302DL_DOUBLECLICKINTERRUPT_Y_ENABLE            ((uint8_t)0x08)
#define LIS302DL_DOUBLECLICKINTERRUPT_Z_ENABLE            ((uint8_t)0x20)
#define LIS302DL_DOUBLECLICKINTERRUPT_XYZ_ENABLE          ((uint8_t)0x2A)
#define LIS302DL_CS_LOW()       GPIO_ResetBits(LIS302DL_SPI_CS_GPIO_PORT, LIS302DL_SPI_CS_PIN)
#define LIS302DL_CS_HIGH()      GPIO_SetBits(LIS302DL_SPI_CS_GPIO_PORT, LIS302DL_SPI_CS_PIN)
#define READWRITE_CMD              ((uint8_t)0x80)
#define MULTIPLEBYTE_CMD           ((uint8_t)0x40)
#define DUMMY_BYTE                 ((uint8_t)0x00)

__IO uint32_t  LIS302DLTimeout = LIS302DL_FLAG_TIMEOUT;





int pomiar_x=0;
int pomiar_y=0;
int pomiar_z=0;
uint16_t PrescalerValue = 0;
__IO uint32_t TimingDelay = 0;
int8_t przyspieszenie_x;
int8_t przyspieszenie_y;
int8_t przyspieszenie_z;


void LIS302DL_Init(LIS302DL_InitTypeDef *LIS302DL_InitStruct);
void LIS302DL_Write(uint8_t* pBuffer, uint8_t WriteAddr, uint16_t NumByteToWrite);
static uint8_t LIS302DL_SendByte(uint8_t byte);
void LIS302DL_InterruptConfig(LIS302DL_InterruptConfigTypeDef *LIS302DL_IntConfigStruct);
void LIS302DL_Read(uint8_t* pBuffer, uint8_t ReadAddr, uint16_t NumByteToRead);
uint32_t LIS302DL_TIMEOUT_UserCallback(void);




void LIS302DL_Init(LIS302DL_InitTypeDef *LIS302DL_InitStruct)
{
	uint8_t ctrl = 0x00;

	/* Configure the low level interface ---------------------------------------*/
	//  LIS302DL_LowLevel_Init();

	/* Configure MEMS: data rate, power mode, full scale, self test and axes */
	ctrl = (uint8_t) (LIS302DL_InitStruct->Output_DataRate | LIS302DL_InitStruct->Power_Mode | \
		LIS302DL_InitStruct->Full_Scale | LIS302DL_InitStruct->Self_Test | \
		LIS302DL_InitStruct->Axes_Enable);

	/* Write value to MEMS CTRL_REG1 regsister */
	LIS302DL_Write(&ctrl, LIS302DL_CTRL_REG1_ADDR, 1);
}






void LIS302DL_Write(uint8_t* pBuffer, uint8_t WriteAddr, uint16_t NumByteToWrite)
{
	/* Configure the MS bit:
	- When 0, the address will remain unchanged in multiple read/write commands.
	- When 1, the address will be auto incremented in multiple read/write commands.
	*/
	if(NumByteToWrite > 0x01)
	{
		WriteAddr |= (uint8_t)MULTIPLEBYTE_CMD;
	}
	/* Set chip select Low at the start of the transmission */
	LIS302DL_CS_LOW();

	/* Send the Address of the indexed register */
	LIS302DL_SendByte(WriteAddr);
	/* Send the data that will be written into the device (MSB First) */
	while(NumByteToWrite >= 0x01)
	{
		LIS302DL_SendByte(*pBuffer);
		NumByteToWrite--;
		pBuffer++;
	}

	/* Set chip select High at the end of the transmission */
	LIS302DL_CS_HIGH();
}






static uint8_t LIS302DL_SendByte(uint8_t byte)
{
	/* Loop while DR register in not emplty */
	LIS302DLTimeout = LIS302DL_FLAG_TIMEOUT;
	while (SPI_I2S_GetFlagStatus(LIS302DL_SPI, SPI_I2S_FLAG_TXE) == RESET)
	{
		if((LIS302DLTimeout--) == 0) return LIS302DL_TIMEOUT_UserCallback();
	}

	/* Send a Byte through the SPI peripheral */
	SPI_I2S_SendData(LIS302DL_SPI, byte);

	/* Wait to receive a Byte */
	LIS302DLTimeout = LIS302DL_FLAG_TIMEOUT;
	while (SPI_I2S_GetFlagStatus(LIS302DL_SPI, SPI_I2S_FLAG_RXNE) == RESET)
	{
		if((LIS302DLTimeout--) == 0) return LIS302DL_TIMEOUT_UserCallback();
	}

	/* Return the Byte read from the SPI bus */
	return (uint8_t)SPI_I2S_ReceiveData(LIS302DL_SPI);
}



void LIS302DL_InterruptConfig(LIS302DL_InterruptConfigTypeDef *LIS302DL_IntConfigStruct)
{
	uint8_t ctrl = 0x00;

	/* Read CLICK_CFG register */
	LIS302DL_Read(&ctrl, LIS302DL_CLICK_CFG_REG_ADDR, 1);

	/* Configure latch Interrupt request, click interrupts and double click interrupts */
	ctrl = (uint8_t)(LIS302DL_IntConfigStruct->Latch_Request| \
		LIS302DL_IntConfigStruct->SingleClick_Axes | \
		LIS302DL_IntConfigStruct->DoubleClick_Axes);

	/* Write value to MEMS CLICK_CFG register */
	LIS302DL_Write(&ctrl, LIS302DL_CLICK_CFG_REG_ADDR, 1);
}

void LIS302DL_Read(uint8_t* pBuffer, uint8_t ReadAddr, uint16_t NumByteToRead)
{
	if(NumByteToRead > 0x01)
	{
		ReadAddr |= (uint8_t)(READWRITE_CMD | MULTIPLEBYTE_CMD);
	}
	else
	{
		ReadAddr |= (uint8_t)READWRITE_CMD;
	}
	/* Set chip select Low at the start of the transmission */
	LIS302DL_CS_LOW();

	/* Send the Address of the indexed register */
	LIS302DL_SendByte(ReadAddr);

	/* Receive the data that will be read from the device (MSB First) */
	while(NumByteToRead > 0x00)
	{
		/* Send dummy byte (0x00) to generate the SPI clock to LIS302DL (Slave device) */
		*pBuffer = LIS302DL_SendByte(DUMMY_BYTE);
		NumByteToRead--;
		pBuffer++;
	}

	/* Set chip select High at the end of the transmission */
	LIS302DL_CS_HIGH();
}



/**
* @brief  Decrements the TimingDelay variable.
* @param  None
* @retval None
*/
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{
		TimingDelay--;
	}
}



/**
* @brief  MEMS accelerometre management of the timeout situation.
* @param  None.
* @retval None.
*/
uint32_t LIS302DL_TIMEOUT_UserCallback(void)
{
	/* MEMS Accelerometer Timeout error occured */
	while (1)
	{
	}
}


/**
* @}
*/

/**
* @}
*/


/** @addtogroup STM32F4-Discovery_USB_HID
* @{
*/

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define ADC1_CDR_Address    ((uint32_t)0x40012308)


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
#if defined ( __ICCARM__ ) /*!< IAR Compiler */
#pragma data_alignment = 4
#endif
#endif /* USB_OTG_HS_INTERNAL_DMA_ENABLED */
__ALIGN_BEGIN USB_OTG_CORE_HANDLE  USB_OTG_dev __ALIGN_END;

__IO uint8_t UserButtonPressed = 0x00;
uint8_t InBuffer[64], OutBuffer[63];
void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);
void przerwania(void);


/* Private functions ---------------------------------------------------------*/

/**
* @brief  Main program.
* @param  None
* @retval None
*/


/*void TIM4_IRQHandler(void)
{

	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	{
		GPIO_ResetBits(GPIOD, GPIO_Pin_15);
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);

	}
} */
int main(void)
{
	SystemInit();
	SystemCoreClockUpdate(); // inicjalizacja dystrybucji czasu procesora



	/* Enable the SPI periph */
	RCC_APB2PeriphClockCmd(LIS302DL_SPI_CLK, ENABLE);

	/* Enable SCK, MOSI and MISO GPIO clocks */
	RCC_AHB1PeriphClockCmd(LIS302DL_SPI_SCK_GPIO_CLK | LIS302DL_SPI_MISO_GPIO_CLK | LIS302DL_SPI_MOSI_GPIO_CLK, ENABLE);

	/* Enable CS  GPIO clock */
	RCC_AHB1PeriphClockCmd(LIS302DL_SPI_CS_GPIO_CLK, ENABLE);

	/* Enable INT1 GPIO clock */
	RCC_AHB1PeriphClockCmd(LIS302DL_SPI_INT1_GPIO_CLK, ENABLE);

	/* Enable INT2 GPIO clock */
	RCC_AHB1PeriphClockCmd(LIS302DL_SPI_INT2_GPIO_CLK, ENABLE);

	GPIO_PinAFConfig(LIS302DL_SPI_SCK_GPIO_PORT, LIS302DL_SPI_SCK_SOURCE, LIS302DL_SPI_SCK_AF);
	GPIO_PinAFConfig(LIS302DL_SPI_MISO_GPIO_PORT, LIS302DL_SPI_MISO_SOURCE, LIS302DL_SPI_MISO_AF);
	GPIO_PinAFConfig(LIS302DL_SPI_MOSI_GPIO_PORT, LIS302DL_SPI_MOSI_SOURCE, LIS302DL_SPI_MOSI_AF);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	/* SPI SCK pin configuration */
	GPIO_InitStructure.GPIO_Pin = LIS302DL_SPI_SCK_PIN;
	GPIO_Init(LIS302DL_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

	/* SPI  MOSI pin configuration */
	GPIO_InitStructure.GPIO_Pin =  LIS302DL_SPI_MOSI_PIN;
	GPIO_Init(LIS302DL_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

	/* SPI MISO pin configuration */
	GPIO_InitStructure.GPIO_Pin = LIS302DL_SPI_MISO_PIN;
	GPIO_Init(LIS302DL_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

	/* SPI configuration -------------------------------------------------------*/
	SPI_InitTypeDef  SPI_InitStructure;
	SPI_I2S_DeInit(LIS302DL_SPI);
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_Init(LIS302DL_SPI, &SPI_InitStructure);

	/* Enable SPI1  */
	SPI_Cmd(LIS302DL_SPI, ENABLE);

	/* Configure GPIO PIN for Lis Chip select */
	GPIO_InitStructure.GPIO_Pin = LIS302DL_SPI_CS_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LIS302DL_SPI_CS_GPIO_PORT, &GPIO_InitStructure);

	/* Deselect : Chip Select high */
	GPIO_SetBits(LIS302DL_SPI_CS_GPIO_PORT, LIS302DL_SPI_CS_PIN);

	/* Configure GPIO PINs to detect Interrupts */
	GPIO_InitStructure.GPIO_Pin = LIS302DL_SPI_INT1_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(LIS302DL_SPI_INT1_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = LIS302DL_SPI_INT2_PIN;
	GPIO_Init(LIS302DL_SPI_INT2_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitTypeDef GPIO_InitStructure2;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitStructure2.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure2.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure2.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure2.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOD, &GPIO_InitStructure2);


	 TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure2;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	TIM_TimeBaseStructure2.TIM_Period = 10000;
	TIM_TimeBaseStructure2.TIM_Prescaler = 8400;
	TIM_TimeBaseStructure2.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure2.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure2.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure2);
	//TIM_Cmd(TIM4, ENABLE);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	            RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	            TIM_TimeBaseStructure.TIM_Prescaler = 8400;
	            TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	            TIM_TimeBaseStructure.TIM_Period = 10000;
	            TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	            TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	            TIM_TimeBaseInit(TIM3 , &TIM_TimeBaseStructure);
	LIS302DL_InitTypeDef  LIS302DL_InitStruct;
	uint8_t ctrl = 0x00;

	/* Set configuration of LIS302DL*/
	LIS302DL_InitStruct.Power_Mode = LIS302DL_LOWPOWERMODE_ACTIVE;
	LIS302DL_InitStruct.Output_DataRate = LIS302DL_DATARATE_100;
	LIS302DL_InitStruct.Axes_Enable = LIS302DL_X_ENABLE | LIS302DL_Y_ENABLE | LIS302DL_Z_ENABLE;
	LIS302DL_InitStruct.Full_Scale = LIS302DL_FULLSCALE_2_3;
	LIS302DL_InitStruct.Self_Test = LIS302DL_SELFTEST_NORMAL;
	LIS302DL_Init(&LIS302DL_InitStruct);

	LIS302DL_InterruptConfigTypeDef LIS302DL_InterruptStruct;
	/* Set configuration of Internal High Pass Filter of LIS302DL*/
	LIS302DL_InterruptStruct.Latch_Request = LIS302DL_INTERRUPTREQUEST_LATCHED;
	LIS302DL_InterruptStruct.SingleClick_Axes = LIS302DL_CLICKINTERRUPT_Z_ENABLE;
	LIS302DL_InterruptStruct.DoubleClick_Axes = LIS302DL_DOUBLECLICKINTERRUPT_Z_ENABLE;
	LIS302DL_InterruptConfig(&LIS302DL_InterruptStruct);

	STM32F4_Discovery_LEDInit(LED3);
	STM32F4_Discovery_LEDInit(LED4);
	STM32F4_Discovery_LEDInit(LED5);
	STM32F4_Discovery_LEDInit(LED6);
	STM32F4_Discovery_PBInit(BUTTON_USER, BUTTON_MODE_GPIO);

	STM32F4_Discovery_LEDOn(LED3);
	Delay(0xFFFF);
	STM32F4_Discovery_LEDOff(LED3);

	USBD_Init(&USB_OTG_dev,
#ifdef USE_USB_OTG_HS
		USB_OTG_HS_CORE_ID,
#else
		USB_OTG_FS_CORE_ID,
#endif
		&USR_desc,
		&USBD_HID_cb,
		&USR_cb);
	int przyspieszenie_x, przyspieszenie_y, przyspieszenie_z;
	przerwania();
	int temp=0;
	char button=0;
	int przyx[8];
	int przyy[8];
	int przyxx=0;
	int przyyy=0;
	int i=0;
	// zielone swiatelko na poczatek
	GPIO_SetBits(GPIOD, GPIO_Pin_12);

	while (1)

	{

		przyxx=0;
		przyyy=0;
		temp=0;


		Delay(0xFF);
		/*
		if (OutBuffer[0]&1)  	STM32F4_Discovery_LEDOn(LED3);
		else			STM32F4_Discovery_LEDOff(LED3);
		if (OutBuffer[0]&2)  	STM32F4_Discovery_LEDOn(LED4);
		else			STM32F4_Discovery_LEDOff(LED4);
		if (OutBuffer[0]&4)  	STM32F4_Discovery_LEDOn(LED5);
		else			STM32F4_Discovery_LEDOff(LED5);
		if (OutBuffer[0]&8)  	STM32F4_Discovery_LEDOn(LED6);
		else			STM32F4_Discovery_LEDOff(LED6);
		*/

		if ((STM32F4_Discovery_PBGetState(BUTTON_USER) == Bit_SET)){
			InBuffer[2] = 1;

		}
		else{
			InBuffer[2] = 0;

		}

		button = STM32F4_Discovery_PBGetState(BUTTON_USER);

		//	  {

		do{
		LIS302DL_Read(&przyspieszenie_x, LIS302DL_OUT_X_ADDR, 1);
		if(przyspieszenie_x>127)
		{
			przyspieszenie_x=przyspieszenie_x-1;
			przyspieszenie_x=(~przyspieszenie_x)&0xFF;
			przyspieszenie_x=-przyspieszenie_x;
		}
		LIS302DL_Read(&przyspieszenie_y, LIS302DL_OUT_Y_ADDR, 1);
		if(przyspieszenie_y>127)
		{
			przyspieszenie_y=przyspieszenie_y-1;
			przyspieszenie_y=(~przyspieszenie_y)&0xFF;
			przyspieszenie_y=-przyspieszenie_y;
		}
		LIS302DL_Read(&przyspieszenie_z, LIS302DL_OUT_Z_ADDR, 1);
		if(przyspieszenie_z>127)
		{
			przyspieszenie_z=przyspieszenie_z-1;
			przyspieszenie_z=(~przyspieszenie_z)&0xFF;
			przyspieszenie_z=-przyspieszenie_z;
		}
		przyx[temp]=przyspieszenie_x;
		przyy[temp]=przyspieszenie_y;
		temp++;
		}while(temp<8);
		for(i=0; i<8; i++){
		przyxx+=przyx[i];
		przyyy+=przyy[i];
		}
		przyspieszenie_x=przyxx/8;
		przyspieszenie_y=przyyy/8;

		InBuffer[1] = przyspieszenie_x;
		InBuffer[0] = przyspieszenie_y;
		//InBuffer[4] = przyspieszenie_z;
		//USBD_HID_SendReport (&USB_OTG_dev, InBuffer, 64);
		//  }
		//button = STM32F4_Discovery_PBGetState(BUTTON_USER);
/*
		if(TIM_GetCounter(TIM3) > 8000)
						{
					                  GPIO_ResetBits(GPIOD, GPIO_Pin_15);
					                  TIM_Cmd(TIM3, DISABLE);
					                   TIM_SetCounter(TIM3, 0);
					          }
		if(TIM_GetCounter(TIM4) > 8000)
							{
						                  GPIO_ResetBits(GPIOD, GPIO_Pin_15);
						                  TIM_Cmd(TIM4, DISABLE);
						                   TIM_SetCounter(TIM4, 0);
						          }
*/
		if(OutBuffer[0] == 1){



			GPIO_SetBits(GPIOD, GPIO_Pin_15);
					TIM_SetCounter(TIM4, 0);
					TIM_Cmd(TIM4, ENABLE);

			OutBuffer[0] =0;


		}else if(OutBuffer[1] == 2){

			//zapal żółtą, zgaś zieloną
			GPIO_SetBits(GPIOD, GPIO_Pin_13);
			GPIO_ResetBits(GPIOD, GPIO_Pin_12);
		}else if(OutBuffer[1] == 3){
			//zapal czerwoną, zgaś żółtą
			GPIO_SetBits(GPIOD, GPIO_Pin_14);
			GPIO_ResetBits(GPIOD, GPIO_Pin_13);

		}else if(OutBuffer[1] == 1 && OutBuffer[2] == 1  ){
			//zapal zielona, zgaś czerwona, zapal na chwile niebieska, zgas pomaranczowa i czerwona
			GPIO_SetBits(GPIOD, GPIO_Pin_12);
			GPIO_ResetBits(GPIOD, GPIO_Pin_14);
			GPIO_ResetBits(GPIOD, GPIO_Pin_13);
			GPIO_SetBits(GPIOD, GPIO_Pin_15);
			//TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
			TIM_SetCounter(TIM3, 0);
			TIM_Cmd(TIM3, ENABLE);

			OutBuffer[1] =0;
			OutBuffer[2] =0;


		}
		USBD_HID_SendReport (&USB_OTG_dev, InBuffer, 64);
	}


}

void przerwania(void){
    	NVIC_InitTypeDef NVIC_InitStructure;
    	// numer przerwania
    	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    	// priorytet główny
    	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
    	// subpriorytet
    	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
    	// uruchom dany kanał
    	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    	// zapisz wypełnioną strukturę do rejestrów
    	NVIC_Init(&NVIC_InitStructure);

    	// wyczyszczenie przerwania od timera 3 (wystąpiło przy konfiguracji timera)
    	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    	// zezwolenie na przerwania od przepełnienia dla timera 3
    	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

    	NVIC_InitTypeDef NVIC_InitStructure2;
    	// numer przerwania
    	NVIC_InitStructure2.NVIC_IRQChannel = TIM4_IRQn;
    	// priorytet główny
    	NVIC_InitStructure2.NVIC_IRQChannelPreemptionPriority = 0x00;
    	// subpriorytet
    	NVIC_InitStructure2.NVIC_IRQChannelSubPriority = 0x00;
    	// uruchom dany kanał
    	NVIC_InitStructure2.NVIC_IRQChannelCmd = ENABLE;
    	// zapisz wypełnioną strukturę do rejestrów
    	NVIC_Init(&NVIC_InitStructure2);

    	// wyczyszczenie przerwania od timera 3 (wystąpiło przy konfiguracji timera)
    	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
    	// zezwolenie na przerwania od przepełnienia dla timera 3
    	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
    }
void TIM3_IRQHandler(void)
    {
              if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
              {
                      GPIO_ResetBits(GPIOD, GPIO_Pin_15);
                      TIM_ClearITPendingBit(TIM3, TIM_IT_Update);

              }

    }

    void TIM4_IRQHandler(void)
    {

              if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
              {
                      GPIO_ResetBits(GPIOD, GPIO_Pin_15);
                      TIM_ClearITPendingBit(TIM4, TIM_IT_Update);

              }
    }

/**
* @brief  Inserts a delay time.
* @param  nTime: specifies the delay time length.
* @retval None
*/
void Delay(__IO uint32_t nTime)
{
	if (nTime != 0x00)
	{
		nTime--;
	}
}



#ifdef  USE_FULL_ASSERT

/**
* @brief  Reports the name of the source file and the source line number
*   where the assert_param error has occurred.
* @param  file: pointer to the source file name
* @param  line: assert_param error line source number
* @retval None
*/
void assert_failed(uint8_t* file, uint32_t line)
{ 
	/* User can add his own implementation to report the file name and line number,
	ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while (1)
	{
	}
}
#endif



/**
* @}
*/


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
