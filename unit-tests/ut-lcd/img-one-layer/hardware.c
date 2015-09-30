/**
 * STM32F7 Display Unit Test
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
static void hw_init_ltdc (void);
static void hw_init_timer(void);

void hw_init(void)
{
	hw_init_clock();
	hw_init_gpio();
	hw_init_ltdc();
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
		                
	/* 3) Update flash latency, and peripheral bus prescaler */
	
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

static void hw_init_ltdc (void)
{
    u32 val;
    
	/* Activate GPIO controller */
	val = reg_rd((u32)RCC_AHB1ENR);
	val |= 0x0010; /* GPIO-E */
	val |= 0x0040; /* GPIO-G */
	val |= 0x0100; /* GPIO-I */
	val |= 0x0200; /* GPIO-J */
	val |= 0x0400; /* GPIO-K */
	reg_wr((u32)RCC_AHB1ENR, val);

	/* Configure GPIO-E pins mode */
	val  = reg_rd((u32)GPIOE_MODER);
	val &= 0xFFFFFCFF; /* PE-4 : LCD_B0 */
	val |= 0x00000200; /* PE-4 : use alternate function */
	reg_wr((u32)GPIOE_MODER, val);
	/* Configure GPIO-E alternate functions */
	val  = reg_rd((u32)GPIOE_AFRL);
	val |= (0x0E << 16); /* PE-4 = AF14 : LTDC */
    reg_wr((u32)GPIOE_AFRL, val);
    
	/* Configure GPIO-G pins mode */
	val  = reg_rd((u32)GPIOG_MODER);
	val |= (0x02 << 24); /* PG-12  : LCD_B4 */
    reg_wr((u32)GPIOG_MODER, val);
	/* Configure GPIO-G alternate functions */
	val  = reg_rd((u32)GPIOG_AFRH);
	val |= (0x0E <<  16); /* PG-12 = AF14 : LTDC */
    reg_wr((u32)GPIOG_AFRH, val);

	/* Configure GPIO-I pins mode */
	val  = reg_rd((u32)GPIOI_MODER);
	val |= (0x02 << 18); /* PI-9  : LCD_VSYNC */
	val |= (0x02 << 20); /* PI-10 : LCD_HSYNC */
	val |= (0x02 << 28); /* PI-14 : LCD_CLK   */
	val |= (0x02 << 30); /* PI-15 : LCD_R0    */
	val |= (0x01 << 24); /* PI-12 : LCD_DISP  - manual output */
	reg_wr((u32)GPIOI_MODER, val);
	/* Configure GPIO-I alternate functions */
	val  = reg_rd((u32)GPIOI_AFRH);
	val |= (0x0E <<  4); /* PI-9  = AF14 : LTDC */
	val |= (0x0E <<  8); /* PI-10 = AF14 : LTDC */
	val |= (0x0E << 24); /* PI-14 = AF14 : LTDC */
	val |= (0x0E << 28); /* PI-15 = AF14 : LTDC */
	reg_wr((u32)GPIOI_AFRH, val);

	/* Configure GPIO-J pins mode */
	val  = reg_rd((u32)GPIOJ_MODER);
	val &= 0x03000000; /* Reset all except PJ12 (used by USB)    */
	val |= 0xA8AAAAAA; /* Use alternate function for all lcd ios */
	reg_wr((u32)GPIOJ_MODER, val);
	/* Configure GPIO-J alternate functions */
	val  = 0xEEEEEEEE;
	reg_wr((u32)GPIOJ_AFRL, val);
	val  = reg_rd((u32)GPIOJ_AFRH);
	val &= 0x000F0000;
	val |= 0xEEE0EEEE;
	reg_wr((u32)GPIOJ_AFRH, val);

	/* Configure GPIOK pins as alternate-function */
	val  = reg_rd((u32)GPIOK_MODER);
	val |= (0x02 <<  0); /* PK-0  : LCD_G5   */
	val |= (0x02 <<  2); /* PK-1  : LCD_G6   */
	val |= (0x02 <<  4); /* PK-2  : LCD_G7   */
	val |= (0x01 <<  6); /* PK-3  : LCD_BackLight - manual output */
	val |= (0x02 <<  8); /* PK-4  : LCD_B5   */
	val |= (0x02 << 10); /* PK-5  : LCD_B6   */
	val |= (0x02 << 12); /* PK-6  : LCD_B7   */
	val |= (0x02 << 14); /* PK-7  : LCD_DE   */
	reg_wr((u32)GPIOK_MODER, val);
	/* Configure GPIO-I alternate functions */
	val  = reg_rd((u32)GPIOK_AFRL);
	val |= (0x0E <<  0); /* PK-0 = AF14 : LTDC */
	val |= (0x0E <<  4); /* PK-1 = AF14 : LTDC */
	val |= (0x0E <<  8); /* PK-2 = AF14 : LTDC */
	val |= (0x0E << 16); /* PK-4 = AF14 : LTDC */
	val |= (0x0E << 20); /* PK-5 = AF14 : LTDC */
	val |= (0x0E << 24); /* PK-6 = AF14 : LTDC */
	val |= (0x0E << 28); /* PK-7 = AF14 : LTDC */
	reg_wr((u32)GPIOK_AFRL, val);

    /* 2) Configure Clocks */
	
    val = reg_rd(RCC_PLLSAI);
    /* Set VCO division factor (SAI "N") */
    val &= ~(0x1FF << 6);
    val |=  (192   << 6);
    /* Set LCD division factor (SAI "R") */
    val &= ~(0x07 << 28);
    val |=  ( 5   << 28);
    /* Update RCC PLLSAI */
    reg_wr(RCC_PLLSAI, val);
    
	/* Activate PLL-SAI */
	reg_set(RCC_CR, 0x10000000);
	while( (reg_rd(RCC_CR) & 0x20000000) == 0)
		;

    /* Update LCD dedicated clock prescaller */
    val  = reg_rd(RCC_DKCFGR1);
    val &= ~(0x03 << 16);
    val |=  (0x01 << 16); /* div by 4 */
    reg_wr(RCC_DKCFGR1, val);
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