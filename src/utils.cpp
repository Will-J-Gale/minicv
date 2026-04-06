#include <chrono>

#include <core.h>
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

Rect<int> calculate_rotation_bounds(int width, int height, float degrees)
{
    //@TODO Can be made nicer
    int half_width = width / 2;
    int half_height = height / 2;
    float rad_angle = deg_to_rad(degrees);
    float cos_angle = cos(rad_angle);
    float sin_angle = sin(rad_angle);
    
    int tl_x_rot = std::floor((-half_width * cos_angle) - (-half_height * sin_angle)) + half_width;
    int tl_y_rot = std::floor((-half_width * sin_angle) + (-half_height * cos_angle)) + half_height;

    int tr_x_rot = std::floor((half_width * cos_angle) - (-half_height * sin_angle)) + half_width;
    int tr_y_rot = std::floor((half_width * sin_angle) + (-half_height * cos_angle)) + half_height;

    int bl_x_rot = std::floor((-half_width * cos_angle) - (half_height * sin_angle)) + half_width;
    int bl_y_rot = std::floor((-half_width * sin_angle) + (half_height * cos_angle)) + half_height;

    int br_x_rot = std::floor((half_width * cos_angle) - (half_height * sin_angle)) + half_width;
    int br_y_rot = std::floor((half_width * sin_angle) + (half_height * cos_angle)) + half_height;

    int min_x = min({tl_x_rot, tr_x_rot, bl_x_rot, br_x_rot});
    int min_y = min({tl_y_rot, tr_y_rot, bl_y_rot, br_y_rot});
    int max_x = max({tl_x_rot, tr_x_rot, bl_x_rot, br_x_rot});
    int max_y = max({tl_y_rot, tr_y_rot, bl_y_rot, br_y_rot});

    Rect<int> bounds = Rect<int>(
        Point<int>(min_x, min_y),
        Point<int>(max_x, max_y)
    );

    return bounds;
}

template <typename T>
T max(std::initializer_list<T> values)
{
    T max_value = INT_MIN;
    for(const T& value : values)
    {
        if(value > max_value)
        {
            max_value = value;
        }
    }

    return max_value;
}

template <typename T>
T min(std::initializer_list<T> values)
{
    T max_value = INT_MAX;
    for(const T& value : values)
    {
        if(value < max_value)
        {
            max_value = value;
        }
    }

    return max_value;
}
}