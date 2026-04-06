#pragma once

#include <constants.h>
#include <utils.h>
#include <mat.h>

namespace mcv
{
Mat resize(Mat& src, size_t dst_width, size_t dst_height, InterpolationType interpolation = InterpolationType::NEAREST);
Mat rotate(Mat& src, float degrees, InterpolationType interpolation = InterpolationType::NEAREST);
} 