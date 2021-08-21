/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2021 Andrew Rogers
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
 *
 */

#include "SLCanPico.h"


int slcan_cmd_byte( uint8_t c )
{
    return SLCanPico::getInstance().cmdByte( c );
}

size_t slcan_get_bytes(uint8_t* buf, size_t n)
{
    return SLCanPico::getInstance().getBytes( buf, n );
}

bool SLCanPico::transmit(uint32_t* bits, size_t numbits)
{
    // Setup a PWM slice for the counter to measure time.
    const uint32_t slice(0);
    const uint32_t fsys(clock_get_hz(clk_sys));
    pwm_config c = pwm_get_default_config();
    pwm_config_set_clkdiv(&c, fsys/16000000.0F);
    pwm_init(slice, &c, true);
    
    // Setup GP22 for the CAN TXD output.
    gpio_init(22);
    gpio_set_dir(22, true);
    
    // Do a 500kHz square wave for now.
    uint16_t expiry( pwm_get_counter(slice) + 16 );
    for (int i=0; i<500; i++) {
        txd(0);
        waitExpiry(expiry);
        expiry += 16;
        txd(1);
        waitExpiry(expiry);
        expiry += 16;
    }
    
    
    // Setup GP21 for the CAN RXD input.
    // Disable all interrupts.
    // Bit loop.
    // Enable all interrupts.
    return false;
}

