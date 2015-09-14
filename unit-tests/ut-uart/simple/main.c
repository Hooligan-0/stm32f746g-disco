/**
 * STM32F7 Uart Unit Test
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
#define RCC   0x40023800
#define RCC_AHB1ENR (RCC + 0x030)
#define RCC_APB2ENR (RCC + 0x044)
#define GPIOA 0x40020000
#define GPIOI 0x40022000
#define GPIOI_MODER (GPIOI + 0x000)
#define GPIOI_ODR   (GPIOI + 0x014)
#define GPIOI_BSRR  (GPIOI + 0x018)
//
#define GPIOA_MODER (GPIOA + 0x000)
#define GPIOA_ODR   (GPIOA + 0x014)
#define GPIOA_BSRR  (GPIOA + 0x018)
#define GPIOA_AFRH  (GPIOA + 0x024)

#define UART1 0x40011000
#define UART1_CR1 (UART1 + 0x00)
#define UART1_BRR (UART1 + 0x0C)
#define UART1_ISR (UART1 + 0x1C)
#define UART1_TDR (UART1 + 0x28)

typedef unsigned char  u8;
typedef unsigned long  u32;

void uart_putc(u8 c);
void uart_puts (char *s);
void hw_init(void);
u32  reg_rd(u32 reg);
void reg_wr(u32 reg, u32 value);

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

void hw_init(void)
{
	u32 val;

	/* Activate GPIO-I controller */
	val = reg_rd((u32)RCC_AHB1ENR);
	val |= 0x0100;
	reg_wr((u32)RCC_AHB1ENR, val);

	/* Configure GPIOI-1 as output */
	val  = reg_rd((u32)GPIOI_MODER);
	val |= (0x01 << 2);
	reg_wr((u32)GPIOI_MODER, val);


	/* Activate GPIO-A controller */
	val = reg_rd((u32)RCC_AHB1ENR);
	val |= 0x01;
	reg_wr((u32)RCC_AHB1ENR, val);
	
	/* Configure uart gpios as Alternate Function */
	val  = reg_rd((u32)GPIOA_MODER);
	val |= 0x00080000; /* PA9:  TX */
	val |= 0x00200000; /* PA10: RX */
	reg_wr((u32)GPIOA_MODER, val);
	/* Select Alternate functions */
	val  = reg_rd((u32)GPIOA_AFRH);
	val |= 0x70;  /* PA9  use AF7 */
	val |= 0x700; /* PA10 use AF7 */
	reg_wr((u32)GPIOA_AFRH, val);

	/* Activate USART1 */
	val = reg_rd((u32)RCC_APB2ENR);
	val |= 0x10;
	reg_wr((u32)RCC_APB2ENR, val);

	reg_wr(UART1_BRR, 0x008B); /* 115200 @ 16MHz       */
	reg_wr(UART1_CR1,  0x0C);  /* Set TE & RE bits     */
	reg_wr(UART1_CR1,  0x0D);  /* Set USART Enable bit */
}

u32 reg_rd(u32 reg)
{
        return ( *(volatile u32 *)reg );
}
void reg_wr(u32 reg, u32 value)
{
        *(volatile u32 *)reg = value;
}
