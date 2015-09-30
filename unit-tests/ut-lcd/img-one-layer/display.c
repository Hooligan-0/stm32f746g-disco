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
#include "display.h"
#include "disp_image.h"

static void ltdc_init(void);
static void layer_config(u32 fb_addr);

void display_init(void)
{
    ltdc_init();
    layer_config((u32)&gimp_image.pixel_data);
}

static void layer_config(u32 fb_addr)
{
    u32 val, tmp;
    
    /* Configure Horizontal start/stop position */
    tmp = ( (reg_rd(LTDC_BPCR) & 0x0FFF0000) >> 16);
    val  = ((DISP_WIDTH + tmp) << 16);
    val |=  (         1 + tmp);
    reg_wr(LTDC_L1_WHPCR, val);
    
    /* Configure Vertical start/stop position */
    tmp = (reg_rd(LTDC_BPCR) & 0x07FF);
    val  = ((DISP_HEIGHT + tmp) << 16); /* Set Stop position to the last line */
    val |=  (          1 + tmp);      /* Set start position to the first line */
    reg_wr(LTDC_L1_WVPCR, val);
    
    /* Set the pixel format */
    val = 0x02; /* RGB 565 */
    reg_wr(LTDC_L1_PFCR, val);
    
    /* ToDo : set default color value */
    
    /* ToDo : set constant alpha value */
    
    /* ToDo : set blending factors */
    
    /* Configure the frame buffer address */
    reg_wr(LTDC_L1_CFBAR, fb_addr);
    
    /* Color Frame Buffer Length */
    val  = ((DISP_WIDTH * 2) << 16);
    val |=  (DISP_WIDTH * 2) + 3;
    reg_wr(LTDC_L1_CFBLR, val);
    
    /* Define the number of lines into the color Frame Buffer */
    reg_wr(LTDC_L1_CFBLNR, DISP_HEIGHT);
    
    reg_set(LTDC_L1_CR, 1);
    
    /* Refresh shadow register after layer config */
    reg_set(LTDC_SRCR,  1);
}

static void ltdc_init(void)
{
	u32 val;
    
	/* Activate external LCD  */
	reg_wr((u32)GPIOI_BSRR, (0x1 << 12) );
	/* Set LCD backlight      */
	reg_wr((u32)GPIOK_BSRR, (0x1 << 3) );
	
	/* Activate LTDC controller */
	val = reg_rd((u32)RCC_APB2ENR);
	val |= (1 << 26);
	reg_wr((u32)RCC_APB2ENR, val);
	
	/* Configure polarity */
	val = reg_rd(LTDC_GCR) & 0x0FFFFFFF;
	val |= (0 << 31); /* HS polarity              */
	val |= (0 << 30); /* VS polarity              */
	val |= (0 << 29); /* Not Data Enable polarity */
	val |= (0 << 28); /* Pixel Clock polarity     */
	reg_wr(LTDC_GCR, val);

	/* Configure Synchronization Size */
	val  = ((DISP_HSYNC - 1) << 16); /* Horizontal Sync */
	val |=  (DISP_VSYNC - 1);        /* Vertical Sync   */
	reg_wr(LTDC_SSCR, val);
	
	/* Configure Back Porch */
	val  = (DISP_AHBP << 16);   /* Horizontal Back Porch */
	val |=  DISP_AVBP;          /* Vertical Back Porch   */
	reg_wr(LTDC_BPCR, val);

	/* Configure Active Width */
	val  = (DISP_AAW << 16);    /* Active Width  */
	val |=  DISP_AAH;           /* Active Height */
	reg_wr(LTDC_AWCR, val);

	/* Configure Total Width */
	val  = (DISP_TOTALW << 16); /* Total Width  */
	val |=  DISP_TOTALH;        /* Total Height */
	reg_wr(LTDC_TWCR, val);

	/* Configure Background Color */
	val  = (0x80 << 16); /* Set Red value   */
	val |= (0x80 <<  8); /* Set Green value */
	val |= (0x00 <<  0); /* Set Blue value  */
	reg_wr(LTDC_BCCR, val);
	
	/* Enable LTDC */
	reg_set(LTDC_GCR, 0x01); /* Set EN bit */

	reg_set(LTDC_SRCR,  1); /* Refresh shadow register by writing 1 to IMR */
}

/* EOF */
