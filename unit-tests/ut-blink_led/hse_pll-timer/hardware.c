/**
 * STM32F7 LED blink (PLL clock) Unit Test
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

	/* 1) Activate HSE, that will be used as PLL source */

	/* Clear HSEON bit */
	reg_clr(RCC_CR, 0x00010000);
	/* Clear HSEBYP bit */
	reg_clr(RCC_CR, 0x00040000);
	/* Activate HSE (set HSEON) */
	reg_set(RCC_CR, 0x00010000);
	/* Wait until HSERDY bit set */
	while( (reg_rd(RCC_CR) & 0x00020000) == 0)
		;
	
	/* 2) Configure and activate PLL */
	
	/* Configure PLL */
	val  = (432 <<  6); // set N (VCO multiplier)
	val |=   25;        // set M (VCO divisor)
	val |= (  0 << 16); // set P (output divisor
	val |= (  9 << 24); // set Q (peripheral divisor)
	reg_wr(RCC_PLLCFGR, val);
		
	/* Activate PLL */
	reg_set(RCC_CR, 0x01000000);
	while( (reg_rd(RCC_CR) & 0x02000000) == 0)
		;
		                
	/* 3) Update flash latency, and periphera bus prescaler */
	
	/* Set Flash latency to 7 */
	reg_set(FLASH_ACR, 0x07);
	
	/* PCLK1 - Set APB1 clock divider to 4 (value 5) */
	reg_set(RCC_CFGR, (5 << 10) );
	/* PCLK2 - Set APB2 clock divider to 2 (value 4) */
	reg_set(RCC_CFGR, (4 << 13) );
	
	/* 4) Switch the current clock to PLL */

	/* Change the clock source */
	val  = reg_rd(RCC_CFGR);
	val &= ~0x03;
	val |=  0x02;
	reg_wr(RCC_CFGR, val);
	/* Wait until, clock source is modified */
	while( (reg_rd(RCC_CFGR) & 0x0C) != (0x02 << 2))
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
	while( (reg_rd(RCC_APB1ENR) & 1) == 0)
	        ;
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