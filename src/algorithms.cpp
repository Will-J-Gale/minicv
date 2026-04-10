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
    return rotate_degrees(src, degrees);
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
    else
    {
        throw std::runtime_error("colour_code not implemented");
    }
}

}