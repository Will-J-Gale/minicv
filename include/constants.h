#pragma once

using byte = unsigned char;
using uint = unsigned int;
using BytePtr = std::shared_ptr<byte>;

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
    BYTE = 0,
    UINT,
    FLOAT
};

const std::map<DType, unsigned long> DTYPE_SIZE = std::map<DType, unsigned long> 
{
    {DType::BYTE, 1},
    {DType::UINT, 4},
    {DType::FLOAT, 4}
};

}