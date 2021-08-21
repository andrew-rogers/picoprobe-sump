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

#include  "SLCan.h"

int slcan_cmd_byte( uint8_t c )
{
    return SLCan::getInstance().cmdByte( c );
}

size_t slcan_get_bytes(uint8_t* buf, size_t n)
{
    return SLCan::getInstance().getBytes( buf, n );
}

int SLCan::cmdByte( char c )
{
    if( c=='a' ) {
        m_got = true;
        return 1;
    }
    return 0;
}

size_t SLCan::getBytes( uint8_t* buf, size_t n )
{
    if( m_got && n>=2) {
        buf[0]='A';
        buf[1]='R';
        m_got = false;
        return 2;
    }
    return 0;
}
