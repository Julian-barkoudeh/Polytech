/*
 *  bsp.c
 * Created on: 14 févr. 2021 * Author: darga
 */

#include "bsp.h"
/*
 * BSP_LED_Init()
 * Initialise la broche PA5 (LED) en sortie, mode Push-pull, vitesse de rafraichissement High-Speed, pas de resistance de tirage
 * Etat initial mus a '0'
 */
void BSP_LED_Init()
{
	//activation de horloge du peripherique GPIOA
	// mettre le bit b17 du registre RCC_AHBENR a '1'
	// voir page 128 du manuel technique (User Manuel) du Microcontrôleur STM32F072RB
	// le bit b17 de RCC_AHBENR est egalement defini = RCC_AHBENR_GPIOAEN dans le fichier stm32f0xx.h
	RCC->AHBENR |= (1<<17);
	// ou
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

	// Configurer la broche PA5 en sortie
	// Ecrire "01" sur les bits b11b10 du registre (GPIOA_MODER)
	GPIOA->MODER &= ~(1<<11); GPIOA->MODER |= (1<<10);
	// Choisir option electronique Push-pull pour la sortie PA5
	// Ecrire "0" sur le bit b5 du registre (GPIOA_OTYPER)
	GPIOA->OTYPER &= ~(1<<5);
	// Choisir option electronique high speed pour la vitesse de rafraichissement pour la sortie PA5
	// Ecrire "11" sur les bits b11b10 du registre (GPIOx_OSPEEDR)
	GPIOA->OSPEEDR |= (1<<11); GPIOA->OSPEEDR |= (1<<10);
	// Deactiver les resistances de tirages (Pull-up ou Pull-down) pour la sortie PA5
	// Ecrire "00" sur les bits b11b10 du registre (GPIOx_PUPDR)
	GPIOA->PUPDR &= ~(1<<11);
	GPIOA->PUPDR &= ~(1<<10);
	// Mettre l'état initial de PA5 sur OFF
	GPIOA->ODR &= ~(1<<5);
}
/*
* BSP_LED_On()
* Allume la LED lier a la broche PA5
*/
void BSP_LED_On()
{
	// Ecrire "1" sur le bit b5 du registre (GPIOA_ODR)
	GPIOA->ODR |= (1<<5);
}
/*
 * BSP_LED_Off()
 * Eteint la LED lier a la broche PA5
 */
void BSP_LED_Off()
{
	// Ecrire "0" sur le bit b5 du registre (GPIOA_ODR)
	GPIOA->ODR &= ~(1<<5);
}
/*
  BSP_LED_Toggle() * Change etat de la LED lier a la broche PA5 */
void BSP_LED_Toggle()
{
	GPIOA->ODR ^= (1<<5);


/*
 * BSP_PB_Init()
 * Initialise la broche PC13 (Bouton poussoir) en input sans les resistance de tirages Pull-up/Pull-down
 */
}
void BSP_PB_Init()
{
	//activation de horloge du peripherique GPIOC
	// mettre le bit b19 du registre RCC_AHBENR a '1'
	RCC->AHBENR |= (1<<19);

	// Configurer la broche PC13 en Input
	// Ecrire "00" sur les bits b27b26 du registre (GPIOC_MODER)
	GPIOC->MODER &= ~(1<<27);
	GPIOC->MODER &= ~(1<<26);
	// Deactiver les resistances de tirages (Pull-up ou Pull-down) pour la sortie PA5
	// Ecrire "00" sur les bits b27b26 du registre (GPIOC_PUPDR)
	GPIOC->PUPDR &= ~(1<<27);
	GPIOC->PUPDR &= ~(1<<26);
}
	/*
	 * BSP_PB_GetState()
	 * Renvoi etat du bouton (0=Non Appuyer, 1=Appuyer)
	 */

uint8_t BSP_PB_GetState()
	{
		uint8_t state;
	if ((GPIOC->IDR & (1<<13)) == (1<<13))
	{
		state = 0;
	}
	else
	{
		state = 1;
	}
	return state;
}

