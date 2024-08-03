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

int main() {
    cv::VideoCapture cap(CAMERA);
    if (!cap.isOpened()) {
        std::cerr << "Error: cannot open camera" << std::endl;
        return -1;
    }

    ContourFinder contour_finder;
    cv::Rect2d bounding_box;
    int name_counter = 0;

    cv::namedWindow("frame", cv::WINDOW_NORMAL);

    while (true) {
        cap >> contour_finder.frame;
        if (contour_finder.frame.empty()) {
            break;
        }

        contour_finder.color_segmentation();
        if (contour_finder.choose_contours()) {
            bounding_box = contour_finder.get_bounding_box();
            // 对bounding_box进行扩大
            bounding_box.x -= 10;
            bounding_box.y -= 10;
            bounding_box.width += 20;
            bounding_box.height += 20;
            // 判断是否超出
            if (bounding_box.x < 0) {
                bounding_box.x = 0;
            }
            if (bounding_box.y < 0) {
                bounding_box.y = 0;
            }
            if (bounding_box.x + bounding_box.width > contour_finder.frame.cols) {
                bounding_box.width = contour_finder.frame.cols - bounding_box.x;
            }
            if (bounding_box.y + bounding_box.height > contour_finder.frame.rows) {
                bounding_box.height = contour_finder.frame.rows - bounding_box.y;
            }

            // 从源图像中截取矩形区域
            cv::Mat roi = contour_finder.frame(bounding_box);
            // 保存截取的图像
            cv::imwrite("../resources/contour/roi" + std::to_string(name_counter) + ".jpg", roi);

            name_counter++;
        }

        cv::imshow("frame", contour_finder.frame);
        // q键退出
        if (cv::waitKey(33) == 'q') {
            break;
        }
    }

    cv::destroyAllWindows();
    cap.release();

    return 0;
}