#
# DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
#
# Copyright 2008 Sun Microsystems, Inc. All rights reserved.
#
# THE BSD LICENSE
#
# Redistribution and use in source and binary forms, with or without 
# modification, are permitted provided that the following conditions are met:
#
# Redistributions of source code must retain the above copyright notice, this
# list of conditions and the following disclaimer. 
# Redistributions in binary form must reproduce the above copyright notice, 
# this list of conditions and the following disclaimer in the documentation 
# and/or other materials provided with the distribution. 
#
# Neither the name of the  nor the names of its contributors may be
# used to endorse or promote products derived from this software without 
# specific prior written permission. 
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER 
# OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

# The framework library contains the functions common to the netsite 
# servers, to implement configuration, server application functions,
# and speak network protocols. Depends on the base library for
# definitions.
BUILD_ROOT=../../..
USE_NSPR=1
USE_CLIENTLIBS=1

include ${BUILD_ROOT}/make/base.mk

MODULE=LibDrCache

all::


LOCAL_INC=-I.. -I../public -I../../support
LOCAL_DEF+= -DSERVER_BUILD
LOCAL_DEF+= -DES2NSDB
LOCAL_DEF+= -DPEER_SNMP
LOCAL_DEF+= -DBUILD_DLL

# object list is here
LOCAL_SRC = \
			drcache    \
			drnsapi

CPPSRCS=$(LOCAL_SRC:=.cpp)

AR_TARGET=drcache
AR_OBJS=$(LOCAL_SRC)
EXPORT_LIBRARIES=$(AR_TARGET)

# this should always be last!
include ${BUILD_ROOT}/make/rules.mk
