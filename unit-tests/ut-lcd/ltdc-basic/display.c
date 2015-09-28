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

void display_init(void)
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

#ifdef use_layers
	reg_set(LTDC_L1_CR, 1);
#endif

	reg_set(LTDC_SRCR,  1); /* Refresh shadow register by writing 1 to IMR */
}

/* EOF */
