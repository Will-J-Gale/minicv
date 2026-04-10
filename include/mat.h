#pragma once

#include <constants.h>

namespace mcv
{

class Mat
{
public:
    Mat();
    Mat(size_t width, size_t height, size_t channels, DType dtype=DType::UINT);
    Mat(BytePtr& data, size_t width, size_t height, size_t channels, DType dtype=DType::UINT);
    Mat(byte* data, size_t width, size_t height, size_t channels, DType dtype=DType::UINT);
    Mat (Mat& m); // Copy constructor
    Mat(Mat&&); //Move constrcutor
    Mat(const Mat&) = delete;//Copy constructor
    Mat& operator= (Mat& m);
    ~Mat();

    void init(size_t width, size_t height, size_t channels, DType dtype);
    size_t width();
    size_t height();
    size_t channels();
    BytePtr& data();
    DType dtype();
    size_t size();

private:
    size_t width_ = 0;
    size_t height_ = 0;
    size_t channels_ = 0;
    BytePtr data_ = nullptr;
    DType dtype_  = DType::BYTE;
    size_t size_;
};
}