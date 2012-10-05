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

#ifndef __symbols_h
#define __symbols_h

/*
 * Description (symbols.h)
 *
 *	This file describes the interface to an ACL symbol table
 *	implementation.  The symbol table provides for storing symbols
 *	keyed by name and type, creating a separate name space for
 *	each symbol type.
 */

#ifdef __PRIVATE_SYMBOLS

#include "plhash.h"
#include "base/crit.h"

/*
 * Description (SymTable_t)
 *
 *	This type describes a symbols table.  It contains a pointer to
 *	an NSPR hash table and a pointer to a monitor.  The monitor is
 *	needed even for read access to the symbol table because NSPR
 *	modifies the list for a hash bucket when a name is looked up.
 */

typedef struct SymTable_s SymTable_t;
struct SymTable_s {
    CRITICAL stb_crit;			/* monitor pointer */
    PRHashTable * stb_ht;		/* hash table pointer */
};


/* Private functions defined in symbols.c */
static PRHashEntry * symAllocEntry(void * pool, const void *unused);
static void * symAllocTable(void * pool, PRSize size);
static int symCmpName(const void * name1, const void * name2);
static int symCmpValue(const void * value1, const void * value2);
static PRHashNumber symHash(const void * symkey);
static void symFreeEntry(void * pool, PRHashEntry * he, uintn flag);
static void symFreeTable(void * pool, void * item);

#endif /* __PRIVATE_SYMBOLS */

/*
 * Description (Symbol_t)
 *
 *	This type describes a symbol table entry.  A symbol is
 *	identified by the combination of its name and type.  This
 *	structure is normally embedded in a structure for a particular
 *	symbol type, which will contain the symbol "value" information
 *	as well.
 */

typedef struct Symbol_s Symbol_t;
struct Symbol_s {
    char * sym_name;			/* pointer to symbol name string */
    int sym_type;			/* symbol type */
    void *sym_data;			/* symbol data storage */
};

/* Define error return codes */
#define SYMERRNOMEM	-1		/* insufficient dynamic memory */
#define SYMERRDUPSYM	-2		/* duplicate symbol name and type */
#define SYMERRNOSYM	-3		/* symbol name and type not found */

/* Define return flags for symTableEnumerate() func() */
#define SYMENUMSTOP	0x1		/* terminate enumeration */
#define SYMENUMREMOVE	0x2		/* remove entry from symbol table */

NSPR_BEGIN_EXTERN_C

/* Public functions defined in symbols.c */
extern int symTableAddSym(void * table, Symbol_t * newsym, void * symref);
extern void symTableRemoveSym(void * table, Symbol_t * sym);
extern void symTableDestroy(void * table, int flags);
typedef int (*enumSTfunc)(Symbol_t * sym, void * parg);
extern void symTableEnumerate(void * table, void * argp, enumSTfunc func);
extern int symTableFindSym(void * table, char * symname,
			   int symtype, void **psymref);
extern int symTableNew(void **ptable);

NSPR_END_EXTERN_C

#endif /* __symbols_h */
