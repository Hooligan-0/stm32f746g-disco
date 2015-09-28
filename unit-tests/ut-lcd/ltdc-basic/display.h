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
#ifndef DISPLAY_H
#define DISPLAY_H

#define  DISP_WIDTH  ((u16)480)
#define  DISP_HEIGHT ((u16)272)
#define  DISP_HSYNC  ((u16) 41)   /* Horizontal Sync        */
#define  DISP_HBP    ((u16) 13)   /* Horizontal back porch  */
#define  DISP_HFP    ((u16) 32)   /* Horizontal front porch */
#define  DISP_VSYNC  ((u16) 10)   /* Vertical Sync          */
#define  DISP_VBP    ((u16)  2)   /* Vertical back porch    */
#define  DISP_VFP    ((u16)  2)   /* Vertical front porch   */
/* Define the Back Porch length according to display values */
#define DISP_AHBP   (DISP_HSYNC + DISP_HBP - 1)
#define DISP_AVBP   (DISP_VSYNC + DISP_VBP - 1)
/* Define the Active Width according to display values */
#define DISP_AAW    (DISP_AHBP + DISP_WIDTH)
#define DISP_AAH    (DISP_AVBP + DISP_HEIGHT)
/* Define the Total Width according to display values */
#define DISP_TOTALW (DISP_AAW + DISP_HFP)
#define DISP_TOTALH (DISP_AAH + DISP_VFP)

void display_init(void);

#endif
