#pragma once
#pragma once

# define _CRTDBG_MAP_ALLOC
#include< stdlib.h >
#include< crtdbg.h >
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdint.h>

#define  kDEFAULT_VEC_SIZE 10
#define kVEC_SIZE_RATIO 2

typedef struct Vector {

	uint32_t size;
	uint32_t elem_size;
	uint32_t capacity;
	void *vector;

} vector_t;



inline void vec_init(vector_t *vi, uint32_t size, uint32_t elem_size) {
	vi->vector = malloc(elem_size*size);
	vi->size = 0;
	vi->capacity = size;
	vi->elem_size = elem_size;
}
inline void vec_init_with_array(vector_t *vi, uint32_t size, uint32_t elem_size, void* arr) {
	vi->vector = malloc(elem_size*size);
	vi->size = 0;
	vi->capacity = size;
	vi->elem_size = elem_size;
	memcpy(vi->vector, arr, elem_size*size);
}

inline void* vec_at(vector_t *vec, uint32_t index) {
	if (index > vec->size) {
		fprintf(stderr, "BAD INDEX\n");
		fflush(stderr);
		exit(1);
	}
	uint8_t *ret = ((uint8_t*)vec->vector) + vec->elem_size*index;
	return ret;
}
inline uint32_t vec_get_used_mem_size(vector_t *vi) {
	return vi->elem_size*vi->size;
}
inline void vec_copy_array(vector_t *vi, void* arr) {
	memcpy(arr, vi->vector, vec_get_used_mem_size(vi));
}
inline void vec_copy_to_vec(vector_t *src, vector_t *dst) {
	*dst = *src;
	dst->vector = malloc(src->capacity*src->elem_size);
	memcpy(dst->vector, src->vector, vec_get_used_mem_size(src));
}
inline void vec_increase_size(vector_t *vi) {

	vi->vector = realloc(vi->vector, (size_t)vi->elem_size*(vi->capacity*kVEC_SIZE_RATIO));
	if (vi->vector == NULL) {
		fprintf(stderr, "OUT OF MEMORY\n");
		fflush(stderr);
		exit(1);
	}
	vi->capacity *= kVEC_SIZE_RATIO;
}
inline void vec_push(vector_t *vi, void *elem) {
	if (vi->size == vi->capacity) {
		vec_increase_size(vi);
	}
	memcpy(((char*)vi->vector) + vi->elem_size*vi->size, elem, vi->elem_size);
	vi->size++;
}
inline void vec_add(vector_t *vi, void *elem) {
	if (vi->size == vi->capacity) {
		vec_increase_size(vi);
	}
	memcpy(((char*)vi->vector) + vi->elem_size*vi->size, elem, vi->elem_size);
	vi->size++;
}

inline void vec_free(vector_t *vi) {
	free(vi->vector);
}
inline void* vec_peek(vector_t *vi) {

	return (char*)vi->vector + (vi->size*vi->elem_size);
}
inline void vec_pop(vector_t *vi, void * elem) {
	if (vi->size <= 0) {
		fprintf(stderr, "NOTHING TO REMOVE!\n");
		fflush(stderr);
		exit(1);
	}
	vi->size--;
	memcpy(elem, (char*)vi->vector + (vi->size*vi->elem_size), vi->elem_size);
}
inline void vec_insert(vector_t *vi, uint32_t index, void* elem) {

	if (index >= vi->size) {
		fprintf(stderr, "BAD INDEX\n");
		fflush(stderr);
		exit(1);
	}
	if (vi->size == vi->capacity)vec_increase_size(vi);

	memmove((void*)((char*)vi->vector + vi->elem_size*(index + 1)),
		(void*)((char*)vi->vector + vi->elem_size*(index)),
		vi->elem_size*(vi->size - index));
	memcpy((void*)((char*)vi->vector + vi->elem_size*(index)), elem, vi->elem_size);
	vi->size++;


}
inline int vec_find_index_of_largest(vector_t *vi, uint32_t si, int(*cmp)(void * a, void *b)) {
	int32_t largestIndex = si;
	for (int i = si; i < vi->size; i++) {
		int icmp = cmp((char*)vi->vector + vi->elem_size*i,
			(char*)vi->vector + vi->elem_size*largestIndex);

		if (icmp > 0) {
			largestIndex = i;
		}
	}
	return largestIndex;
}

inline int vec_find_index_of_smallest(vector_t *vi, uint32_t si, int(*cmp)(void * a, void *b)) {
	int32_t largestIndex = si;
	for (int i = si; i < vi->size; i++) {
		int icmp = cmp((char*)vi->vector + vi->elem_size*i,
			(char*)vi->vector + vi->elem_size*largestIndex);


		if (icmp < 0) {
			largestIndex = i;
		}



	}

	return largestIndex;
}


inline int vec_find_value(vector_t *vi, void* elem, int(*cmp)(void * a, void *b)) {
	for (int i = 0; i < vi->size; i++) {
		if (cmp((char*)vi->vector + vi->elem_size*i, elem) == 0)
			return i;
	}
	return -1;
}
inline void * vec_get_base(vector_t *vec) {
	return vec->vector;

}


