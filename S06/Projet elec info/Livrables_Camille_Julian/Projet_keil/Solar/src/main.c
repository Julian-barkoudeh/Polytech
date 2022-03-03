/*
 * main.c
 * Created on: Feb 23, 2021
* Author: BARKOUDEH */

#include "stm32f0xx.h"
#include "bsp.h"
#include "delay.h"
 #include "main.h"
#define max_pan  2000
#define max_tilt  1950
#define min_pan  1500
#define min_tilt  1500

static void SystemClock_Config(void);

//Programme

//Vars globales
uint8_t cmpt= 1;
int16_t r1,r0,r2;
//Definition des channel de conversion ADC 
// r0 												r1
//							r2
int main()
{

	int8_t delta = 50;
    int tilt = 1500;
    int pan = 1500;
    SystemClock_Config();
    //Initialisation PWM
    BSP_Console_Init();
    mon_printf("La Console est ready!\r\n");
		BSP_TIMER_PWM_Init();

    //Initaialisation de L'ADC
    BSP_ADC_Init_IT();
    //BSP_PWM_HS422_Init();
    // Boucle Infini
    while(1)
    {
				mon_printf("r0 : %d\n\r", r0);
        mon_printf("r1 : %d\n\r", r1);
        mon_printf("r2 : %d\n\r", r2);
        mon_printf("Valeur pan : %d\n\r", pan);
        mon_printf("Valeur tilt : %d\n\r", tilt);

        //Reglage du Pan
        if(r1-r0 > delta)
        {
            if (pan < max_pan){
							mon_printf("***********Aller à Droite*************\r\n");
                pan = pan +6;
						}
        }
        if(r0-r1 > delta)
        {
            if (pan > min_pan){
							mon_printf("***********Aller à Gauche*************\r\n");
                pan = pan - 6;
						}
        }

        //Reglage du Tilt
        if(r1-r2 > delta)
        {
            if (tilt < max_tilt){
							mon_printf("***********Monter*************\r\n");
                tilt = tilt + 6;
						}
        }
        if(r2-r1 > delta)
        {
            if (tilt > min_tilt){
							mon_printf("*********** Descendre *************\r\n");
                tilt  = tilt -6;
						}
        }

        TIM1->CCR2 = pan; 
        TIM1->CCR1 = tilt;

        BSP_DELAY_ms(20);
    }

}
				
		
		
		
		/*
		while(1){
			//while(rc<2500){
			if(BSP_PB_GetState() == 1){
				rc = rc + 100;
				BSP_PWM_com(rc);
				j_printf("rapport cyclique =%d\r\n", rc);
				BSP_DELAY_ms(200);
			}
			if(rc == 2500){
				rc = 1100;
			}
		
		
			BSP_DELAY_ms(500);
			while(rc>1500){
				rc = rc - 100;
				j_printf("rapport cyclique =%d\r\n", rc);
				BSP_PWM_com(rc);
				BSP_DELAY_ms(200);
			}				BSP_DELAY_ms(200);
				
			}
}*/

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

