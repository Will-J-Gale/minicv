#include <iostream>

#include <opencv4/opencv2/opencv.hpp>
#include <minicv.h>

inline void resize_bilinear_test(cv::Mat& cv_image, mcv::Mat& mcv_image, bool show=false)
{
    size_t width = 700;
    size_t height = 500;

    double cv_start = mcv::time();
    cv::Mat cv_processed;
    cv::resize(cv_image, cv_processed, cv::Size(width, height), 0.0, 0.0, cv::INTER_LINEAR);
    double cv_dt = mcv::time() - cv_start;

    double mcv_start = mcv::time();
    mcv::Mat mcv_processed = mcv::resize(mcv_image, width, height, mcv::InterpolationType::BILINEAR);
    double mcv_dt = mcv::time() - cv_start;

    double x_slower = mcv_dt / cv_dt;
    std::cout << "Resize bilinear" << std::endl;
    std::cout << "\topencv: \t" << cv_dt << std::endl;
    std::cout << "\tminicv: \t" << mcv_dt << std::endl;
    std::cout << "\tslowdown: \t" << x_slower << std::endl;

    if(show)
    {
        cv::Mat mcv_out_image = cv::Mat(mcv_processed.height(), mcv_processed.width(), CV_8UC3, mcv_processed.data().get());
        cv::imshow("opencv", cv_processed);
        cv::imshow("minicv", mcv_out_image);
        cv::waitKey(0);
    }
}

inline void resize_nearest_test(cv::Mat& cv_image, mcv::Mat& mcv_image, bool show=false)
{
    size_t width = 1000;
    size_t height = 800;

    double cv_start = mcv::time();
    cv::Mat cv_processed;
    cv::resize(cv_image, cv_processed, cv::Size(width, height), 0.0, 0.0, cv::INTER_NEAREST);
    double cv_dt = mcv::time() - cv_start;

    double mcv_start = mcv::time();
    mcv::Mat mcv_processed = mcv::resize(mcv_image, width, height, mcv::InterpolationType::NEAREST);
    double mcv_dt = mcv::time() - cv_start;

    double x_slower = mcv_dt / cv_dt;
    std::cout << "Resize nearest" << std::endl;
    std::cout << "\topencv: \t" << cv_dt << std::endl;
    std::cout << "\tminicv: \t" << mcv_dt << std::endl;
    std::cout << "\tslowdown: \t" << x_slower << std::endl;

    if(show)
    {
        cv::Mat mcv_out_image = cv::Mat(mcv_processed.height(), mcv_processed.width(), CV_8UC3, mcv_processed.data().get());
        cv::imshow("opencv", cv_processed);
        cv::imshow("minicv", mcv_out_image);
        cv::waitKey(0);
    }
}

inline void rotate_270(cv::Mat& cv_image, mcv::Mat& mcv_image, bool show=false)
{
    size_t width = 700;
    size_t height = 500;

    double cv_start = mcv::time();
    cv::Mat cv_processed;
    cv::rotate(cv_image, cv_processed, cv::ROTATE_90_COUNTERCLOCKWISE);
    double cv_dt = mcv::time() - cv_start;

    double mcv_start = mcv::time();
    mcv::Mat mcv_processed = mcv::rotate(mcv_image, mcv::Rotation::CLOCKWISE_270);
    double mcv_dt = mcv::time() - cv_start;

    double x_slower = mcv_dt / cv_dt;
    std::cout << "Rotate 270" << std::endl;
    std::cout << "\topencv: \t" << cv_dt << std::endl;
    std::cout << "\tminicv: \t" << mcv_dt << std::endl;
    std::cout << "\tslowdown: \t" << x_slower << std::endl;

    if(show)
    {
        cv::Mat mcv_out_image = cv::Mat(mcv_processed.height(), mcv_processed.width(), CV_8UC3, mcv_processed.data().get());
        cv::imshow("opencv", cv_processed);
        cv::imshow("minicv", mcv_out_image);
        cv::waitKey(0);
    }
}

inline void flip(cv::Mat& cv_image, mcv::Mat& mcv_image, bool show=false)
{
    size_t width = 700;
    size_t height = 500;

    double cv_start = mcv::time();
    cv::Mat cv_processed;
    cv::flip(cv_image, cv_processed, -1);
    double cv_dt = mcv::time() - cv_start;

    double mcv_start = mcv::time();
    mcv::Mat mcv_processed = mcv::flip(mcv_image, mcv::Flip::BOTH);
    double mcv_dt = mcv::time() - cv_start;

    double x_slower = mcv_dt / cv_dt;
    std::cout << "Flip" << std::endl;
    std::cout << "\topencv: \t" << cv_dt << std::endl;
    std::cout << "\tminicv: \t" << mcv_dt << std::endl;
    std::cout << "\tslowdown: \t" << x_slower << std::endl;

    if(show)
    {
        cv::Mat mcv_out_image = cv::Mat(mcv_processed.height(), mcv_processed.width(), CV_8UC3, mcv_processed.data().get());
        cv::imshow("opencv", cv_processed);
        cv::imshow("minicv", mcv_out_image);
        cv::waitKey(0);
    }
}

inline void gray_convert_test(cv::Mat& cv_image, mcv::Mat& mcv_image, bool show=false)
{
    size_t width = 700;
    size_t height = 500;

    double cv_start = mcv::time();
    cv::Mat cv_processed;
    cv::cvtColor(cv_image, cv_processed, cv::COLOR_BGR2GRAY);
    double cv_dt = mcv::time() - cv_start;

    double mcv_start = mcv::time();
    mcv::Mat mcv_processed = mcv::convert_colour(mcv_image, mcv::ColourCode::GRAY);
    double mcv_dt = mcv::time() - cv_start;

    double x_slower = mcv_dt / cv_dt;
    std::cout << "Gray convert" << std::endl;
    std::cout << "\topencv: \t" << cv_dt << std::endl;
    std::cout << "\tminicv: \t" << mcv_dt << std::endl;
    std::cout << "\tslowdown: \t" << x_slower << std::endl;

    if(show)
    {
        cv::Mat mcv_out_image = cv::Mat(mcv_processed.height(), mcv_processed.width(), CV_8UC1, mcv_processed.data().get());
        cv::imshow("opencv", cv_processed);
        cv::imshow("minicv", mcv_out_image);
        cv::waitKey(0);
    }
}

int main(int argc, char const *argv[])
{
    std::string image_path;
    bool show = false;

    if(argc >= 2) image_path = argv[1];
    if(argc >= 3) show = std::string(argv[2]) == "show";

    cv::Mat cv_image = cv::imread(image_path);

    size_t data_size = cv_image.cols * cv_image.rows * cv_image.channels() * sizeof(byte);
    byte* image_data = (byte*)std::malloc(data_size);
    std::memcpy(image_data, cv_image.data, data_size);

    mcv::Mat mcv_image = mcv::Mat(image_data, cv_image.cols, cv_image.rows, cv_image.channels(), mcv::DType::BYTE);

    resize_bilinear_test(cv_image, mcv_image, show);
    resize_nearest_test(cv_image, mcv_image, show);
    rotate_270(cv_image, mcv_image, show);
    flip(cv_image, mcv_image, show);
    gray_convert_test(cv_image, mcv_image, show);

    return 0;
}