#include <chrono>

#include <utils.h>

namespace mcv
{

unsigned int xy_to_image_index(uint x, uint y, uint width, uint channels)
{
    return (x + (width * y)) * channels;
}

float interpolate(float value, float old_min, float old_max, float new_min, float new_max)
{
    float old_range = old_max - old_min;
    float new_range = new_max - new_min;
    float alpha = (value - old_min) / old_range;

    return (alpha * new_range) + new_min;
}

float get_decimal(float value)
{
    return value - (int)value;
}

bool is_int(float value)
{
    return (int)value / value == 1;
}

float bilinear_interpolation(float x_alpha, float y_alpha, float tl, float tr, float bl, float br)
{
    return (
        (x_alpha * y_alpha * tl) + 
        ((1.0f-x_alpha) * y_alpha * tr) +
        (x_alpha * (1.0f-y_alpha) * bl) + 
        ((1.0f-x_alpha) * (1.0f-y_alpha) * br)
    );
}

float deg_to_rad(float deg)
{
    return deg * (PI / 180.0f);
}

double time()
{
    auto currentTime = std::chrono::system_clock::now();
    auto duration = std::chrono::duration<double>(currentTime.time_since_epoch());

    return duration.count();
}
}