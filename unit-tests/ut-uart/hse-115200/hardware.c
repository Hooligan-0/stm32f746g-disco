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

static void hw_init_clock(void);
static void hw_init_gpio(void);
static void hw_init_uart(void);

void hw_init(void)
{
	hw_init_clock();
	hw_init_gpio();
	hw_init_uart();
}

static void hw_init_clock(void)
{
	u32 val;

	/* Clear HSEON bit */
	reg_clr(RCC_CR, 0x00010000);
	/* Clear HSEBYP bit */
	reg_clr(RCC_CR, 0x00040000);
	/* Activate HSE (set HSEON) */
	reg_set(RCC_CR, 0x00010000);
	/* Wait until HSERDY bit set */
	while( (reg_rd(RCC_CR) & 0x00020000) == 0)
		;
	
	/* Select HSE as new clock source */
	val  = reg_rd(RCC_CFGR);
	val &= ~0x03;
	val |=  0x01;
	reg_wr(RCC_CFGR, val);
	/* Wait until, clock source is modified */
	while( (reg_rd(RCC_CFGR) & 0x0C) != (0x01 << 2))
		;
}

static void hw_init_gpio(void)
{
        u32 val;
        
	/* Activate GPIO-A controller */
	val = reg_rd((u32)RCC_AHB1ENR);
	val |= 0x01;
	reg_wr((u32)RCC_AHB1ENR, val);
	
	/* Configure uart gpios as Alternate Function */
	val  = reg_rd((u32)GPIOA_MODER);
	val |= 0x00080000; /* PA9:  TX */
	val |= 0x00200000; /* PA10: RX */
	reg_wr((u32)GPIOA_MODER, val);
	/* Select Alternate functions  */
	val  = reg_rd((u32)GPIOA_AFRH);
	val |= 0x70;  /* PA9  use AF7  */
	val |= 0x700; /* PA10 use AF7  */
	reg_wr((u32)GPIOA_AFRH, val);
}

static void hw_init_uart(void)
{
        u32 val;
        
	/* Activate USART1 */
	val = reg_rd((u32)RCC_APB2ENR);
	val |= 0x10;
	reg_wr((u32)RCC_APB2ENR, val);
	
	/* Configure UART */
	reg_wr(UART1_BRR, 0x00D9); /* 115200 @ 25MHz       */
	reg_wr(UART1_CR1,   0x0C); /* Set TE & RE bits     */
	reg_wr(UART1_CR1,   0x0D); /* Set USART Enable bit */
}

u32 reg_rd(u32 reg)
{
        return ( *(volatile u32 *)reg );
}

void reg_wr(u32 reg, u32 value)
{
        *(volatile u32 *)reg = value;
}

void reg_set(u32 reg, u32 value)
{
	*(volatile u32 *)reg = ( *(volatile u32 *)reg | value );
}

void reg_clr(u32 reg, u32 value)
{
	*(volatile u32 *)reg = ( *(volatile u32 *)reg & ~value );
}

/* EOF */
