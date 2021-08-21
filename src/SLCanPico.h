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

#ifndef SLCAN_PICO_H
#define SLCAN_PICO_H

#include <stdint.h>
#include <stddef.h>

#include "hardware/clocks.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"

#ifdef __cplusplus
extern "C" {
#endif
int slcan_cmd_byte(uint8_t c);
size_t slcan_get_bytes(uint8_t* buf, size_t n);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include "SLCan.h"

class SLCanPico : public SLCan
{
public:
    static SLCanPico& getInstance()
    {
        static SLCanPico instance;
        return instance;
    }

protected:
    virtual bool transmit(uint32_t* bits, size_t numbits);

private:
    SLCanPico() {}; // Private constructor. This is a singleton class.
    inline void waitExpiry(uint16_t expiry)
    {
        const uint32_t slice(0);
        int16_t elapsed = pwm_get_counter(slice) - expiry;
        while( elapsed < 0) elapsed = pwm_get_counter(slice) - expiry; // Tight loop waiting for counter to reach expiry.
    }
    inline void txd(bool v)
    {
        gpio_put(22,v);
    }

};
#endif // __cplusplus

#endif  // SLCAN_PICO_H

