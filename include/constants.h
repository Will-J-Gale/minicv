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

enum class Rotation
{
    NONE,
    CLOCKWISE_90,
    CLOCKWISE_180,
    CLOCKWISE_270
};

enum class Flip
{
    NONE,
    HORIZONTAL,
    VERTICAL,
    BOTH
};

enum class ColourCode
{
    NONE,
    GRAY
};

enum class DType
{
    UINT,
    FLOAT
};

}