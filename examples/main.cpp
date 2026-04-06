#include <iostream>

#include <opencv4/opencv2/opencv.hpp>
#include <minicv.h>

int main(int argc, char const *argv[])
{
    cv::Mat cv_image = cv::imread("/home/mai/Downloads/wallpaper.jpg");
    cv::resize(cv_image, cv_image, cv::Size(), 0.25f, 0.25f);

    size_t data_size = cv_image.cols * cv_image.rows * cv_image.channels() * sizeof(byte);
    byte* image_data = (byte*)std::malloc(data_size);
    std::memcpy(image_data, cv_image.data, data_size);

    mcv::Mat image = mcv::Mat(image_data, cv_image.cols, cv_image.rows, cv_image.channels());

    size_t width = image.width();
    size_t height = image.height();
    
    double start = mcv::time();
    // mcv::Mat out_image = mcv::resize(image, width*2, height*2, mcv::InterpolationType::NEAREST);
    // mcv::Mat out_image = mcv::rotate(image, 35.0f);
    // mcv::Mat out_image = mcv::rotate(image, mcv::Rotation::CLOCKWISE_90);
    // mcv::Mat out_image = mcv::flip(image, mcv::Flip::VERTICAL);
    mcv::Mat out_image = mcv::convert_colour(image, mcv::ColourCode::GRAY);

    double dt = mcv::time() - start;

    std::cout << dt << std::endl;

    // cv::Mat cv_out_image = cv::Mat(out_image.height(), out_image.width(), CV_8UC3, out_image.data());
    cv::Mat cv_out_image = cv::Mat(out_image.height(), out_image.width(), CV_8UC1, out_image.data());
    cv::imshow("before img", cv_image);
    cv::imshow("after img", cv_out_image);
    cv::waitKey(0);

    return 0;
}