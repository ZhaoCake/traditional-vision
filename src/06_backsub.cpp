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
#include "contour_finder.hpp"

// 使用OpenCV中的背景分离算法
int main () {
    cv::VideoCapture cap(CAMERA);
    if (!cap.isOpened()) {
        std::cerr << "Error: cannot open camera" << std::endl;
        return -1;
    }

    // cv::Ptr<cv::BackgroundSubtractor> pMOG2 = cv::createBackgroundSubtractorMOG2();  // 创建背景分离器
    cv::Ptr<cv::BackgroundSubtractor> pMOG2 = cv::createBackgroundSubtractorKNN();  // 创建背景分离器
    ContourFinder contour_finder;

    cv::Mat frame, fgMask, contourMask;
    cv::namedWindow("frame", cv::WINDOW_NORMAL);

    while (true) {
        cap >> contour_finder.frame;
        if (contour_finder.frame.empty()) {
            break;
        }

        pMOG2->apply(contour_finder.frame, fgMask);  // 背景分离

        contourMask = contour_finder.color_segmentation();  // 颜色分割

        // 图像取交
        cv::bitwise_and(fgMask, contourMask, fgMask);

        cv::imshow("frame", fgMask);
        if (cv::waitKey(30) == 27) {
            break;
        }
    }

    return 0;
}
