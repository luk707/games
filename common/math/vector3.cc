#include "raylib-3.0.0-Win64-msvc15/include/raylib.h"
#include "vector3.hh"

Common::Math::Vector3::Vector3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Common::Math::Vector3 Common::Math::Vector3::operator+(
    const Common::Math::Vector3& b
)
{
    return Common::Math::Vector3(this->x + b.x, this->y + b.y, this->z + b.z);
}

Common::Math::Vector3 Common::Math::Vector3::operator*(
    const float& b
)
{
    return Common::Math::Vector3(this->x * b, this->y * b, this->z * b);
}

Common::Math::Vector3 Common::Math::Vector3::operator*(
    const Common::Math::Vector3& b
)
{
    return Common::Math::Vector3(this->x * b.x, this->y * b.y, this->z * b.z);
}
