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

#ifndef LIBXSD2CPP_INTEGER_H
#define LIBXSD2CPP_INTEGER_H

#include "nspr.h"
#include "libxsd2cpp.h"
#include "Simple.h"

namespace LIBXSD2CPP_NAMESPACE {

//-----------------------------------------------------------------------------
// Integer
//-----------------------------------------------------------------------------

/**
 * Integer is an Element that accepts only integral values.
 */
class LIBXSD2CPP_EXPORT Integer : public Simple {
public:
    /**
     * Instantiates an Integer object based on an element from a DOM tree.
     */
    static Integer *createIntegerInstance(const DOMElement *elementArg)
    {
        return new Integer(elementArg);
    }

    /**
     * Instantiates an Integer object based on an element from a DOM tree.
     */
    Integer(const DOMElement *elementArg);

    /**
     * Returns the Integer's value in the range [PR_INT32_MIN, PR_INT32_MAX].
     */
    PRInt32 getInt32Value() const;

    /**
     * Returns the Integer's value.
     */
    PRInt64 getInt64Value() const { return int64Value; }

    /**
     * Returns the Integer's value.
     */
    operator PRInt64() const { return int64Value; }

private:
    PRInt64 int64Value;
};

} // namespace LIBXSD2CPP_NAMESPACE

#endif // LIBXSD2CPP_INTEGER_H
