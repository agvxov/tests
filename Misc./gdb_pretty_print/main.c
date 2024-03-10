/* vector.c
 * Copyright 2023 Anon Anonson, Ognjen 'xolatile' Milan Robovic, Emil Williams
 * SPDX Identifier: GPL-3.0-only / NO WARRANTY / NO GUARANTEE */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// TODO: Handle error warnings?
// TODO: Implement more useful functions?

typedef struct {
	char   *          data;
	size_t    element_size;
	size_t   element_count;
} vector_t;

extern void vector_init(vector_t *        vector,
                        size_t      element_size,
                        size_t     element_count);

extern void vector_push(vector_t * vector,
                        void     *   data);

extern void vector_pop(vector_t * vector);

extern void * vector_get(const vector_t * const   vector,
                         const size_t            element);

extern void vector_set(vector_t *  vector,
                       void     *    data,
                       size_t     element);

extern void vector_free(vector_t * vector);

void vector_init(vector_t *        vector,
                 size_t      element_size,
                 size_t     element_count) {
	assert(element_size);

	vector->data          = NULL;
	vector->element_size  = element_size;
	vector->element_count = element_count;

	vector->data = calloc(vector->element_count, vector->element_size);

	assert(vector->data);
}

void vector_push(vector_t * vector,
                 void     *   data) {
	assert(vector);

	vector->element_count += 1;

	vector->data = realloc(vector->data,
	                       vector->element_size * vector->element_count);

	assert(vector->data);

	memcpy(&vector->data[(vector->element_count - 1) * vector->element_size],
	       data,
	       vector->element_size);
}

void vector_pop(vector_t * vector) {
	assert(vector); // UNUSED
}

void * vector_get(const vector_t * const  vector,
                  const size_t           element) {
	assert(vector);
	assert(element < vector->element_count);

	return &vector->data[vector->element_size * element];
}

void vector_set(vector_t *  vector,
                void     *    data,
                size_t     element) {
	assert(vector);
	assert(element >= vector->element_count);

	memcpy(&vector->data[vector->element_size * element],
	       data,
	       vector->element_size);
}

void vector_free(vector_t * vector) {
	free(vector->data);
}


// @COMPILECMD gcc $@ -ggdb -o main

typedef struct {
	int i;
	vector_t v;
} mybs;

signed main(){
	mybs m;
	m.i = -7;
	vector_init(&m.v, sizeof(char *), 0);

	char * a = "abc";
	char * b = "def";
	char * c = "hhhjj";
	char * d = "kjhk";

	vector_push(&m.v, &a);
	vector_push(&m.v, &b);
	vector_push(&m.v, &c);
	vector_push(&m.v, &d);

	return 0;
}
