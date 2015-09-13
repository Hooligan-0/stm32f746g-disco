/**
 * STM32F7 LED blink Unit Test
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
#define GPIOI 0x40022000
#define GPIOI_MODER (GPIOI + 0x000)
#define GPIOI_ODR   (GPIOI + 0x014)
#define GPIOI_BSRR  (GPIOI + 0x018)

typedef unsigned long  u32;

void hw_init(void);
void led_on(void);
void led_off(void);
u32  reg_rd(u32 reg);
void reg_wr(u32 reg, u32 value);

int main(void)
{
	int i;

	hw_init();

	while(1)
	{
		led_on();
		for (i = 0; i < 0x10000; i++)
			;
		led_off();
		for (i = 0; i < 0x10000; i++)
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
}

u32 reg_rd(u32 reg)
{
        return ( *(volatile u32 *)reg );
}
void reg_wr(u32 reg, u32 value)
{
        *(volatile u32 *)reg = value;
}
