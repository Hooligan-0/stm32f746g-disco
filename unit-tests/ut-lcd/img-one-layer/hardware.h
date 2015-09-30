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
#ifndef HARDWARE_H
#define HARDWARE_H

#define TIM2  0x40000000
/* APB 2 */
#define LTDC  0x40016800
/* AHB 1 */
#define GPIOA 0x40020000
#define GPIOC 0x40020800
#define GPIOE 0x40021000
#define GPIOG 0x40021800
#define GPIOI 0x40022000
#define GPIOJ 0x40022400
#define GPIOK 0x40022800
#define RCC   0x40023800
#define FLASH 0x40023C00

#define TIM2_CR1    (TIM2 + 0x00)
#define TIM2_CCMR1  (TIM2 + 0x18)
#define TIM2_CCER   (TIM2 + 0x20)
#define TIM2_PSC    (TIM2 + 0x28)
#define TIM2_ARR    (TIM2 + 0x2C)
#define TIM2_CCR1   (TIM2 + 0x34)

#define LTDC_SSCR   (LTDC + 0x08)
#define LTDC_BPCR   (LTDC + 0x0C)
#define LTDC_AWCR   (LTDC + 0x10)
#define LTDC_TWCR   (LTDC + 0x14)
#define LTDC_GCR    (LTDC + 0x18)
#define LTDC_SRCR   (LTDC + 0x24)
#define LTDC_BCCR   (LTDC + 0x2C)
#define LTDC_L1_CR     (LTDC + 0x84)
#define LTDC_L1_WHPCR  (LTDC + 0x88)
#define LTDC_L1_WVPCR  (LTDC + 0x8C)
#define LTDC_L1_PFCR   (LTDC + 0x94)
#define LTDC_L1_CFBAR  (LTDC + 0xAC)
#define LTDC_L1_CFBLR  (LTDC + 0xB0)
#define LTDC_L1_CFBLNR (LTDC + 0xB4)

#define RCC_CR      (RCC + 0x000)
#define RCC_PLLCFGR (RCC + 0x004)
#define RCC_CFGR    (RCC + 0x008)
#define RCC_AHB1ENR (RCC + 0x030)
#define RCC_APB1ENR (RCC + 0x040)
#define RCC_APB2ENR (RCC + 0x044)
#define RCC_PLLSAI  (RCC + 0x088)
#define RCC_DKCFGR1 (RCC + 0x08C)

#define GPIOA_MODER (GPIOA + 0x000)
#define GPIOA_AFRL  (GPIOA + 0x020)
#define GPIOC_MODER (GPIOC + 0x000)

#define GPIOE_MODER (GPIOE + 0x000)
#define GPIOE_AFRL  (GPIOE + 0x020)

#define GPIOG_MODER (GPIOG + 0x000)
#define GPIOG_AFRL  (GPIOG + 0x020)
#define GPIOG_AFRH  (GPIOG + 0x024)

#define GPIOI_MODER (GPIOI + 0x000)
#define GPIOI_ODR   (GPIOI + 0x014)
#define GPIOI_BSRR  (GPIOI + 0x018)
#define GPIOI_AFRH  (GPIOI + 0x024)

#define GPIOJ_MODER (GPIOJ + 0x000)
#define GPIOJ_AFRL  (GPIOJ + 0x020)
#define GPIOJ_AFRH  (GPIOJ + 0x024)

#define GPIOK_MODER (GPIOK + 0x000)
#define GPIOK_BSRR  (GPIOK + 0x018)
#define GPIOK_AFRL  (GPIOK + 0x020)

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