/*------------------------------
 * Fonctions pour PB3
 */
void BSP_LED_Init_PB3()
{
	//activation de horloge du peripherique GPIOA
	// mettre le bit b17 du registre RCC_AHBENR a '1'
	// voir page 128 du manuel technique (User Manuel) du Microcontrôleur STM32F072RB
	// le bit b17 de RCC_AHBENR est egalement defini = RCC_AHBENR_GPIOAEN dans le fichier stm32f0xx.h
	RCC->AHBENR |= (1<<18);
	// ou
	//RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

	// Configurer la broche PA5 en sortie
	// Ecrire "01" sur les bits b11b10 du registre (GPIOA_MODER)
	GPIOB->MODER &= ~(1<<7);
	GPIOB->MODER |= (1<<6);
	// Choisir option electronique Push-pull pour la sortie PA5
	// Ecrire "0" sur le bit b5 du registre (GPIOA_OTYPER)
	GPIOB->OTYPER &= ~(1<<3);
	// Choisir option electronique high speed pour la vitesse de rafraichissement pour la sortie PA5
	// Ecrire "11" sur les bits b11b10 du registre (GPIOx_OSPEEDR)
	GPIOB->OSPEEDR |= (1<<7);
	GPIOB->OSPEEDR |= (1<<6);
	// Deactiver les resistances de tirages (Pull-up ou Pull-down) pour la sortie PA5
	// Ecrire "00" sur les bits b11b10 du registre (GPIOx_PUPDR)
	GPIOB->PUPDR &= ~(1<<7);
	GPIOB->PUPDR &= ~(1<<6);
	// Mettre l'état initial de PA5 sur OFF
	GPIOB->ODR &= ~(1<<3);
}

	/*
	 * BSP_PB_GetState()
	 * Renvoi etat du bouton (0=Non Appuyer, 1=Appuyer)
	 */

/*
* BSP_LED_On()
* Allume la LED lier a la broche PB3
*/
void BSP_LED_On_PB3()
{
	// Ecrire "1" sur le bit b5 du registre (GPIOA_ODR)
	GPIOB->ODR |= (1<<3);
}
/*
 * BSP_LED_Off()
 * Eteint la LED lier a la broche PB3
 */
void BSP_LED_Off_PB3()
{
	// Ecrire "0" sur le bit b5 du registre (GPIOA_ODR)
	GPIOB->ODR &= ~(1<<3);
}
/*
  BSP_LED_Toggle() * Change etat de la LED lier a la broche PA5 */
void BSP_LED_Toggle_PB3()
{
	GPIOB->ODR ^= (1<<3);
}

/*
 * BSP_PB_Init()
 * Initialise la broche PC18 (Bouton poussoir) en input sans les resistance de tirages Pull-up/Pull-down
 */

/*-----------------------------------------------------------------------------------
 * Codes pour liaison URT
 */

/*
 * BSP_Console_Init()
 * USART2 @ 115200 Full Duplex
 * 1 start - 8-bit - 1 stop
 * TX -> PA2 (AF1)
 * RX -> PA3 (AF1) */
