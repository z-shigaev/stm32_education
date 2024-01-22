# include "gpio_ctrl.h"


void gpio_init(GPIO_TypeDef* port, uint32_t line){
	/*comment*/
	port -> MODER |= (0x1 << (2 * line));
	port -> OTYPER |= (0x0 << line);
	port -> OSPEEDR |= (0x3 << (2*line));
	port -> PUPDR |= (0x0 << (2*line));
}

void gpio_set(GPIO_TypeDef* port, uint32_t line, uint8_t state){
	uint8_t x = state^0x1;
	port -> BSRR = (0x01 << (line + 16*x));
//	uint32_t tmp_var = 0;
//	tmp_var = port -> IDR;
//	port->ODR = tmp_var | (state<<line);
}

uint8_t gpio_get(GPIO_TypeDef* port, uint32_t line){
	uint32_t tmp_var = 0;
	tmp_var = port -> IDR;
	uint8_t res = (tmp_var >> line) & 0x01;
	return res;
}

void gpio_toggle(GPIO_TypeDef* port, uint32_t line){
	uint32_t tmp_var = 0;
	tmp_var = port -> IDR;
	port -> ODR = tmp_var ^ (0x1 << line);
}

void delay(uint32_t value){
	int i;
	for(i=0;i<value;i++){
	}
}
