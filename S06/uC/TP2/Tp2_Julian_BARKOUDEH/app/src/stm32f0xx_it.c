/**
  ******************************************************************************
  * @file    Templates/Src/stm32f0xx_it.c 
  * @author  MCD Application Team
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <main.h>
#include "stm32f0xx_it.h"


/** @addtogroup STM32F0xx_HAL_Examples
  * @{
  */

/** @addtogroup Templates
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  //HAL_IncTick();
}

/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/


/**
  * @}
  */ 

/**
  * @}
  */
/******************************************************************************/
/* STM32F0xx Peripherals Interrupt Handlers */
/* Add here the Interrupt Handler for the used peripheral(s) (PPP), for the */
/* available peripheral interrupt handler's name please refer to the startup */
/* file (startup_stm32f0xx.s). */
/******************************************************************************/
/**
* This function handles EXTI line 13 interrupt request.
*/
/**
* This function handles EXTI line 13 interrupt request.
*/
extern uint8_t button_irq;
void EXTI4_15_IRQHandler()
{
	// Verifiver si cest PC13 (Ligne 13) qui a declencher interruption
	if ((EXTI->PR & EXTI_PR_PR13_Msk) != 0)
	{
		// Acquitter ou valider la demande interruption
		// Reset du drapeau en ecrivant '1' sur le bit b13 de EXTI_PR
		EXTI->PR = EXTI_PR_PR13;
		// Tache a realiser
		button_irq++;
	}
}
/*
* This function handles TIM6 interrupts
*/
extern uint8_t timebase_irq;
void TIM6_DAC_IRQHandler()
{
	// Verifier que cest le debordement de Timer TIM6 qui a declencher interruption
	if ((TIM6->SR & TIM_SR_UIF) == TIM_SR_UIF)
	{
		// CAcquitter ou valider la demande interruption
		TIM6->SR &= ~TIM_SR_UIF;
		// Tache a realiser
		timebase_irq = 1;
	}
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