void BSP_Console_Init()
{
	//activer horloge du peripherique GPIOA
	//mettre le bit b17 du registre RCC_AHBENR a '1'
	// voir page 128 du manuel technique (User Manuel) du Microcontrôleur STM32F072RB
	//le bit b17 de RCC_AHBENR est egalement defini = RCC_AHBENR_GPIOAEN dans le fichier stm32f0xx.h
	RCC->AHBENR |= (1<<17); // ou RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

	// Choisir le mode Alternate Function (AF) pour les broches PA2 et PA3
	// pour PA2 : ecrire "10" sur les bits b5b4 du registre GPIOA_MODER
	GPIOA->MODER |=(1<<5);
	GPIOA->MODER &=~(1<<4);
	// pour PA3 : ecrire "10" sur les bits b7b6 du registreGPIOA_MODER
	GPIOA->MODER |=(1<<7);
	GPIOA->MODER &=~(1<<6);
	// Choisir la fonction AF1 (USART2) pour les broches PA2 et PA3
	// pour PA2 : ecrire "0001" sur les bits b11b10b9b8 du registre GPIOA_AFRL = GPIO->AFR[0]
	GPIOA->AFR[0] &= ~(1<<11);
	GPIOA->AFR[0] &= ~(1<<10);
	GPIOA->AFR[0] &= ~(1<<9);
	GPIOA->AFR[0] |= (1<<8);
	// Choisir la fonction AF1 (USART2) pour les broches PA2 et PA3
	// pour PA3 : ecrire "0001" sur les bits b15b14b13b12 du registre GPIOA_AFRL = GPIO->AFR[0]
	GPIOA->AFR[0] &= ~(1<<15);
	GPIOA->AFR[0] &= ~(1<<14);
	GPIOA->AFR[0] &= ~(1<<13);
	GPIOA->AFR[0] |= (1<<12);
	//activer horloge du peripherique USART2
	// mettre '1' le bit b17 du registre (RCC_APB1ENR)
	// voir page 131 du manuel technique (User Manuel) du Microcontrôleur STM32F072RB
	RCC -> APB1ENR |= (1<<17);
	//Reset de la configuration de USART2 : Mise a zero des registres de control de USART2
	//USART2_CR1, USART2_CR2 , USART2_CR3
	// On utilise les valeurs par defaut /
	// 8-bits de donnees
	// 1 bit START
	// 1 bit STOP
	// desactivation de CTS/RTS
	USART2->CR1 = 0x00000000;
	USART2->CR2 = 0x00000000;
	USART2->CR3 = 0x00000000;
	// Choisir la source PCLK (APB1) comme source horloge de USART2 : Valeur par defaut
	// PCLK -> 48 MHz
	// mettre "00" sur les bits b17b16 du registre (RCC_CFGR3)
	// voir page 140 du reference manual
	RCC->CFGR3 &= ~(1<<17);
	RCC->CFGR3 &= ~(1<<16);
	// Configuration du Baud Rate = 115200
	// sans oversampling 8 bits (OVER8=0) et Fck=48MHz, USARTDIV = 48E6/115200 = 416.6666
	// BRR = 417 -> Baud Rate = 115107.9137 -> 0.08% erreur
	// avec oversampling 8 bits (OVER8=1) and Fck=48MHz, USARTDIV = 2*48E6/115200 = 833.3333
	// BRR = 833 -> Baud Rate = 115246.0984 -> 0.04% error (Meilleur choix)
	// choix oversampling 8 bits (OVER8=1)
	// mettre a '1' le bit b15 de USART2_CR1
	USART2->CR1 |= (1<<15);
	// ecrire la valeur du Baud Rate dans le registre USART2_BRR
	USART2->BRR = 833;
	// Activer la transmision : ecrire '1' sur le bit b3 de USART2_CR1
	USART2->CR1 |= (1<<3);
	// Activer la reception : ecrire '1' sur le bit b2 de USART2_CR1
	USART2->CR1 |= (1<<2);
	// activer le peripherique USART2 en dernier
	// mettre a '1' le bit bit b0 de USART2_CR1
	USART2->CR1 |= (1<<0);
}
//---------------------------------------------------------------------------------------
/* Tp création d'un bouton pousoire */
void BSP_PA7_Init()
{
	//activation de horloge du peripherique GPIOC
	// mettre le bit b17 du registre RCC_AHBENR a '1'
	RCC->AHBENR |= (1<<17);

	// Configurer la broche PA7 en Input
	// Ecrire "00" sur les bits b27b26 du registre (GPIOC_MODER)
	GPIOA->MODER &= ~(1<<15);
	GPIOA->MODER &= ~(1<<14);
	// Deactiver les resistances de tirages (Pull-up ou Pull-down) pour la sortie PA5
	// Ecrire "00" sur les bits b27b26 du registre (GPIOC_PUPDR)
	GPIOA->PUPDR &= ~(1<<15);
	GPIOA->PUPDR &= ~(1<<14);
}
uint8_t BSP_PA7_GetState()
	{
		uint8_t state;
	if ((GPIOA->IDR & (1<<7)) == (1<<7))
	{
		state = 0;
	}
	else
	{
		state = 1;
	}
	return state;
}
//----------------------------------------------------------------------------
//CAN
/*
 * ADC_Init()
 * Initialise ADC pour la conversion sur un seul canal
 * canal 11 -> pin PC1
 */
