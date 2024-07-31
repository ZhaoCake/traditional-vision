// Copyright (c) 2024 ZhaoCake
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "general.hpp"

int main () {
    // 打开摄像头
    cv::VideoCapture cap(CAMERA);
    if (!cap.isOpened()) {
        std::cerr << "Error: cannot open camera" << std::endl;
        return -1;
    }

    // ************************摄像头参数调整方法***********************
    // 调整摄像头参数
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    // 白平衡
    cap.set(cv::CAP_PROP_AUTO_WB, 0); // 关闭自动，下面同理
    cap.set(cv::CAP_PROP_WB_TEMPERATURE, 5000);
    // 曝光
    cap.set(cv::CAP_PROP_AUTO_EXPOSURE, 0);
    cap.set(cv::CAP_PROP_EXPOSURE, 0.1);
    // 饱和度
    cap.set(cv::CAP_PROP_SATURATION, 50);
    // 对比度
    cap.set(cv::CAP_PROP_CONTRAST, 50); 

    // 创建窗口
    cv::namedWindow("Camera", cv::WINDOW_AUTOSIZE);  
    // 第二个参数是窗口大小，可以是cv::WINDOW_NORMAL（可以resize） 
        // 或者 cv::WINDOW_AUTOSIZE（不可以resize，根据图片大小确定窗口大小）

    // 读取摄像头
    cv::Mat frame;
    while (true) {
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "Error: cannot read frame" << std::endl;
            break;
        }
        cv::imshow("Camera", frame);  // 显示图片
        if (cv::waitKey(30) >= 0) {  // 等待按键，括号内是毫秒数，设为0则无限等待，在显示图片时常用
            break;
        }
    }

    // 释放摄像头
    cap.release();
    cv::destroyAllWindows();

    return 0;
}