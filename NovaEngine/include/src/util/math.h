#pragma once

#include "def.h"


typedef struct vec2i32 {
    i32 x;
    i32 y;
} vec2i32;

typedef int32_t i32s;

typedef struct vec2i32s {
    i32s x;
    i32s y;
} vec2i32s;

typedef struct vec2f32 {
    f32 x;
    f32 y;
} vec2f32;


typedef struct vec2f64 {
    f32 x;
    f32 y;
} vec2f64;


typedef struct vec2i64 {
    i64 x;
    i64 y;
} vec2i64;

static inline vec2i32s vec2i32sadd(vec2i32s a, vec2i32s b); 
static inline vec2i32 vec2i32add(vec2i32 a, vec2i32 b);

static inline vec2i32 vec2i32sub(vec2i32 a, vec2i32 b);


static inline vec2f32 vec2f32add(vec2f32 a, vec2f32 b);

static inline vec2f32 vec2f32sub(vec2f32 a, vec2f32 b);

static inline vec2i64 vec2i64add(vec2i64 a, vec2i64 b);

static inline vec2i64 vec2i64sub(vec2i64 a, vec2i64 b);


static inline vec2f64 vec2f64add(vec2f64 a, vec2f64 b);

static inline vec2f64 vec2f64sub(vec2f64 a, vec2f64 b);


static inline vec2i64 vec2i64scale(vec2i64 v, i64 scale);

static inline vec2i32 vec2i32scale(vec2i32 v, i32 scale);

static inline vec2f64 vec2f64scale(vec2f64 v, f32 scale);

static inline vec2f32 vec2f32scale(vec2f32 v, f32 scale);


static inline f32 vec2f32length(vec2f32 v);

static inline vec2f32 vec2f32normalize(vec2f32 v);