void BSP_ADC_Init()
{
	// Activation de horloge du GPIOC
	// Mettre a '1' le bit b19 du registre RCC_AHBENR
	RCC->AHBENR |= (1<<19);
	// Configure le pin PC1 en mode Analog
	// Mettre à "11" les bits b3b2 du registre GPIOC_MODER
	GPIOC->MODER |= (0x03 <<1);
	// Activation de horloge de ADC
	// Mettre a '1' le bit b9 du registre RCC_APB2ENR
	// voir page 130 pour les autres bits
	RCC->APB2ENR |= (1<<9);
	// Reset de la configuration de ADC
	// Mise a zero des regsitres de configuration de ADC
	ADC1->CR = 0x00000000;
	ADC1->CFGR1 = 0x00000000;
	ADC1->CFGR2 = 0x00000000;
	ADC1->CHSELR = 0x00000000;
	// Choix du mode de conversion
	// bit b13 (CONT) du registre ADC1_CFGR1
	// '0' : conversion une seule fois : a la demande
	// '1' : conversion une en continue
	ADC1->CFGR1 |= (1<<13);
	// Choix de la resolution (nombre de bits des data)
	// bits b4b3 (Data resolution)
	// 00: 12 bits
	// 01: 10 bits
	// 10: 8 bits
	// 11: 6 bits
	ADC1->CFGR1 &= ~(0x03 <<4);
	// Choix de la source horloge pour ADC
	// bits b31b30 CKMODE[1:0]: ADC clock mode
	// 00: ADCCLK (Asynchronous clock mode), generated at product level (refer to RCC section)
	// 01: PCLK/2 (Synchronous clock mode)
	// 10: PCLK/4 (Synchronous clock mode)
	// 11: Reserved
	ADC1->CFGR2 |= (0x01 <<31UL);
	// Choix de la periode chantillonnage
	// Bits b2b1b0 (SMP[2:0]: Sampling time selection) du registre ADC sampling time register (ADC_SMPR)
	// 000: 1.5 ADC clock cycles
	// 001: 7.5 ADC clock cycles
	// 010: 13.5 ADC clock cycles
	// 011: 28.5 ADC clock cycles
	// 100: 41.5 ADC clock cycles
	// 101: 55.5 ADC clock cycles
	// 110: 71.5 ADC clock cycles
	// 111: 239.5 ADC clock cycles ADC1->SMPR = 0x03;
	// Selectionner le canal 11 pour la conversion
	// bit b11 du registre ADC channel selection register (ADC_CHSELR)
	// Select channel 11
	ADC1->CHSELR |= ADC_CHSELR_CHSEL11;
	// Activer ADC
	// Mettre a '1' le bit b0 du registre ADC_CR
	ADC1->CR |= (1<<0);
	// Demarrer la conversion
	// Mettre a '1' le bit b2 du registre ADC_CR
	ADC1->CR |= (1<<2);
}
//-------------------------------------------------------------
/* -----------------Timers------------------------------------
 */
/*
* BSP_TIMER_Timebase_Init()
* TIM6 cadenser a 48MHz
* Prescaler = 48000 -> periode de comptage = 1ms
* Auto-reload = 1000 -> periode de mis a jour = 1s
*/

