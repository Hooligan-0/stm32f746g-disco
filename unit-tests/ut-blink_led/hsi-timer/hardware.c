/**
 * STM32F7 LED blink (HSI clock) Unit Test
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
static void hw_init_gpio (void);
static void hw_init_timer(void);

void hw_init(void)
{
	hw_init_clock();
	hw_init_gpio();
	hw_init_timer();
}

static void hw_init_clock(void)
{
	u32 val;

	/* Select HSI as new clock source */
	val  = reg_rd(RCC_CFGR);
	val &= ~0x03; /* 0x00 : HSI */
	reg_wr(RCC_CFGR, val);
	/* Wait until, clock source is modified */
	while( (reg_rd(RCC_CFGR) & 0x0C) != (0x00 << 2))
		;
}

static void hw_init_gpio(void)
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
}

static void hw_init_timer(void)
{
	reg_set(RCC_APB1ENR, 0x01); /* Activate Timer2 */
	/* Configure Timer2 */
	reg_wr (TIM2_CR1, 0x0200); /* Input clock divided by 4 */
	reg_wr (TIM2_ARR, 0x8000); /* Value used when reloaded */
	reg_wr (TIM2_PSC,   0x80); /* Prescaler       */
	reg_set(TIM2_CR1,   0x08); /* Set OPM (one-pulse-mode) */
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