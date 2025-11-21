#ifndef MATH_TYPES_H
#define MATH_TYPES_H

#include <cmath>


// Simple 2D vector (float precision)
struct float2 {
    float x, y;
    float2() : x(0), y(0) {}
    float2(float x, float y) : x(x), y(y) {}
};

// Simple 3D vector
struct float3 {
    float x, y, z;

    float3() : x(0), y(0), z(0) {}
    float3(float x, float y, float z) : x(x), y(y), z(z) {}

    float3 operator+(const float3& v) const { return float3(x + v.x, y + v.y, z + v.z); }
    float3 operator-(const float3& v) const { return float3(x - v.x, y - v.y, z - v.z); }
    float3 operator*(float s) const { return float3(x * s, y * s, z * s); }
    float3 operator/(float s) const { return float3(x / s, y / s, z / s); }

    float length() const { return sqrtf(x*x + y*y + z*z); }
    float3 normalize() const {
        float len = length();
        return (len > 0.0f) ? (*this / len) : float3(0, 0, 0);
    }

    static float dot(const float3& a, const float3& b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    static float3 cross(const float3& a, const float3& b) {
        return float3(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        );
    }
};

#endif