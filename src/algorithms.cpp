/*
    @TODO Implement
    * convert colour
    * Add weighted 
    * figure out rgb/bgr?
*/
#include <constants.h>
#include <algorithms.h>
#include <algorithms_impl.h>
#include <mat.h>

namespace mcv
{

Mat resize(Mat& src, size_t dst_width, size_t dst_height, InterpolationType interpolation)
{
    if(interpolation == InterpolationType::NEAREST)
    {
        return resize_nearest(src, dst_width, dst_height);
    }
    else
    {
        return resize_biliear(src, dst_width, dst_height);
    }
}

Mat rotate(Mat& src, float degrees)
{
    Rect<int> bounds = calculate_rotation_bounds(src.width(), src.height(), degrees);
    Mat dst = Mat(bounds.width, bounds.height, src.channels(), src.dtype());

    int half_width = src.width() / 2;
    int half_height = src.height() / 2;

    float rad_angle = -deg_to_rad(degrees);
    float cos_angle = cos(rad_angle);
    float sin_angle = sin(rad_angle);

    const byte* src_data = src.data();
    byte* dst_data = dst.data();

    for (int y = 0; y < dst.height(); y++)
    {
        int y_shifted = y + bounds.tl.y;

        for (int x = 0; x < dst.width(); x++)
        {
            int x_shifted = x + bounds.tl.x;
            int x_norm = x_shifted - half_width;
            int y_norm = y_shifted - half_height;

            int x_rot = std::floor((x_norm * cos_angle) - (y_norm * sin_angle)) + half_width;
            int y_rot = std::floor((x_norm * sin_angle) + (y_norm * cos_angle)) + half_height;

            if(x_rot < 0 or x_rot >= src.width() or y_rot < 0 or y_rot >= src.height())
            {
                continue;
            }

            uint src_pixel_index = xy_to_image_index(x_rot, y_rot, src.width(), src.channels());
            uint dst_pixel_index = xy_to_image_index(x, y, dst.width(), dst.channels());

            dst_data[dst_pixel_index] = src_data[src_pixel_index];
            dst_data[dst_pixel_index+1] = src_data[src_pixel_index+1];
            dst_data[dst_pixel_index+2] = src_data[src_pixel_index+2];
        }

    }
    return dst;
}

Mat rotate(Mat& src, Rotation rotation)
{
    if(rotation == Rotation::NONE)
    {
        return src;
    }
    else if(rotation == Rotation::CLOCKWISE_90)
    {
        return rotate_90(src);
    }
    else if(rotation == Rotation::CLOCKWISE_180)
    {
        return rotate_180(src);
    }
    else
    {
        return rotate_270(src);
    }
}

Mat flip(Mat& src, Flip flip)
{
    if(flip == Flip::NONE)
    {
        return src;
    }
    else if(flip == Flip::HORIZONTAL)
    {
        return flip_horizontal(src);
    }
    else if(flip == Flip::VERTICAL)
    {
        return flip_vertical(src);
    }
    else
    {
        return flip_horizontal_vertical(src);
    }
}

Mat convert_colour(Mat& src, ColourCode colour_code)
{
    if(colour_code == ColourCode::NONE)
    {
        return src;
    }
    else if(colour_code == ColourCode::GRAY)
    {
        return convert_gray(src);
    }
}

}