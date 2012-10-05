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

#ifndef LIBXSD2CPP_BOOL_H
#define LIBXSD2CPP_BOOL_H

#include "nspr.h"
#include "libxsd2cpp.h"
#include "Simple.h"

namespace LIBXSD2CPP_NAMESPACE {

//-----------------------------------------------------------------------------
// Bool
//-----------------------------------------------------------------------------

/**
 * Bool is an Element that accepts only boolean values.
 */
class LIBXSD2CPP_EXPORT Bool : public Simple {
public:
    /**
     * Instantiates a Bool object based on an element from a DOM tree.
     */
    static Bool *createBoolInstance(const DOMElement *element)
    {
        return new Bool(element);
    }

    /**
     * Instantiates a Bool object based on an element from a DOM tree.
     */
    Bool(const DOMElement *elementArg);

    /**
     * Returns the Bool's contents as a PRBool.
     */
    PRBool getBoolValue() const { return boolValue; }

    /**
     * Returns the Bool's contents as a PRBool.
     */
    operator PRBool() const { return boolValue; }

private:
    PRBool boolValue;
};

} // namespace LIBXSD2CPP_NAMESPACE

#endif // LIBXSD2CPP_BOOL_H
