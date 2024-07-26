#include <opencv2/dnn_superres.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <chrono>
#include <iostream>

using namespace std;
using namespace cv;
using namespace dnn;
using namespace dnn_superres;

int main(int argc, char* argv[])
{
    //Create the module's object
    DnnSuperResImpl sr;
    int scale = 2;

    //Set the image you would like to upscale
    string img_path = "D:\\study\\github\\opencv\\input.png";
    Mat img = cv::imread(img_path);

    //Read the desired model
    string path = "D:\\study\\github\\implementation-dnn-sr\\models\\FSRCNN\\FSRCNN_x2.pb";
    //string path = "D:\\study\\github\\implementation-dnn-sr\\models\\EDSR\\EDSR_x2.pb";
    sr.readModel(path);

    //Set the desired model and scale to get correct pre- and post-processing
    sr.setModel("fsrcnn", scale);
    //sr.setModel("edsr", scale);

    // 获取当前时间点
    auto now = std::chrono::system_clock::now();

    // 转换为毫秒级别的时间戳
    auto ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);

    // 获取毫秒级别的时间戳的值
    auto timestamp_start = ms.time_since_epoch().count();

    //Upscale
    Mat img_new;
    sr.upsample(img, img_new);

    // 获取当前时间点
    now = std::chrono::system_clock::now();

    // 转换为毫秒级别的时间戳
    ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);

    // 获取毫秒级别的时间戳的值
    auto timestamp_end = ms.time_since_epoch().count();

    std::cout << "cost: " << timestamp_end - timestamp_start << std::endl;

    // Image resized using OpenCV
    Mat resized;
    cv::resize(img, resized, cv::Size(), scale, scale);

    imshow("Original image", img);
    imshow("SR upscaled", img_new);
    imshow("OpenCV upscaled", resized);
    cv::imwrite("D:\\study\\github\\opencv\\upscaled.png", img_new);
    waitKey(0);
    destroyAllWindows();

    return 0;
}
