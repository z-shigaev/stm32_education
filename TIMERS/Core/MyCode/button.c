#include "button.h"
#include "stm32f303xc.h"
#include "gpio_ctrl.h"
#include "timer.h"

#define GPIO_ODR_A0 (1<<0)

uint8_t button_read(void){
	uint32_t tmp_var = 0;
	tmp_var = GPIOA -> IDR;
	uint8_t res = (tmp_var >> 0) & 0x01;
	return res;
}

void button_init(){
	/*Инициализация GPIO для кнопки*/
	GPIOA->MODER|=(0x0<<0);		//установка режима
	GPIOA->OTYPER|=(0x0<<0);	//установка типа выхода
	GPIOA->OSPEEDR|=(0x0<<0);	//установка скорости
	GPIOA->PUPDR|=(0x0<<0);		//отключаем подтяжки порта

	NVIC_EnableIRQ(EXTI0_IRQn);	//разрешение прерывания
	EXTI->IMR |= (1<<0);		//включение прерывания
	EXTI->RTSR |= (1<<0);		//прерывание по переднему фронту включено
	EXTI->FTSR |= (1<<0);
//	EXTI->FTSR &= ~(1<<0);		//прерывание по заднему фронту отключено
//	gpio_set(GPIOE, 9, 0x1);
}

void EXTI0_IRQHandler(void){
	static volatile uint8_t flag = 0;
	static volatile uint8_t flag_timer = 0;

	if (flag){
		// действия по заднему фронту
		gpio_toggle(GPIOE, 9);
		GPIOA->ODR |= GPIO_ODR_A0;	//led on
		flag = 0;
		// timer
		flag_timer = timer_get_state(TIM7);
		if (flag_timer){
			timer_set_up_period(TIM6, 1000);

		}
		else{
			timer_set_up_period(TIM6, 5000);
		}
		gpio_set(GPIOE, 13, 0x1);
		timer_set_state(TIM6, 0x1);
	}
	else{
		// действия по переднему фронту
		gpio_toggle(GPIOE, 9);
		gpio_toggle(GPIOE, 10);
		GPIOA->ODR &= ~GPIO_ODR_A0;	//led off
		flag = 1;
		// timer
		timer_set_up_period(TIM7, 1000);
		timer_set_state(TIM7, 0x1);
	}


	EXTI->PR |= (1<<0);
}


