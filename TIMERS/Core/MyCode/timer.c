#include "timer.h"
#include "button.h"
#include "stm32f303xc.h"
#include "gpio_ctrl.h"


void timer_init(TIM_TypeDef* tim, uint8_t irq_state){
	/*настройка таймера:
	считает вверх;
	остановка до ARR;
	счетчик отключен;
	разрешение генерации события по переполнению таймера*/
	tim->CR1 |= (0<<11)|(0<<7)|(1<<3)|(0<<1)|(0<<0);
	tim->CR2 |= 0;					// работа в режиме мастера
	tim->EGR |= 0;					// не используется
	tim->DIER |= (irq_state<<0);	// настройка прерываний
	// предварительный запуск таймера
	tim->PSC = 9999;
	tim->ARR = 1;
	tim->CR1 |= (1<<0);
	while((tim->CR1 & 0x01) != 0x0){};
}

void timer_set_up_period(TIM_TypeDef* tim, uint32_t period){
	/*period в мс*/
	tim->PSC = 9999;				// период счетчика 1 мс
	tim->ARR = period;				// период срабатывания в мс
}

void timer_set_state(TIM_TypeDef* tim, uint8_t state){
	tim->CR1 |= (state<<0);
}

uint8_t timer_get_state(TIM_TypeDef* tim){
	uint32_t tmp_var = 0;
	tmp_var = tim->CR1;
	uint8_t res = (tmp_var >> 0) & 0x1;
	return res;
}

void TIM6_DAC_IRQHandler(void){
	gpio_set(GPIOE, 13, 0x0);
	// очистка прерывания
	TIM6->SR &= ~(0x01);			// обнуление флага вызова прерывания
}

void TIM7_IRQHandler(void){
	gpio_set(GPIOE, 15, 0x0);
	// очистка прерывания
	TIM7->SR &= ~(0x01);			// обнуление флага вызова прерывания
}
