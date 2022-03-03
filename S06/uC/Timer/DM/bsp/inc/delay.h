/*
 * delay.h
 *
 * Created on: 15 févr. 2021 * Author: darga */
#ifndef BSP_INC_DELAY_H_
#define BSP_INC_DELAY_H_
#include "stm32f0xx.h"
/*
 * Delais attentes ou temporisation Software */
void BSP_DELAY_ms (uint32_t delay);
void BSP_DELAY_us (uint32_t delay);
#endif /* BSP_INC_DELAY_H_ */

