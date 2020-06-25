#pragma once
#include <glmath.h>

typedef struct {
	vec3 position;
	vec3 normal;
} vertex_t;

extern vertex_t vertices[];
extern const unsigned vertices_size;
extern const unsigned vertices_count;
