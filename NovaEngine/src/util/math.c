#include "src/util/math.h"

static inline vec2i32s vec2i32sadd(vec2i32s a, vec2i32s b) {
    return (vec2i32s){
        .x = a.x + b.x,
        .y = a.y + b.y
    };
}

static inline vec2i32 vec2i32add(vec2i32 a, vec2i32 b) {
    return (vec2i32){
        .x = a.x + b.x,
        .y = a.y + b.y
    };
}

static inline vec2i32 vec2i32sub(vec2i32 a, vec2i32 b) {
    return (vec2i32){
        .x = a.x - b.x,
        .y = a.y - b.y
    };
}


static inline vec2f32 vec2f32add(vec2f32 a, vec2f32 b) {
    return (vec2f32){
        .x = a.x + b.x,
        .y = a.y + b.y
    };
}

static inline vec2f32 vec2f32sub(vec2f32 a, vec2f32 b) {
    return (vec2f32){
        .x = a.x - b.x,
        .y = a.y - b.y
    };
}

static inline vec2i64 vec2i64add(vec2i64 a, vec2i64 b) {
    return (vec2i64){
        .x = a.x + b.x,
        .y = a.y + b.y
    };
}

static inline vec2i64 vec2i64sub(vec2i64 a, vec2i64 b) {
    return (vec2i64){
        .x = a.x - b.x,
        .y = a.y - b.y
    };
}


static inline vec2f64 vec2f64add(vec2f64 a, vec2f64 b) {
    return (vec2f64){
        .x = a.x + b.x,
        .y = a.y + b.y
    };
}

static inline vec2f64 vec2f64sub(vec2f64 a, vec2f64 b) {
    return (vec2f64){
        .x = a.x - b.x,
        .y = a.y - b.y
    };
}


static inline vec2i64 vec2i64scale(vec2i64 v, i64 scale) {
    return (vec2i64){
        .x = v.x * scale,
        .y = v.y * scale
    };
}

static inline vec2i32 vec2i32scale(vec2i32 v, i32 scale) {
    return (vec2i32){
        .x = v.x * scale,
        .y = v.y * scale
    };
}

static inline vec2f64 vec2f64scale(vec2f64 v, f32 scale) {
    return (vec2f64){
        .x = v.x * scale,
        .y = v.y * scale
    };
}

static inline vec2f32 vec2f32scale(vec2f32 v, f32 scale) {
    return (vec2f32){
        .x = v.x * scale,
        .y = v.y * scale
    };
}


static inline f32 vec2f32length(vec2f32 v) {
    return sqrtf(v.x * v.x + v.y * v.y);
}

static inline vec2f32 vec2f32normalize(vec2f32 v) {
    f32 len = vec2f32length(v);
    if (len == 0) return (vec2f32){0, 0};
    return vec2f32scale(v, 1.0f / len);
}