void BSP_TIMER_Timebase_Init()
{
	// activer horloge du peripherique TIM6
	// mettre a '1' le bit b4 (TIM6EN) du registre RCC_APB1ENR
	// voir page 131 du manuel de reference
	RCC->APB1ENR |= (1<<4);
	// le bit b4 est defini comme etant RCC_APB1ENR_TIM6EN
	// Faire un Reset de configuration du TIM6 : mise a zero des registres
	// TIM6_CR1 et TIM6_CR2
	// voir page 543 a 544 du manuel de reference
	TIM6->CR1 = 0x0000;
	TIM6->CR2 = 0x0000;
	// Configuration frequence de comptage
	// Prescaler : registre TIM6_PSC
	// Fck = 48MHz -> /48000 = 1KHz frequence de comptage
	TIM6->PSC = (uint16_t) 48 -1;
	// Configuration periode des evenements
	// Prescaler : registre TIM6_ARR
	// 1000 /1000 = 1s
	TIM6->ARR = (uint16_t) 200 -1;
	// Activation auto-reload preload : prechargement
	// mettre a '1' le bit b7 du registre TIM6_CR1
	TIM6->CR1 |= (1<<7);
	// Demarrer le Timer TIM6
	// Mettre a '1' le bit b0 du registre TIM6_CR1
	TIM6->CR1 |= (1<<0);
}

/*
 * BSP_TIMER_IC_Init()
 * Configuration TIM3 en mode Input Capture
 * Channel 1 -> PB4 (AF1) */
/* * BSP_TIMER_IC_Init() * Configuration TIM3 en mode Input Capture * Channel 1 -> PB4 (AF1) */
void BSP_TIMER_IC_Init()
{
	// activer horloge de GPIOB
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	// configurer PB4 en mode Alternate function (AF)
	GPIOB->MODER &= ~(GPIO_MODER_MODER4_Msk);
	GPIOB->MODER |= (0x02 <<GPIO_MODER_MODER4_Pos);
	// Choisir AF1 (TIM3_CH1) pour PB4
	GPIOB->AFR[0] &= ~(0x000F0000);
	GPIOB->AFR[0] |= (0x00010000);
	// activer horloge de TIM3
	RCC -> APB1ENR |= RCC_APB1ENR_TIM3EN;
	// Reset de la configuration de TIM3
	TIM3->CR1 = 0x0000;
	TIM3->CR2 = 0x0000;
	TIM3->CCER = 0x0000;
	// configuration du prescaler de TIM3
	// Fck = 48MHz -> /48000 = 1KHz frequence de comptage
	TIM3->PSC = (uint16_t) 48000 -1;
	// Configuration de Auto-Reload a sa valeur max
	TIM3->ARR = (uint16_t) 0xFFFF;
	// Reset de la configuration du mode Input Capture
	TIM3->CCMR1 = 0x0000;
	TIM3->CCMR2 = 0x0000;
	// Choisir le Channel 1 (canal 1) comme input de TI1
	TIM3->CCMR1 |= (0x01 <<TIM_CCMR1_CC1S_Pos);
	// Choisir aussi le Channel 2 (canal 2) comme input de TI1
	TIM3->CCMR1 |= (0x02 <<TIM_CCMR1_CC2S_Pos);
	// Configurer le filtre avec N=8 : 8 mesures : sur les 2 cannaux
	TIM3->CCMR1 |= (0x03 <<TIM_CCMR1_IC1F_Pos) | (0x03 <<TIM_CCMR1_IC2F_Pos);
	// Choisir le mode de detection : falling edge pour le channel 1
	TIM3->CCER |= (0x00 <<TIM_CCER_CC1NP_Pos) | (0x01 <<TIM_CCER_CC1P_Pos);
	// Choisir le mode de detection : rising edge pour le channel 2
	TIM3->CCER |= (0x00 <<TIM_CCER_CC2NP_Pos) | (0x00 <<TIM_CCER_CC2P_Pos);
	// Activer la capture sur le channel 1 et sur le channel 2
	TIM3->CCER |= (0x01 <<TIM_CCER_CC1E_Pos) | (0x01 <<TIM_CCER_CC2E_Pos);
	// Activer le TIM3
	TIM3->CR1 |= TIM_CR1_CEN;
}

