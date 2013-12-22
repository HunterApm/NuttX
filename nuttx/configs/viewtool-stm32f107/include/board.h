/************************************************************************************
 * configs/viewtool-stm32f107/include/board.h
 *
 *   Copyright (C) 2013 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ************************************************************************************/

#ifndef __CONFIGS_VIEWTOOLS_STM32F107_INCLUDE_BOARD_H
#define __CONFIGS_VIEWTOOLS_STM32F107_INCLUDE_BOARD_H 1

/************************************************************************************
 * Included Files
 ************************************************************************************/

#include <nuttx/config.h>

#ifndef __ASSEMBLY__
# include <stdint.h>
#endif

#include "stm32_rcc.h"
#include "stm32_sdio.h"
#include "stm32.h"

/************************************************************************************
 * Pre-processor Definitions
 ************************************************************************************/

/* Clocking *************************************************************************/

#if defined(CONFIG_ARCH_CHIP_STM32F107VC)
# include <arch/board/board-stm32f107vct6.h>
#elif defined(CONFIG_ARCH_CHIP_STM32F103VCT6)
# include <arch/board/board-stm32f103vct6.h>
#else
#  error Unregnized STM32 chip
#endif

/* LED definitions ******************************************************************/
/* There are four LEDs on the ViewTool STM32F103/F107 board that can be controlled
 * by software:  LED1 through LED4.  All pulled high and can be illuminated by
 * driving the output to low
 *
 *   LED1 PA6
 *   LED2 PA7
 *   LED3 PB12
 *   LED4 PB13
 */

/* LED index values for use with stm32_setled() */

#define BOARD_LED1        0
#define BOARD_LED2        1
#define BOARD_LED3        2
#define BOARD_LED4        3
#define BOARD_NLEDS       4

/* LED bits for use with stm32_setleds() */

#define BOARD_LED1_BIT    (1 << BOARD_LED1)
#define BOARD_LED2_BIT    (1 << BOARD_LED2)
#define BOARD_LED3_BIT    (1 << BOARD_LED3)
#define BOARD_LED4_BIT    (1 << BOARD_LED4)

/* These LEDs are not used by the board port unless CONFIG_ARCH_LEDS is
 * defined.  In that case, the usage by the board port is defined in
 * include/board.h and src/stm32_leds.c. The LEDs are used to encode OS-related
 * events as follows:
 *
 *      SYMBOL            Val    Meaning                     LED state
 *                                                       LED1 LED2 LED3 LED4
 *      ----------------- ---   -----------------------  ---- ---- ---- ----  */
#define LED_STARTED       0  /* NuttX has been started   ON   OFF  OFF  OFF   */
#define LED_HEAPALLOCATE  1  /* Heap has been allocated  OFF  ON   OFF  OFF   */
#define LED_IRQSENABLED   2  /* Interrupts enabled       ON   ON   OFF  OFF   */
#define LED_STACKCREATED  3  /* Idle stack created       OFF  OFF  ON   OFF   */
#define LED_INIRQ         4  /* In an interrupt          N/C  N/C  N/C  GLOW  */
#define LED_SIGNAL        4  /* In a signal handler      N/C  N/C  N/C  GLOW  */
#define LED_ASSERTION     4  /* An assertion failed      N/C  N/C  N/C  GLOW  */
#define LED_PANIC         4  /* The system has crashed   N/C  N/C  N/C  FLASH */
#undef  LED_IDLE             /* MCU is is sleep mode         Not used         */

/* After booting, LED1-3 are not longer used by the system and can be used for
 * other purposes by the application (Of course, all LEDs are available to the
 * application if CONFIG_ARCH_LEDS is not defined.
 */

/* Buttons **************************************************************************/
/* All pulled high and will be sensed low when depressed.
 *
 *   SW2 PC11  Needs J42 closed
 *   SW3 PC12  Needs J43 closed
 *   SW4 PA0   Needs J44 closed
 */

#define BUTTON_SW2        0
#define BUTTON_SW3        1
#define BUTTON_SW4        2
#define NUM_BUTTONS       3

#define BUTTON_SW2_BIT    (1 << BUTTON_SW2)
#define BUTTON_SW3_BIT    (1 << BUTTON_SW3)
#define BUTTON_SW4_BIT    (1 << BUTTON_SW4)

/************************************************************************************
 * Public Data
 ************************************************************************************/

#ifndef __ASSEMBLY__

#undef EXTERN
#if defined(__cplusplus)
#define EXTERN extern "C"
extern "C" {
#else
#define EXTERN extern
#endif

/************************************************************************************
 * Public Function Prototypes
 ************************************************************************************/
/************************************************************************************
 * Name: stm32_boardinitialize
 *
 * Description:
 *   All STM32 architectures must provide the following entry point.  This entry point
 *   is called early in the intitialization -- after all memory has been configured
 *   and mapped but before any devices have been initialized.
 *
 ************************************************************************************/

void stm32_boardinitialize(void);

/************************************************************************************
 * Name:  up_setled and up_setleds
 *
 * Description:
 *   If CONFIG_ARCH_LEDS is defined, then NuttX will control the on-board LEDs.  If
 *   CONFIG_ARCH_LEDS is not defined, then the following interfaces are available to
 *   control the LEDs from user applications.
 *
 ************************************************************************************/

#ifndef CONFIG_ARCH_LEDS
void up_setled(int led, bool ledon);
void up_setleds(uint8_t ledset);
#endif

/************************************************************************************
 * Name: up_buttoninit
 *
 * Description:
 *   up_buttoninit() must be called to initialize button resources.  After that,
 *   up_buttons() may be called to collect the current state of all buttons or
 *   up_irqbutton() may be called to register button interrupt handlers.
 *
 ************************************************************************************/

#ifdef CONFIG_ARCH_BUTTONS
void up_buttoninit(void);

/************************************************************************************
 * Name: up_buttons
 *
 * Description:
 *   After up_buttoninit() has been called, up_buttons() may be called to collect
 *   the state of all buttons.  up_buttons() returns an 8-bit bit set with each bit
 *   associated with a button.  See the BUTTON* definitions above for the meaning of
 *   each bit in the returned value.
 *
 ************************************************************************************/

uint8_t up_buttons(void);

/************************************************************************************
 * Name: up_irqbutton
 *
 * Description:
 *   This function may be called to register an interrupt handler that will be
 *   called when a button is depressed or released.  The ID value is one of the
 *   BUTTON* definitions provided above. The previous interrupt handler address is
 *   returned (so that it may restored, if so desired).
 *
 ************************************************************************************/

#ifdef CONFIG_ARCH_IRQBUTTONS
xcpt_t up_irqbutton(int id, xcpt_t irqhandler);
#endif /* CONFIG_ARCH_IRQBUTTONS */
#endif /* CONFIG_ARCH_BUTTONS */

#undef EXTERN
#if defined(__cplusplus)
}
#endif

#endif /* __ASSEMBLY__ */
#endif /* __CONFIGS_VIEWTOOLS_STM32F107_INCLUDE_BOARD_H */
