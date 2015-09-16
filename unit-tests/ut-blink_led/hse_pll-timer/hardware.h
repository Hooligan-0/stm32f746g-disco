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
#ifndef HARDWARE_H
#define HARDWARE_H

#define TIM2  0x40000000
/* AHB 1 */
#define GPIOA 0x40020000
#define GPIOC 0x40020800
#define GPIOI 0x40022000
#define RCC   0x40023800
#define FLASH 0x40023C00

#define TIM2_CR1    (TIM2 + 0x00)
#define TIM2_CCMR1  (TIM2 + 0x18)
#define TIM2_CCER   (TIM2 + 0x20)
#define TIM2_PSC    (TIM2 + 0x28)
#define TIM2_ARR    (TIM2 + 0x2C)
#define TIM2_CCR1   (TIM2 + 0x34)

#define RCC_CR      (RCC + 0x000)
#define RCC_PLLCFGR (RCC + 0x004)
#define RCC_CFGR    (RCC + 0x008)
#define RCC_AHB1ENR (RCC + 0x030)
#define RCC_APB1ENR (RCC + 0x040)

#define GPIOA_MODER (GPIOA + 0x000)
#define GPIOA_AFRL  (GPIOA + 0x020)
#define GPIOC_MODER (GPIOC + 0x000)

#define GPIOI_MODER (GPIOI + 0x000)
#define GPIOI_ODR   (GPIOI + 0x014)
#define GPIOI_BSRR  (GPIOI + 0x018)

#define FLASH_ACR   (FLASH + 0x00)

typedef unsigned long  u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef volatile unsigned long  vu32;
typedef volatile unsigned short vu16;

void hw_init(void);

/* Low level register functions */
void reg_wr (u32 reg, u32 value);
u32  reg_rd (u32 reg);
void reg_set(u32 reg, u32 value);   
void reg_clr(u32 reg, u32 value);   

#endif
