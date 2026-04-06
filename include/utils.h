#pragma once

#include <constants.h>

namespace mcv
{
unsigned int xy_to_image_index(uint x, uint y, uint width, uint channels);
float interpolate(float value, float old_min, float old_max, float new_min, float new_max);
float get_decimal(float value);
bool is_int(float value);
float bilinear_interpolation(float x_alpha, float y_alpha, float tl, float tr, float bl, float br);
float deg_to_rad(float deg);
double time();
}