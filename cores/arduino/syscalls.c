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
  Copyright (c) 2011 Arduino.  All right reserved.

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

/**
  * \file syscalls_sam3.c
  *
  * Implementation of newlib syscall.
  *
  */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/


#include "syscalls.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#if defined (  __GNUC__  ) /* GCC CS3 */
  #include <sys/types.h>
  #include <sys/stat.h>
#endif

/*----------------------------------------------------------------------------
 *        Exported variables
 *----------------------------------------------------------------------------*/

#undef errno
extern int errno ;
extern int __bss_end__;

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/
extern void _exit( int status ) ;
extern void _kill( int pid, int sig ) ;
extern int _getpid ( void ) ;

extern caddr_t _sbrk ( int incr )
{
    static unsigned char *heap = NULL ;
    unsigned char *prev_heap ;

    if ( heap == NULL )
    {
        heap = (unsigned char *)&__bss_end__ ;
    }
    prev_heap = heap;

    heap += incr ;

    return (caddr_t) prev_heap ;
}

extern int link( char *cOld, char *cNew )
{
    return -1 ;
}

extern int _close( int file )
{
    return -1 ;
}

extern int _fstat( int file, struct stat *st )
{
    st->st_mode = S_IFCHR ;

    return 0 ;
}

extern int _isatty( int file )
{
    return 1 ;
}

extern int _lseek( int file, int ptr, int dir )
{
    return 0 ;
}

extern int _read(int file, char *ptr, int len)
{
    return 0 ;
}

extern int _write( int file, char *ptr, int len )
{
    // declared in variant.cpp
    // UART0_TX will not TX or lockup flushing TX if UART0 has not been started
    extern void UART0_TX( uint8_t uc_data );

    int i;
    for (i = 0; i < len; i++, ptr++)
        UART0_TX(*ptr);
    return i;
}

extern void _exit( int status )
{
    printf( "Exiting with status %d.\n", status ) ;

    for ( ; ; ) ;
}

extern void _kill( int pid, int sig )
{
    return ;
}

extern int _getpid ( void )
{
    return -1 ;
}
