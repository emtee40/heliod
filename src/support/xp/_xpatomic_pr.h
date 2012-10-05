/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 * Copyright 2008 Sun Microsystems, Inc. All rights reserved.
 *
 * THE BSD LICENSE
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer. 
 * Redistributions in binary form must reproduce the above copyright notice, 
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution. 
 *
 * Neither the name of the  nor the names of its contributors may be
 * used to endorse or promote products derived from this software without 
 * specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER 
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * _xpatomic_pr.h
 *
 * Atomic operation inlines for platforms that use the NSPR 32-bit atomic
 * implementations.
 */

#ifndef _XP_XPATOMIC_H
#error This file should only be included by xpatomic.h
#endif

#include "pratom.h"

XP_INLINE XPUint32 XP_AtomicAdd32(volatile XPUint32 *target, XPInt32 delta)
{
    return (XPUint32) PR_AtomicAdd((PRInt32 *) target, delta);
}

XP_INLINE XPUint32 XP_AtomicDecrement32(volatile XPUint32 *target)
{
    return (XPUint32) PR_AtomicDecrement((PRInt32 *) target);
}

XP_INLINE XPUint32 XP_AtomicIncrement32(volatile XPUint32 *target)
{
    return (XPUint32) PR_AtomicIncrement((PRInt32 *) target);
}

XP_INLINE XPUint32 XP_AtomicSwap32(volatile XPUint32 *target, XPUint32 newvalue)
{
    return (XPUint32) PR_AtomicSet((PRInt32 *) target, newvalue);
}

XP_INLINE XPUint32 XP_AtomicLoad32(volatile XPUint32 *target)
{
    /*
     * Since we can only guarantee atomicity if *target is contained entirely
     * in a single cache line, we require that all 32-bit values are 32-bit
     * aligned.
     */
    XP_ASSERT(((size_t) target & (sizeof(XPUint32) - 1)) == 0);

    return *target;
}
