/**
 * STM32F7 LED blink (HSE clock) Unit Test
 *
 * Copyright (c) 2015 Saint-Genest Gwenael <gwen@agilack.fr>
 *
 * This file may be distributed and/or modified under the terms of the
 * GNU General Public License version 2 as published by the Free Software
 * Foundation. (See COPYING.GPL for details.)
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
#include "hardware.h"

void led_on(void);
void led_off(void);

int main(void)
{
	hw_init();

	while(1)
	{
		led_on();
		
		/* Start Timer2 */
		reg_set(TIM2_CR1, 1);
		/* Wait Timer2 ends */
		while(reg_rd(TIM2_CR1) & 1)
			;

		led_off();
		
		/* Start Timer2 */
		reg_set(TIM2_CR1, 1);
		/* Wait Timer2 ends */
		while(reg_rd(TIM2_CR1) & 1)
			;
	}
}

void led_on(void)
{
	/* Set PI-1 */
	reg_wr((u32)GPIOI_BSRR, (0x1 << 1) );
}

void led_off(void)
{
	/* Clear PI-1 */
	reg_wr((u32)GPIOI_BSRR, (0x1 << 17) );
}