inline void vec_swap(vector_t *vec, uint32_t index, uint32_t index2) {

	char* temp =(char*) malloc(vec->elem_size);

	memcpy(temp, vec_at(vec, index), vec->elem_size);
	memcpy(vec_at(vec, index), vec_at(vec, index2), vec->elem_size);
	memcpy(vec_at(vec, index2), temp, vec->elem_size);

	free(temp);

}
inline void vec_copy_from_index(vector_t *vec, uint32_t index, void* dst) {
	if (index > vec->size) {
		fprintf(stderr, "BAD INDEX\n");
		fflush(stderr);
		exit(1);
	}
	memcpy(dst, vec_at(vec, index), vec->elem_size);


}
inline void vec_copy_to_index(vector_t *vec, uint32_t index, void* src) {
	if (index > vec->size) {
		fprintf(stderr, "BAD INDEX\n");
		fflush(stderr);
		exit(1);
	}
	memcpy((char*)vec->vector + vec->elem_size*index, src, vec->elem_size);


}
inline void vec_sort_ascending(vector_t *vi, int(*cmp)(void * a, void *b)) {
	char *temp = (char*)malloc(vi->elem_size);
	for (int i = 0; i < vi->size; i++) {
		//find smallest value
		int sm_index = vec_find_index_of_smallest(vi, i, cmp);

		memmove(temp, (char*)vi->vector + vi->elem_size*i, vi->elem_size);
		memmove((char*)vi->vector + vi->elem_size*i,
			(char*)vi->vector + vi->elem_size*sm_index,
			vi->elem_size);
		memmove((char*)vi->vector + vi->elem_size*sm_index, temp, vi->elem_size);


	}

	free(temp);

}
inline void vec_sort_descending(vector_t *vi, int(*cmp)(void * a, void *b)) {
	char *temp = (char*)malloc(vi->elem_size);
	for (int i = 0; i < vi->size; i++) {
		//find smallest value
		int sm_index = vec_find_index_of_largest(vi, i, cmp);

		memmove(temp, (char*)vi->vector + vi->elem_size*i, vi->elem_size);
		memmove((char*)vi->vector + vi->elem_size*i,
			(char*)vi->vector + vi->elem_size*sm_index,
			vi->elem_size);
		memmove((char*)vi->vector + vi->elem_size*sm_index, temp, vi->elem_size);


	}

	free(temp);

}
inline void vec_for_each(vector_t *vi, void(*action)(void* elem)) {
	for (int i = 0; i < vi->size; i++) {

		action((char*)vi->vector + vi->elem_size*i);
	}


}



inline void vec_copy_to_array(vector_t *vec, uint32_t index, void* dst) {
	if (index > vec->size) {
		fprintf(stderr, "BAD INDEX\n");
		fflush(stderr);
		exit(1);
	}
	void* loc = (char*)vec->vector + vec->elem_size*index;
	memcpy(dst, loc, vec->elem_size);
}

inline void vec_copy_init(vector_t *vec, vector_t *new_) {
	*new_ = *vec;
	new_->vector = malloc(vec->elem_size*vec->capacity);
	memcpy(new_->vector, vec->vector, vec->elem_size*vec->capacity);
}
inline void vec_shrink(vector_t *vec) {
	//less than a quater of capacity
	if ((float)vec->size < (float)vec->capacity / ((float)kVEC_SIZE_RATIO*2.0f)) {
		char* new_ = (char*)malloc(vec->capacity / 2 * vec->elem_size);
		memcpy(new_, vec->vector, vec->elem_size*vec->capacity / 2);
		free(vec->vector);
		vec->vector = new_;
		vec->capacity /= 2;
	}
}
inline void vec_shrink_mem(vector_t *vi) {
	char* new_ = (char*)malloc(vi->size * vi->elem_size);
	memcpy(new_, vi->vector, vi->elem_size*vi->size);
	free(vi->vector);
	vi->vector = new_;
	vi->capacity = vi->size;
}
inline void vec_remove(vector_t *vi, uint32_t index) {

	if (index >= vi->size) {
		fprintf(stderr, "BAD INDEX\n");
		fflush(stderr);
		exit(1);
	}

	memmove((char*)vi->vector + vi->elem_size*index,
		(char*)vi->vector + vi->elem_size*(index + 1),
		(vi->size - index - 1)*vi->elem_size);

	vi[0].size--;
	vec_shrink(vi);
}

inline void* vec_next(vector_t *vec, void* iter) {
	int32_t i = *(uint32_t*)iter;
	if (i >= vec->size) {
		return NULL;
	}
	((uint32_t*)iter)[0] += 1;
	return vec_at(vec, i);
}
inline void* vec_new_iter(vector_t *vec) {
	int32_t* i =(int32_t*) malloc(4);
	*i = 0;
	return i;

}

inline void vec_free_iter(vector_t *vec, void* iter) {
	free(iter);
}

