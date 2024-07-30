#include <opencv2/opencv.hpp>

// 设置摄像头
#define CAMERA "resources/OnlyBasketball.mp4"

int main () {
    // 打开摄像头
    cv::VideoCapture cap(CAMERA);
    if (!cap.isOpened()) {
        std::cerr << "Error: cannot open camera" << std::endl;
        return -1;
    }

    // 创建窗口
    cv::namedWindow("Camera", cv::WINDOW_AUTOSIZE);

    // 读取摄像头
    cv::Mat frame;
    while (true) {
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "Error: cannot read frame" << std::endl;
            break;
        }
        cv::imshow("Camera", frame);
        if (cv::waitKey(30) >= 0) {
            break;
        }
    }

    // 释放摄像头
    cap.release();
    cv::destroyAllWindows();

    return 0;
}