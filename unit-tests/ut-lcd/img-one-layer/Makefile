##
# STM32F7 Display Unit Test
# 
# Copyright (c) 2015 Saint-Genest Gwenael <gwen@agilack.fr>
# 
# This file may be distributed and/or modified under the terms of the
# GNU General Public License version 2 as published by the Free Software
# Foundation. (See COPYING.GPL for details.)
# 
# This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
# WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
# 
# 
CROSS = arm-none-eabi-
TARGET = ut_lcd_img
CC = $(CROSS)gcc
OBJCOPY = $(CROSS)objcopy
RM = rm
AFLAGS = -g -mcpu=cortex-m7 -mthumb
CFLAGS = -g -mcpu=cortex-m7 -mthumb -I.
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -Wall -Wimplicit -Wcast-align -Wpointer-arith -Wswitch
CFLAGS += -Wredundant-decls -Wreturn-type -Wshadow -Wunused
LDFLAGS = -Wl,-Map=$(TARGET).map,--cref,--gc-sections
LDFLAGS += -lc -lgcc -Tstm32f746ng_flash.ld

all:
	$(CC) $(AFLAGS) -c stm32f746xx.s -o stm32f746xx.o
	$(CC) $(CFLAGS) -c main.c        -o main.o
	$(CC) $(CFLAGS) -c hardware.c    -o hardware.o
	$(CC) $(CFLAGS) -c display.c     -o display.o
	$(CC) $(LDFLAGS) -o $(TARGET) stm32f746xx.o main.o hardware.o display.o
	$(OBJCOPY) -O binary $(TARGET) $(TARGET).bin
clean:
	$(RM) -f $(TARGET) $(TARGET).* *.o *~
