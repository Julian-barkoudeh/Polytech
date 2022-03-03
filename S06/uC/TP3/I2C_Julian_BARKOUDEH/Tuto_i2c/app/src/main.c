/*
 * main.c
 * Created on: Feb 3, 2021
* Author: BARKOUDEH */

#include "stm32f0xx.h"
#include "bsp.h"
#include "delay.h"
 #include "main.h"
static void SystemClock_Config(void);
static uint8_t wait_for_flags();
uint16_t rx_data[2];
int main(void) {
	// Définir l'adresse du composant VEML7700
	I2C1->CR2 &= ~I2C_CR2_SADD_Msk;
	I2C1->CR2 |= ((0x10 <<1U) <<I2C_CR2_SADD_Pos);
	// Mettre I2C en mode Write mode
	I2C1->CR2 &= ~I2C_CR2_RD_WRN;
	// Transfert NBYTES = 3, pas de AUTOEND
	I2C1->CR2 &= ~I2C_CR2_NBYTES;
	I2C1->CR2 |= (3 <<16U);
	I2C1->CR2 &= ~I2C_CR2_AUTOEND;
	// Demarrer la transaction I2C
	I2C1->CR2 |= I2C_CR2_START;
	wait_for_flags(); // TXIS #1
	// Envoyer adresse du registre
	I2C1->TXDR = 0x00;
	wait_for_flags(); // attente TXIS #2
	// Envoyer le premier octet (LSB)
	I2C1->TXDR = 0x00;
	wait_for_flags(); // attente TXIS #3
	// Envoyer le deuxième octet (MSB)
	I2C1->TXDR = 0x00;
	wait_for_flags(); // attente de TC
	// Générer une condition STOP
	I2C1->CR2 |= I2C_CR2_STOP;
	while(1) {
	}
}
/*
int main(void)
{
	// Configurer horloge du systeme pour 48MHz a partir de la source 8MHz HSE
	SystemClock_Config();
	// Initialiser la LED et le bouton bleu
	BSP_LED_Init();
	BSP_PB_Init();
	// Initialiser les pins de debug
	BSP_DBG_Pins_Init();
	// Initialiser la console de debogage
	BSP_Console_Init();
	//mon_printf("\r\n La est Console Ready!\r\n");
	//mon_printf("SYSCLK = %d Hz\r\n", SystemCoreClock);
	// Initialiser le périphérique I2C1
	BSP_I2C1_Init();
	// Adresse du composant VEML7700 (SLAVE) est 0x10
	I2C1->CR2 &= ~I2C_CR2_SADD_Msk;
	I2C1->CR2 |= ((0x10 <<1U) <<I2C_CR2_SADD_Pos);
	// Transfert avec NBYTES=1, pas de AUTOEND
	I2C1->CR2 &= ~I2C_CR2_NBYTES;
	I2C1->CR2 |= (1 <<16U);
	I2C1->CR2 &= ~I2C_CR2_AUTOEND;
	// Demarrer la transaction I2C
	I2C1->CR2 |= I2C_CR2_START; // <-- Mettre un Point arret ici
	wait_for_flags();
	// attente de TXIS
	//TXIS a été activé, passez à l'envoi du code de commande.
	I2C1->TXDR = 0x00;
	wait_for_flags();
	// attente de TC
	// Mettre l'I2C en mode lecture
	I2C1->CR2 |= I2C_CR2_RD_WRN;
	// Transfert avec NBYTES=1, pas de AUTOEND
	I2C1->CR2 &= ~I2C_CR2_NBYTES;
	I2C1->CR2 |= (2 <<16U);
	I2C1->CR2 &= ~I2C_CR2_AUTOEND;
	// Relancer la transaction
	I2C1->CR2 |= I2C_CR2_START;
	wait_for_flags();
	// attente RXNE
	// Lecture du premier octet (LSB)
	rx_data = I2C1->RXDR;
	wait_for_flags();
	// attente RXNE
	// Lecture du deuxième octet (MSB)
	rx_data += (I2C1->RXDR <<8U);
	// Generer une condition STOP
	I2C1->CR2 |= I2C_CR2_STOP;
	while(1) {
	}
}*/
//******************************Partie 6 ****************
/* * Attendre et notifier les drapeaux etats du bus I2C
 * fonction aide pour debug I2C */
static uint8_t wait_for_flags(void) {
	uint8_t exit = 0;
	// Reset des drapeaux STOPF et NACKF
	I2C1->ICR |= I2C_ICR_STOPCF;
	I2C1->ICR |= I2C_ICR_NACKCF;
	while(exit == 0) {
		// TXIS -> PA0 // Quitter attente si TXIS passe a '1'
		if ((I2C1->ISR & I2C_ISR_TXIS) != 0) {
			GPIOA->BSRR = GPIO_BSRR_BS_0;
			// mise a '1' de PA0
			exit = 1;
		}
		else GPIOA->BSRR = GPIO_BSRR_BR_0;
		// mise a '0' de PA0
		// TC -> PA4
		// Quitter attente si TC passe a '1'
		if ((I2C1->ISR & I2C_ISR_TC) != 0) {
			GPIOA->BSRR = GPIO_BSRR_BS_4;
			// mise a '1' de PA4 exit = 3;
			} else GPIOA->BSRR = GPIO_BSRR_BR_4;
		// mise a '0' de PA4
		// STOPF-> PC1
		// Quitter attente si STOPF passe a '1'
		if ((I2C1->ISR & I2C_ISR_STOPF) != 0) {
			GPIOC->BSRR = GPIO_BSRR_BS_1;
			// mise a '1' de PC1
			exit = 2;
		}
		else GPIOC->BSRR = GPIO_BSRR_BR_1;
		// mise a '0' de PC1
		// Ajouter autres sortie de drapeaux // ...
		}
return exit;
}
/*static uint8_t wait_for_flags()
{
	uint8_t exit = 0;
	while(exit == 0)
	{
		// TXIS -> PA0
		// Quitter attente si TXIS passe a '1'
		if ((I2C1->ISR & I2C_ISR_TXIS) != 0)
		{
			GPIOA->BSRR = GPIO_BSRR_BS_0; // mise a '1' de PA0
			exit = 1;
		}
		else GPIOA->BSRR = GPIO_BSRR_BR_0; // mise a '0' de PA0
		// Ajouter autres sortie de drapeaux
		// ...
		// TC-> PA1
		// Quitter attente si RXNE passe a '1'
		if ((I2C1->ISR & I2C_ISR_TC) != 0) {
			GPIOA->BSRR = GPIO_BSRR_BS_1;
			// mise a '1' de PA1
			exit = 1;
		}
		else GPIOA->BSRR = GPIO_BSRR_BR_1; // mise a '0' de PA1
		// RXNE-> PA1
		// Quitter attente si RXNE passe a '1'
		if ((I2C1->ISR & I2C_ISR_RXNE) != 0)
		{
			GPIOA->BSRR = GPIO_BSRR_BS_1;
			// mise a '1' de PA1
			exit = 1;
		}
		else GPIOA->BSRR = GPIO_BSRR_BR_1; // mise a '0' de PA1
	}
	return exit;
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

