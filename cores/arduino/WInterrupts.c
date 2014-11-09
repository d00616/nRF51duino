/*
 Copyright (c) 2013 OpenSourceRF.com.  All right reserved.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 See the GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/*
  Copyright (c) 2011-2012 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "WInterrupts.h"

void attachInterrupt(uint8_t IRQn, callback_t callback)
{
#ifndef __NRF51SDK_STARTUP__
  dynamic_handlers[IRQn] = callback;
  rfduino_nvic_enableirq(IRQn);
#else
 #warning "Dynamic interrupts are not implemented yes. Please fix this"
#endif
}

void detachInterrupt(uint8_t IRQn)
{
#ifndef __NRF51SDK_STARTUP__
  rfduino_nvic_disableirq(IRQn);
  dynamic_handlers[IRQn] = NULL;
#else
 #warning "Dynamic interrupts are not implemented yes. Please fix this"
#endif
}

void attachPinInterrupt(uint32_t pin, pin_callback_t callback, uint32_t mode)
{
  RFduino_pinWakeCallback(pin, mode, callback);
}

void detachPinInterrupt(uint32_t pin)
{
  RFduino_pinWakeCallback(pin, DISABLE, NULL);
}
