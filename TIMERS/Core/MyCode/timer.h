/* timer control functions*/
#pragma once
#ifndef TIMER_H
#define TIMER_H

#include "stm32f303xc.h"

#define TIM_IRQ_ENABLE 0x1
#define TIM_IRQ_DISABLE 0x0

void timer_init(TIM_TypeDef* tim, uint8_t irq_state);
void timer_set_up_period(TIM_TypeDef* tim, uint32_t period);
void timer_set_state(TIM_TypeDef* tim, uint8_t state);
uint8_t timer_get_state(TIM_TypeDef* tim);
void TIM6_DAC_IRQHandler(void);
void TIM7_IRQHandler(void);

#endif /*TIMER_H*/
