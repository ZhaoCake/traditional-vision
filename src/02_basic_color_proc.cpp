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
    cv::VideoCapture cap(CAMERA);
    if (!cap.isOpened()) {
        std::cerr << "Error: cannot open camera" << std::endl;
        return -1;
    }

    cv::Mat frame;
    cv::Mat gray;
    cv::Mat hsv;
    cv::Mat mask;

    while (true) {
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "Error: cannot read frame" << std::endl;
            break;
        }

        // 转换为灰度图
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        // 转换为HSV图
        cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);

        // 创建掩码
        cv::inRange(hsv, cv::Scalar(0, 100, 100), cv::Scalar(10, 255, 255), mask);

        cv::imshow("Camera", frame);
        cv::imshow("Gray", gray);
        cv::imshow("HSV", hsv);
        cv::imshow("Mask", mask);

        if (cv::waitKey(30) >= 0) {
            break;
        }
    }
}