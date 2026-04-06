#pragma once

using byte = unsigned char;
using uint = unsigned int;
constexpr double PI = 3.1415926535;

namespace mcv
{

enum class InterpolationType
{
    NEAREST,
    BILINEAR
};

enum class DType
{
    UINT,
    FLOAT
};

}