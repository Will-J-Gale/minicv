#pragma once

#include <constants.h>
#include <utils.h>
#include <mat.h>

namespace mcv
{
    Mat resize_nearest(Mat& src, size_t dst_width, size_t dst_height);
    Mat resize_biliear(Mat& src, size_t dst_width, size_t dst_height);
    Mat rotate_degrees(Mat& src, float degrees);
    Mat rotate_90(Mat& src);
    Mat rotate_180(Mat& src);
    Mat rotate_270(Mat& src);
    Mat flip_horizontal(Mat& src);
    Mat flip_vertical(Mat& src);
    Mat flip_horizontal_vertical(Mat& src);
    Mat convert_gray(Mat& src);
} 