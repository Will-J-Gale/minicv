#include <mat.h>

namespace mcv
{

Mat::Mat()
{

}

Mat::Mat(size_t width, size_t height, size_t channels, DType dtype)
{
    width_ = width;
    height_ = height;
    channels_ = channels;

    size_t data_size = width * height * channels * sizeof(byte); //@TODO Handle dtyle
    data_ = (byte*)std::malloc(data_size);
}

Mat::Mat(byte* data, size_t width, size_t height, size_t channels, DType dtype)
{
    width_ = width;
    height_ = height;
    channels_ = channels;
    data_ = data;
}

Mat::~Mat()
{
    std::free(data_);
}

size_t Mat::width()
{
    return width_;
}

size_t Mat::height()
{
    return height_;
}
size_t Mat::channels()
{
    return channels_;
}
DType Mat::dtype()
{
    return dtype_;
}

byte* Mat::data()
{
    return data_;
}

}

