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
 * util_rng.cpp: Fast, MT-hot pseudo random number generator
 *
 * Chris Elving
 */

#include "pk11func.h"
#include "base/arcfour.h"
#include "base/session.h"
#include "base/util.h"

#define RNG_SEED_SIZE 32
#define RNG_ARCFOUR_DISCARD 1536
#define RNG_RESEED_THRESHOLD 1048576

typedef struct {
    Arcfour arcfour;
    int remaining;
} RngThreadData;

SlotDestructorFunc rng_destructor;

static int _rng_slot = session_alloc_thread_slot(&rng_destructor);


/* ---------------------------- rng_destructor ---------------------------- */

void rng_destructor(void *data)
{
    PERM_FREE(data);
}


/* ----------------------------- util_random ------------------------------ */

NSAPI_PUBLIC void util_random(void *buf, size_t sz)
{
    session_random(NULL, buf, sz);
}


/* ---------------------------- session_random ---------------------------- */

NSAPI_PUBLIC void session_random(Session *sn, void *buf, size_t sz)
{
    RngThreadData *rng = (RngThreadData *) session_get_thread_data(sn, _rng_slot);
    if (!rng) {
        rng = (RngThreadData *) PERM_CALLOC(sizeof(RngThreadData));
        session_set_thread_data(sn, _rng_slot, rng);
    }

    rng->remaining -= sz;

    if (rng->remaining < 0) {
        unsigned char seed[RNG_SEED_SIZE];
        PK11_GenerateRandom(seed, sizeof(seed));
        arcfour_init(&rng->arcfour, seed, sizeof(seed));
        arcfour_discard(&rng->arcfour, RNG_ARCFOUR_DISCARD);
        rng->remaining = RNG_RESEED_THRESHOLD + (signed char) seed[0];
    }

    arcfour_output(&rng->arcfour, buf, sz);
}
