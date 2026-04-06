#pragma once

#include <constants.h>

namespace mcv
{
class Mat
{
public:
    Mat();
    Mat(size_t width, size_t height, size_t channels, DType dtype=DType::UINT);
    Mat(byte* data, size_t width, size_t height, size_t channels, DType dtype=DType::UINT);
    ~Mat();

    size_t width();
    size_t height();
    size_t channels();
    byte* data();
    DType dtype();

private:
    size_t width_ = 0;
    size_t height_ = 0;
    size_t channels_ = 0;
    byte* data_ = nullptr;
    DType dtype_;
};
}