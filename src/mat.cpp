#include <mat.h>

namespace mcv
{

Mat::Mat()
{
}

Mat::Mat (Mat& m)
{
    width_ = m.width();
    height_ = m.height();
    channels_ = m.channels();
    data_ = m.data();
}

Mat::Mat (Mat&& m)
{
    width_ = m.width();
    height_ = m.height();
    channels_ = m.channels();
    data_ = m.data();
}

Mat& Mat::operator=(Mat& m)
{
    width_ = m.width();
    height_ = m.height();
    channels_ = m.channels();
    data_ = m.data();
    return *this;
}

Mat::Mat(size_t width, size_t height, size_t channels, DType dtype)
{
    width_ = width;
    height_ = height;
    channels_ = channels;

    data_ = std::shared_ptr<byte>((byte*)std::malloc(size()), std::free);
}

Mat::Mat(BytePtr& data, size_t width, size_t height, size_t channels, DType dtype)
{
    width_ = width;
    height_ = height;
    channels_ = channels;
    data_ = data;
}

Mat::Mat(byte* data, size_t width, size_t height, size_t channels, DType dtype)
{
    width_ = width;
    height_ = height;
    channels_ = channels;
    data_ = std::shared_ptr<byte>(data);
}

Mat::~Mat()
{
}

void Mat::init(size_t width, size_t height, size_t channels, DType dtype)
{
    width_ = width;
    height_ = height;
    channels_ = channels;
    data_ = std::shared_ptr<byte>((byte*)std::malloc(size()), std::free);
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

BytePtr& Mat::data()
{
    return data_;
}

size_t Mat::size()
{
    return width_ * height_ * channels_ * DTYPE_SIZE.at(dtype_);
}

Mat Mat::clone()
{
    byte* data_copy = (byte*)std::malloc(size());
    std::memcpy(data_copy, data_.get(), size());

    return Mat(data_copy, width_, height_, channels_, dtype_);
}

}

