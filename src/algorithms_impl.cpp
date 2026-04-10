#include <algorithms_impl.h>

namespace mcv
{
Mat resize_nearest(Mat& src, size_t dst_width, size_t dst_height)
{
    Mat dst = Mat(dst_width, dst_height, src.channels(), src.dtype());

    size_t src_width = src.width();
    size_t src_height = src.height();

    const byte* src_data = src.data().get();
    byte* dst_data = dst.data().get();

    for (int y = 0; y < dst_height; y++)
    {
        for (int x = 0; x < dst_width; x++)
        {
            float src_x = interpolate(x, 0.0f, dst_width, 0.0, src.width());
            float src_y = interpolate(y, 0.0f, dst_height, 0.0, src.height());
            uint dst_pixel_index = xy_to_image_index(x, y, dst_width, dst.channels());

            int src_x_index = std::round(src_x);
            int src_y_index = std::round(src_y);

            uint src_pixel_index = xy_to_image_index(src_x_index, src_y_index, src_width, src.channels());

            dst_data[dst_pixel_index] = src_data[src_pixel_index];
            dst_data[dst_pixel_index+1] = src_data[src_pixel_index + 1];
            dst_data[dst_pixel_index+2] = src_data[src_pixel_index + 2];
        }
    }
    return dst; //@TODO Data copied here??
}
Mat resize_biliear(Mat& src, size_t dst_width, size_t dst_height)
{
    Mat dst = Mat(dst_width, dst_height, src.channels(), src.dtype());

    size_t src_width = src.width();
    size_t src_height = src.height();

    const byte* src_data = src.data().get();
    byte* dst_data = dst.data().get();

    for (int y = 0; y < dst_height; y++)
    {
        for (int x = 0; x < dst_width; x++)
        {
            float src_x = interpolate(x, 0.0f, dst_width, 0.0, src.width());
            float src_y = interpolate(y, 0.0f, dst_height, 0.0, src.height());
            uint dst_pixel_index = xy_to_image_index(x, y, dst_width, dst.channels());
                
            uint src_tl_index = xy_to_image_index(std::floor(src_x), std::floor(src_y), src.width(), src.channels());
            uint src_tr_index = xy_to_image_index(std::ceil(src_x), std::floor(src_y), src.width(), src.channels());
            uint src_bl_index = xy_to_image_index(std::floor(src_x), std::ceil(src_y), src.width(), src.channels());
            uint src_br_index = xy_to_image_index(std::ceil(src_x), std::ceil(src_y), src.width(), src.channels());

            float x_alpha = 1.0f - get_decimal(src_x); 
            float y_alpha = 1.0f - get_decimal(src_y);

            float b_tl = src_data[src_tl_index];
            float b_tr = src_data[src_tr_index];
            float b_bl = src_data[src_bl_index];
            float b_br = src_data[src_br_index];

            float g_tl = src_data[src_tl_index+1];
            float g_tr = src_data[src_tr_index+1];
            float g_bl = src_data[src_bl_index+1];
            float g_br = src_data[src_br_index+1];

            float r_tl = src_data[src_tl_index+2];
            float r_tr = src_data[src_tr_index+2];
            float r_bl = src_data[src_bl_index+2];
            float r_br = src_data[src_br_index+2];

            float new_b = bilinear_interpolation(x_alpha, y_alpha, b_tl, b_tr, b_bl, b_br);
            float new_g = bilinear_interpolation(x_alpha, y_alpha, g_tl, g_tr, g_bl, g_br);
            float new_r = bilinear_interpolation(x_alpha, y_alpha, r_tl, r_tr, r_bl, r_br);

            dst_data[dst_pixel_index] = (int)new_b;
            dst_data[dst_pixel_index+1] = (int)new_g;
            dst_data[dst_pixel_index+2] = (int)new_r;
        }
    }
    return dst; //@TODO Data copied here??
}

Mat rotate_degrees(Mat& src, float degrees)
{
    Rect<int> bounds = calculate_rotation_bounds(src.width(), src.height(), degrees);
    Mat dst = Mat(bounds.width, bounds.height, src.channels(), src.dtype());

    int half_width = src.width() / 2;
    int half_height = src.height() / 2;

    float rad_angle = -deg_to_rad(degrees);
    float cos_angle = cos(rad_angle);
    float sin_angle = sin(rad_angle);

    const byte* src_data = src.data().get();
    byte* dst_data = dst.data().get();

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

Mat rotate_90(Mat& src)
{
    Mat dst = Mat(src.height(), src.width(), src.channels(), src.dtype());
    const byte* src_data = src.data().get();
    byte* dst_data = dst.data().get();

    for(int y = 0; y < dst.height(); y++)
    {
        for(int x = 0; x < dst.width(); x++)
        {
            size_t src_index = xy_to_image_index(y, src.height() - x, src.width(), src.channels());
            size_t dst_index = xy_to_image_index(x, y, dst.width(), dst.channels());

            dst_data[dst_index] = src_data[src_index];
            dst_data[dst_index+1] = src_data[src_index+1];
            dst_data[dst_index+2] = src_data[src_index+2];
        }
    }

    return dst;
}
Mat rotate_180(Mat& src)
{
    Mat dst = Mat(src.width(), src.height(), src.channels(), src.dtype());
    const byte* src_data = src.data().get();
    byte* dst_data = dst.data().get();

    for(int y = 0; y < dst.height(); y++)
    {
        int src_y = src.height() - y;
        for(int x = 0; x < dst.width(); x++)
        {
            int src_x = src.width() - x;
            size_t src_index = xy_to_image_index(src_x, src_y, src.width(), src.channels());
            size_t dst_index = xy_to_image_index(x, y, dst.width(), dst.channels());

            dst_data[dst_index] = src_data[src_index];
            dst_data[dst_index+1] = src_data[src_index+1];
            dst_data[dst_index+2] = src_data[src_index+2];
        }
    }

    return dst;
}
Mat rotate_270(Mat& src)
{
    Mat dst = Mat(src.height(), src.width(), src.channels(), src.dtype());
    const byte* src_data = src.data().get();
    byte* dst_data = dst.data().get();

    for(int y = 0; y < dst.height(); y++)
    {
        for(int x = 0; x < dst.width(); x++)
        {
            size_t src_index = xy_to_image_index(src.width() - y, x, src.width(), src.channels());
            size_t dst_index = xy_to_image_index(x, y, dst.width(), dst.channels());

            dst_data[dst_index] = src_data[src_index];
            dst_data[dst_index+1] = src_data[src_index+1];
            dst_data[dst_index+2] = src_data[src_index+2];
        }
    }

    return dst;
}

Mat flip_horizontal(Mat& src)
{
    Mat dst = Mat(src.width(), src.height(), src.channels(), src.dtype());
    const byte* src_data = src.data().get();
    byte* dst_data = dst.data().get();

    for(int y = 0; y < dst.height(); y++)
    {
        for(int x = 0; x < dst.width(); x++)
        {
            size_t src_index = xy_to_image_index(src.width() - x, y, src.width(), src.channels());
            size_t dst_index = xy_to_image_index(x, y, dst.width(), dst.channels());

            dst_data[dst_index] = src_data[src_index];
            dst_data[dst_index+1] = src_data[src_index+1];
            dst_data[dst_index+2] = src_data[src_index+2];
        }
    }

    return dst;
}

Mat flip_vertical(Mat& src)
{
    Mat dst = Mat(src.width(), src.height(), src.channels(), src.dtype());
    const byte* src_data = src.data().get();
    byte* dst_data = dst.data().get();

    for(int y = 0; y < dst.height(); y++)
    {
        for(int x = 0; x < dst.width(); x++)
        {
            size_t src_index = xy_to_image_index(x, src.height() - y, src.width(), src.channels());
            size_t dst_index = xy_to_image_index(x, y, dst.width(), dst.channels());

            dst_data[dst_index] = src_data[src_index];
            dst_data[dst_index+1] = src_data[src_index+1];
            dst_data[dst_index+2] = src_data[src_index+2];
        }
    }

    return dst;
}

Mat flip_horizontal_vertical(Mat& src)
{
    Mat dst = Mat(src.width(), src.height(), src.channels(), src.dtype());
    const byte* src_data = src.data().get();
    byte* dst_data = dst.data().get();

    for(int y = 0; y < dst.height(); y++)
    {
        for(int x = 0; x < dst.width(); x++)
        {
            size_t src_index = xy_to_image_index(src.width() - x, src.height() - y, src.width(), src.channels());
            size_t dst_index = xy_to_image_index(x, y, dst.width(), dst.channels());

            dst_data[dst_index] = src_data[src_index];
            dst_data[dst_index+1] = src_data[src_index+1];
            dst_data[dst_index+2] = src_data[src_index+2];
        }
    }

    return dst;
}

Mat convert_gray(Mat& src)
{
    double start = time();
    Mat dst = Mat(src.width(), src.height(), 1, src.dtype());
    const byte* src_data = src.data().get();
    byte* dst_data = dst.data().get();

    for(int y = 0; y < dst.height(); y++)
    {
        for(int x = 0; x < dst.width(); x++)
        {
            size_t src_index = xy_to_image_index(x, y, src.width(), src.channels());
            size_t dst_index = xy_to_image_index(x, y, dst.width(), dst.channels());

            byte b = src_data[src_index];
            byte g = src_data[src_index+1];
            byte r = src_data[src_index+2];
            byte gray = (0.299*r) + (0.587 * g) + (0.114*b); //@TODO Float casting making it slow?
            dst_data[dst_index] = gray;
        }
    }

    double dt = time() - start;

    return std::move(dst);
}
}