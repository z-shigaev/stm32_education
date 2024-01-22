/* button control function*/
#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include "stm32f303xc.h"

uint8_t button_read(void);
void button_init();
void EXTI0_IRQHandler(void);

#endif /*BUTTON_H*/
