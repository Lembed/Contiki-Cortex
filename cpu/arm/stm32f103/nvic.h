/*
 * Copyright (c) 2015,
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * This file is part of the Contiki desktop OS.
 *
 *
 */


#ifndef NVIC_H_LE94F5JS4D__
#define NVIC_H_LE94F5JS4D__

#include <stm32f10x_map.h>
#include <stm32f10x_nvic.h>




#define NVIC_ENABLE_INT(i)      WRITE_REG(NVIC->ISER[(i)/32], 1<<((i) & 0x1f))
#define NVIC_DISABLE_INT(i)     WRITE_REG(NVIC->ICER[(i)/32], 1<<((i) & 0x1f))
#define NVIC_SET_PENDING(i)     WRITE_REG(NVIC->ISPR[(i)/32], 1<<((i) & 0x1f))
#define NVIC_CLEAR_PENDING(i)   WRITE_REG(NVIC->ICPR[(i)/32], 1<<((i) & 0x1f))

#define NVIC_SET_PRIORITY(i,p)  MODIFY_REG(NVIC->IPR[(i)/4], 0xf<<(((i)&3)*8), (p)<<(((i)&3)*8))

#define NVIC_SET_SYSTICK_PRI(p) MODIFY_REG(SCB->SHPR[2],  0xf<<24, (p)<<24)






#endif /* NVIC_H_LE94F5JS4D__ */
