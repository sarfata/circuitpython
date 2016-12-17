/*
 * This file is part of the Micro Python project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Glenn Ruben Bakke
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#define PCA10056

#define MICROPY_HW_BOARD_NAME       "PCA10056"
#define MICROPY_HW_MCU_NAME         "NRF52840"
#define MICROPY_PY_SYS_PLATFORM     "nrf52840-PDK"

#define MICROPY_PY_MACHINE_SPI      (0)

#define MICROPY_HW_HAS_SWITCH       (0)
#define MICROPY_HW_HAS_FLASH        (0)
#define MICROPY_HW_HAS_SDCARD       (0)
#define MICROPY_HW_HAS_MMA7660      (0)
#define MICROPY_HW_HAS_LIS3DSH      (0)
#define MICROPY_HW_HAS_LCD          (0)
#define MICROPY_HW_ENABLE_RNG       (0)
#define MICROPY_HW_ENABLE_RTC       (0)
#define MICROPY_HW_ENABLE_TIMER     (0)
#define MICROPY_HW_ENABLE_SERVO     (0)
#define MICROPY_HW_ENABLE_DAC       (0)
#define MICROPY_HW_ENABLE_CAN       (0)

#define MICROPY_HW_LED_PULLUP       (1)

#define MICROPY_HW_LED1             (13) // LED1
#define MICROPY_HW_LED2             (14) // LED2
#define MICROPY_HW_LED3             (15) // LED3
#define MICROPY_HW_LED4             (16) // LED4

// UART config
#define MICROPY_HW_UART1_RX         (8)
#define MICROPY_HW_UART1_TX         (6)
#define MICROPY_HW_UART1_CTS        (7)
#define MICROPY_HW_UART1_RTS        (5)
#define MICROPY_HW_UART1_HWFC       (1)

#define MICROPY_HW_PWM0_NAME        "PWM0"
#define MICROPY_HW_PWM1_NAME        "PWM1"
#define MICROPY_HW_PWM2_NAME        "PWM2"
#if 0
#define MICROPY_HW_PWM3_NAME        "PWM3"
#endif

#define HELP_TEXT_BOARD_LED         "1,2,3,4"
