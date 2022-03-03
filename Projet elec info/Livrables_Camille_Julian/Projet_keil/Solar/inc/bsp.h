/*
 * bsp.h
 * Created on: 14 févr. 2021 * Author: darga
 */
#ifndef BSP_INC_BSP_H_
#define BSP_INC_BSP_H_
#include "stm32f0xx.h"
/*
 * fonctions du driver LED
 */
void BSP_LED_Init (void);
void BSP_LED_On (void);
void BSP_LED_Off (void);
void BSP_LED_Toggle (void);
//--------------------------
/* Fonctions du friver de bouton poussoir*/
void BSP_PB_Init(void);
uint8_t BSP_PB_Getstate(void);
//--------------------------
/* Fonctions pour PB3*/
void BSP_PB_Init_PB3(void);
void BSP_LED_On_PB3(void);
void BSP_LED_Off_PB3(void);
void BSP_LED_Toggle_PB3(void);
void BSP_LED_Init_PB3(void);
void BSP_ADC_Init_IT(void);
//--------------------------
/* Liason URT */
void BSP_Console_Init(void);
//--------------------------
/* Tp creation d'un bouton*/
void BSP_PA7_Init(void);
uint8_t BSP_PA7_GetState(void);
//------CAN----------
void BSP_ADC_Init(void);
int BSP_ADC_mesure(void); 
//------TIMER----------
void BSP_TIMER_Timebase_Init (void);
/*
* Delais avec un Timer : TIM6
*/
void BSP_DELAY_TIM_init (void);
void BSP_DELAY_TIM_ms (uint16_t ms);
void BSP_TIMER_Timebase_Init (void);
void BSP_TIMER_IC_Init(void) ;
//------------PWA---------------
void BSP_TIMER_PWM_Init(void);
void BSP_PWM_com(int);
//int ADC_Conversion(void);
#endif
/* BSP_INC_BSP_H_ */
