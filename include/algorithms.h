#pragma once

#include <constants.h>
#include <utils.h>
#include <mat.h>

namespace mcv
{
Mat resize(Mat& src, size_t dst_width, size_t dst_height, InterpolationType interpolation = InterpolationType::NEAREST);
Mat rotate(Mat& src, float degrees);
Mat rotate(Mat& src, Rotation rotation = Rotation::NONE);
Mat flip(Mat& src, Flip flip = Flip::NONE);
Mat convert_colour(Mat& src, ColourCode colour_code=ColourCode::NONE);
} 