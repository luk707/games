#pragma once
#include "raylib-3.0.0-Win64-msvc15/include/raylib.h"

namespace Common {
    namespace Math {
        class Vector3 : public ::Vector3
        {
        public:
            Vector3(float x, float y, float z);
            Vector3 operator+(const Vector3& b);
            Vector3 operator*(const float& b);
            Vector3 operator*(const Vector3& b);
        };
    }
}


