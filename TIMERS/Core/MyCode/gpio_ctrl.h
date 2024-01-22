/* GPIO  control function*/
#pragma once
#ifndef GPIO_CTRL_H
#define GPIO_CTRL_H

#include "stm32f303xc.h"

void gpio_init(GPIO_TypeDef* port, uint32_t line);
void gpio_set(GPIO_TypeDef* port, uint32_t line, uint8_t state);
uint8_t gpio_get(GPIO_TypeDef* port, uint32_t line);
void gpio_toggle(GPIO_TypeDef* port, uint32_t line);
void delay(uint32_t value);

#endif /*GPIO_CTRL_H*/
