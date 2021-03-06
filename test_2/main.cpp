/***************************************************************************
 *   Copyright (C) 2020 by Silvano Seva                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   As a special exception, if other files instantiate templates or use   *
 *   macros or inline functions from this file, or you compile this file   *
 *   and link it with other works to produce a work based on this file,    *
 *   this file does not by itself cause the resulting work to be covered   *
 *   by the GNU General Public License. However the source code for this   *
 *   file must still be made available in accordance with the GNU General  *
 *   Public License. This exception does not invalidate any other reasons  *
 *   why a work based on this file might be covered by the GNU General     *
 *   Public License.                                                       *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, see <http://www.gnu.org/licenses/>   *
 ***************************************************************************/

#include "stm32f405xx.h"

template <unsigned int P, unsigned char N>
class Pin
{
public:
    static void high()
    {
        reinterpret_cast<GPIO_TypeDef*>(P)->BSRR = 1 << N;
    }

    static void low()
    {
        reinterpret_cast<GPIO_TypeDef*>(P)->BSRR = 1 << (N + 16);
    }

private:
    Pin();
};

static void delay()
{
    volatile int i;
    int j=0;
    for(i=0;i<1000000;i++)
    {
        j++;
    }
}

using red = Pin<GPIOE_BASE, 1>;
using grn = Pin<GPIOE_BASE, 0>;

int main()
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
    GPIOE->MODER |= (1 << 2) | 1;       // PE0 and PE1 outputs

    grn::high();
    red::low();

    while(1)
    {
        red::high();
        delay();
        red::low();
        delay();
    }

    return 0;
}
