/*
 * main.h
 * Created on: Feb 3, 2021
 * Author: darga */
#include "stm32f0xx.h"
#ifndef APP_INC_MAIN_H_
#define APP_INC_MAIN_H_
/*
 * printf() et sprintf() de la lib. printf-stdarg.c */

int j_printf (const char *format, ...);
int j_sprintf (char *out, const char *format, ...);
#endif
/* APP_INC_MAIN_H_ */