//-----------------------Signal PWM--------------------------------
// BSP_PWM_Init()
//Fonction initialisation d'un signal PWM sur le pin PA9
void BSP_PWM_Init(){
	RCC->AHBENR |= (1<<17);
    // Ecrire "10" sur les bits b11b10 du registre (GPIOA_MODER) (AF)
    GPIOA->MODER |= (1<<17);
    GPIOA->MODER &= ~(1<<16);
    //Def de l'AF
    //Ecrire "0010" (AF2) sur b3b2b1b0
    GPIOA->AFR[1] &= ~(1<<3);
    GPIOA->AFR[1] &= ~(1<<2);
    GPIOA->AFR[1] |= (1<<1);
    GPIOA->AFR[1] &= ~(1<<0);
    //APB2 timer1
    RCC->APB2ENR |= (1<<11);
	//Configuration des caractéristiques du signal PWM
    //Time on
	TIM1->PSC = 47;
	//Résolution
    TIM1->ARR = 180;
    // Rapport cyclique
    TIM1->CCR1 = 1;
    TIM1->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1| TIM_CCMR1_OC1PE;
    TIM1->CCER |= TIM_CCER_CC1E;
    TIM1->BDTR |= TIM_BDTR_MOE;
    TIM1->CR1 |= TIM_CR1_CMS_0 | TIM_CR1_CEN;
    TIM1->EGR |= TIM_EGR_UG;
}
void BSP_PWM_com(uint8_t rc){
					uint8_t duty;
					duty =(180*rc)/100;
	j_printf("Le rapport cyclique pour CH1 est de: %d\r\n", duty);
					TIM1->CCR1 =duty;
					TIM1->CCR2 = duty;
}

//--------------------------------------------------------
//-----------------Tuto DAC-------------------------------
/* * DAC_Init() * Initialise le DAC une seule sortie * sur channel 1 -> pin PA4 */

void BSP_DAC_Init()
{
	// activer horloge du GPIOA
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	// Configurer le pin PA4 en mode Analog
	GPIOA->MODER &= ~GPIO_MODER_MODER4_Msk;
	GPIOA->MODER |= (0x03 <<GPIO_MODER_MODER4_Pos);
	// Activer horloge du DAC
	RCC->APB1ENR |= RCC_APB1ENR_DACEN;
	// Reset de la configuration du DAC
	DAC->CR = 0x00000000;
	// Activer le canal 1 du DAC
	DAC->CR |= DAC_CR_EN1;
}

//------------------------------------------------------
//----------------TP3-----------------------------------
//----------------I2C-----------------------------------
/*
* BSP_I2C1_Init()
* Initialise le peripherique I2C1
* * SCL -> PB8 * SDA -> PB9
* */
void BSP_I2C1_Init()
{
	// configuration des pins pour I2C1 // SCL -> PB8 // SDA -> PB9
	// Activer horloge de GPIOB
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	// Configurrer les Pins PB8 et PB9 en mode AF
	GPIOB->MODER &= ~(GPIO_MODER_MODER8 | GPIO_MODER_MODER9);
	GPIOB->MODER |= (0x02 <<16U) | (0x02 <<18U);
	// Choix de AF1 (I2C1) pour les pins PB8 et PB9
	GPIOB->AFR[1] &= ~(0x000000FF);
	GPIOB->AFR[1] |= 0x00000011;
	// Choix de la techno Open-Drain pour les pins PB8 et PB9
	GPIOB->OTYPER |= GPIO_OTYPER_OT_8 | GPIO_OTYPER_OT_9;
	// Selectionner SYSCLK comme horloge I2C1 (48MHz)
	RCC->CFGR3 |= RCC_CFGR3_I2C1SW;
	// Activer horloge du peripherique I2C1
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
	// Assurons-nous que I2C1 est desactiver avec de le configurer
	I2C1->CR1 &= ~I2C_CR1_PE;
	// Reinitialisation de la configuration I2C1 aux valeurs par défaut
	I2C1->CR1 = 0x00000000;
	I2C1->CR2 = 0x00000000;
	I2C1->TIMINGR = 0x00000000;
	// Configurer le timing pour 100kHz, 50% rapport clycique utilisation
	I2C1->TIMINGR |= ((4 -1) <<I2C_TIMINGR_PRESC_Pos);
	// Clock prescaler /4 -> 12MHz
	I2C1->TIMINGR |= (60 <<I2C_TIMINGR_SCLH_Pos);
	// High half-period = 5μs
	I2C1->TIMINGR |= (60 <<I2C_TIMINGR_SCLL_Pos);
	// Low half-period = 5μs
	// Activer I2C1
	I2C1->CR1 |= I2C_CR1_PE;
}
void BSP_DBG_Pins_Init(){
	//PA0
	RCC->AHBENR |= (1<<17);

	GPIOA->MODER &= ~(1<<1);
	GPIOA->MODER |= (1<<0);

	GPIOA->OTYPER &= ~(1<<0);
	//PA1
	GPIOA->MODER &= ~(1<<3);
	GPIOA->MODER |= (1<<2);
	GPIOA->OTYPER &= ~(1<<1);
}

