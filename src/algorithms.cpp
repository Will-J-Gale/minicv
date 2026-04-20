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

Mat convolve(Mat& src, Mat& kernel)
{
    assert(kernel.channels() == 1);
    assert(kernel.width() == kernel.height());
    assert(kernel.dtype() == DType::FLOAT);

    Mat dst = Mat::zeros_like(src);
    byte* src_data = src.data().get();
    byte* dst_data = dst.data().get();
    float* filter_data = (float*)(kernel.data().get());
    int k_mid = (kernel.width() - 1) / 2;

    for(size_t y = 0; y < src.height(); y++)
    {
        for(size_t x = 0; x < src.width(); x++)
        {
            int index = xy_to_image_index(x, y, dst.width(), dst.channels());
            float avg_b = 0.0f;
            float avg_g = 0.0f;
            float avg_r = 0.0f;
            
            for(int filter_y = -k_mid; filter_y <= k_mid; filter_y++)
            {
                for(int filter_x = -k_mid; filter_x <= k_mid; filter_x++)
                {
                    int neighbor_x = x + filter_x;
                    int neighbor_y = y + filter_y;

                    if(neighbor_x < 0 or neighbor_x >= src.width() or neighbor_y < 0 or neighbor_y >= src.height())
                    {
                        continue;
                    }


                    uint filter_index = xy_to_image_index(filter_x + k_mid, filter_y + k_mid, kernel.width(), 1);
                    float filter_value = filter_data[filter_index];

                    int neighbor_index = xy_to_image_index(x + filter_x, y + filter_y, src.width(), src.channels());
                    float neightbor_value_b = (float)src_data[neighbor_index];
                    float neightbor_value_g = (float)src_data[neighbor_index + 1];
                    float neightbor_value_r = (float)src_data[neighbor_index + 2];

                    avg_b += neightbor_value_b * filter_value;
                    avg_g += neightbor_value_g * filter_value;
                    avg_r += neightbor_value_r * filter_value;
                }
            }

            dst_data[index] = avg_b;
            dst_data[index+1] = avg_g;
            dst_data[index+2] = avg_r;
        }
    }

    return dst;
}

}