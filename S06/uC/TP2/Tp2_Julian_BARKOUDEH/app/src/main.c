/*
 * main.c
 * Created on: Feb 23, 2021
* Author: BARKOUDEH */

#include "stm32f0xx.h"
#include "bsp.h"
#include "delay.h"
 #include "main.h"
static void SystemClock_Config(void);

// Main program
// variables globales
uint8_t timebase_irq = 0;
uint16_t in, out;
uint8_t button_irq;
int main(void)
{
	float c1, c2; // les coef du filtre
	uint16_t x = 0; // Entree (Input) du Filtre
	uint32_t y = 0; // Sortie (Output) du filtre
	// configuration des coefs du filtre
	c1 = 482; // 0.11765f *2^12
	c2 = 3614; // 0.88235f *2^12
	// Configure System Clock for 48MHz from 8MHz HSE
	SystemClock_Config();
	//Initialisation de la Led verte
	BSP_LED_Init();
	// initialisation de la base de temps de 10 ms
	BSP_TIMER_Timebase_Init();
	BSP_NVIC_Init();
	// Initialisation de ADC
	BSP_ADC_Init();
	// Initialisation de DAC
	BSP_DAC_Init();
	while(1)
	{
		// Executer tout les 10 ms
		if (timebase_irq == 1)
		{
			// Demmarrer la mesure de performance
			BSP_LED_On();
			// Lecture entree ADC
			while ( (ADC1->ISR & ADC_ISR_EOC) != ADC_ISR_EOC );
			in = ADC1->DR;
			// etage de filtrage
			x = (float)in;
			y = (c1*x) + (c2*y);
			y = (y >>12U); // retrait de la partie decimale
			out = y;
			// envoi de la donnee sur la sortie DAC
			DAC->DHR12R1 = out;
			// Arret la mesure de performance
			BSP_LED_Off();
			timebase_irq = 0;
		}
	}
}
/*
* Clock configuration for the Nucleo STM32F072RB board
* HSE input Bypass Mode -> 8MHz
* SYSCLK, AHB, APB1 -> 48MHz
* PA8 as MCO with /16 prescaler -> 3MHz
*
*/

/*
* Clock configuration for the Nucleo STM32F072RB board
* HSE input Bypass Mode -> 8MHz
* SYSCLK, AHB, APB1 -> 48MHz
* PA8 as MCO with /16 prescaler -> 3MHz
*
*/
	static void SystemClock_Config() {
			uint32_t HSE_Status;
			uint32_t PLL_Status;
			uint32_t SW_Status;
			uint32_t timeout = 0;
			timeout = 1000000;
		// Start HSE in Bypass Mode
			RCC->CR |= RCC_CR_HSEBYP;
			RCC->CR |= RCC_CR_HSEON;
		// Wait until HSE is ready
			do
			{
				HSE_Status = RCC->CR & RCC_CR_HSERDY_Msk;
				timeout--;
			} while ((HSE_Status == 0) && (timeout > 0));
		// Select HSE as PLL input source
			RCC->CFGR &= ~RCC_CFGR_PLLSRC_Msk;
			RCC->CFGR |= (0x02 <<RCC_CFGR_PLLSRC_Pos);
		// Set PLL PREDIV to /1 RCC->CFGR2 = 0x00000000;
		// Set PLL MUL to x6
			RCC->CFGR &= ~RCC_CFGR_PLLMUL_Msk;
			RCC->CFGR |= (0x04 <<RCC_CFGR_PLLMUL_Pos);
		// Enable the main PLL
			RCC-> CR |= RCC_CR_PLLON;
			// Wait until PLL is ready
			do
			{
				PLL_Status = RCC->CR & RCC_CR_PLLRDY_Msk;
				timeout--;
			} while ((PLL_Status == 0) && (timeout > 0));
			// Set AHB prescaler to /1
			RCC->CFGR &= ~RCC_CFGR_HPRE_Msk;
			RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
			//Set APB1 prescaler to /1
			RCC->CFGR &= ~RCC_CFGR_PPRE_Msk;
			RCC->CFGR |= RCC_CFGR_PPRE_DIV1;
			// Enable FLASH Prefetch Buffer and set Flash Latency
			FLASH->ACR = FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY;
			/* --- Until this point, MCU was still clocked by HSI at 8MHz ---*/ /* --- Switching to PLL at 48MHz Now! Fasten your seat belt! ---*/
			// Select the main PLL as system clock source
			RCC->CFGR &= ~RCC_CFGR_SW;
			RCC->CFGR |= RCC_CFGR_SW_PLL;
			// Wait until PLL becomes main switch input
			do
			{
				SW_Status = (RCC->CFGR & RCC_CFGR_SWS_Msk); timeout--;
			} while ((SW_Status != RCC_CFGR_SWS_PLL) && (timeout > 0));

			/* --- Here we go! ---*/
			/*--- Use PA8 as MCO output at 48/16 = 3MHz ---*/
			// Set MCO source as SYSCLK (48MHz)
			RCC->CFGR &= ~RCC_CFGR_MCO_Msk;
			RCC->CFGR |= RCC_CFGR_MCOSEL_SYSCLK;
			// Set MCO prescaler to /16 -> 3MHz
			RCC->CFGR &= ~RCC_CFGR_MCOPRE_Msk;
			RCC->CFGR |= RCC_CFGR_MCOPRE_DIV16;
			// Enable GPIOA clock
			RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
			// Configure PA8 as Alternate function
			GPIOA->MODER &= ~GPIO_MODER_MODER8_Msk;
			GPIOA->MODER |= (0x02 <<GPIO_MODER_MODER8_Pos);
			// Set to AF0 (MCO output)
			GPIOA->AFR[1] &= ~(0x0000000F);
			GPIOA->AFR[1] |= (0x00000000);
			SystemCoreClockUpdate();
		}

