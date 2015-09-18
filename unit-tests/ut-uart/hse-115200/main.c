/**
 * STM32F7 Uart Unit Test (use HSE)
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

void uart_putc(u8 c);
void uart_puts (char *s);

int main(void)
{
	int i;

	hw_init();

	while(1)
	{
		uart_puts("Hello World !\r\n");
		for (i = 0; i < 0x00800000; i++)
			;
	}
}

void uart_putc(u8 c)
{
	while ( (reg_rd(UART1_ISR) & 0x80) != 0x80)
		;
	reg_wr(UART1_TDR, c);
}

void uart_puts (char *s)
{
	while (*s)
	{
		uart_putc(*s);
		s++;
	}
}
/* EOF */