uint8_t BSP_I2C1_Read( uint8_t device_address, uint8_t register_address, uint8_t *buffer, uint8_t nbytes )
{
	uint32_t timeout; // Delai d'attente du drapeau
	uint8_t n;
	// vaiable Compteur
	// Definir adresse du composant slave
	I2C1->CR2 &= ~I2C_CR2_SADD_Msk;
	I2C1->CR2 |= ((device_address <<1U) <<I2C_CR2_SADD_Pos);
	// Metter le peripherique I2C en mode Write
	I2C1->CR2 &= ~I2C_CR2_RD_WRN;
	// Transfert avec NBYTES=1, pas de AUTOEND
	I2C1->CR2 &= ~I2C_CR2_NBYTES;
	I2C1->CR2 |= (1 <<16U);
	I2C1->CR2 &= ~I2C_CR2_AUTOEND;
	// Demarrer la transaction I2C
	I2C1->CR2 |= I2C_CR2_START;
	// Attendre que TXIS passe a '1' avec un timeout
	timeout = 100000;
	while (((I2C1->ISR) & I2C_ISR_TXIS) != I2C_ISR_TXIS) {
		timeout--;
		if (timeout == 0) return 1;
	}
	// Envoyer Adresse du composant (SLAVE)
	I2C1->TXDR = register_address;
	// Attendre que TC passe a '1' avec un timeout
	timeout = 100000;
	while (((I2C1->ISR) & I2C_ISR_TC) != I2C_ISR_TC) {
		timeout--;
		if (timeout == 0) return 2;
	}
	// Metter le peripherique I2C en mode Write
	I2C1->CR2 |= I2C_CR2_RD_WRN;
	// Transfert avec NBYTES=1, pas de AUTOEND
	I2C1->CR2 &= ~I2C_CR2_NBYTES;
	I2C1->CR2 |= (nbytes <<16U);
	I2C1->CR2 &= ~I2C_CR2_AUTOEND;
	// Re-Demarrer la transaction I2C
	I2C1->CR2 |= I2C_CR2_START;
	// Lecure des data
	n = nbytes;
	// nombre octet
	while (n>0) {
		// Attendre que RXNE passe a '1' avec un timeout
		timeout = 100000;
		while (((I2C1->ISR) & I2C_ISR_RXNE) != I2C_ISR_RXNE) {
			timeout--;
			if (timeout == 0) return 3;
		}
	}
	// Enregister les data dans un buffer
	*buffer = I2C1->RXDR; buffer++; n--;
	// Generere une condition STOP
	I2C1->CR2 |= I2C_CR2_STOP;
	// Attendre que STOPF passe a '1' avec un timeout
	timeout = 100000;
	while (((I2C1->ISR) & I2C_ISR_STOPF) != I2C_ISR_STOPF) {
		timeout--; if (timeout == 0) return 4;
	}
	// Renvoi 0 si tout est ok
	return 0;
}


