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
#ifndef HARDWARE_H
#define HARDWARE_H

#define UART1 0x40011000
#define GPIOA 0x40020000
#define RCC   0x40023800

#define RCC_CR      (RCC + 0x000)
#define RCC_CFGR    (RCC + 0x008)
#define RCC_AHB1ENR (RCC + 0x030)
#define RCC_APB1ENR (RCC + 0x040)
#define RCC_APB2ENR (RCC + 0x044)

#define GPIOA_MODER (GPIOA + 0x000)
#define GPIOA_ODR   (GPIOA + 0x014)
#define GPIOA_BSRR  (GPIOA + 0x018)
#define GPIOA_AFRH  (GPIOA + 0x024)

#define UART1_CR1 (UART1 + 0x00)
#define UART1_BRR (UART1 + 0x0C)
#define UART1_ISR (UART1 + 0x1C)
#define UART1_TDR (UART1 + 0x28)

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
