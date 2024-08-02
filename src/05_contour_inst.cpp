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

    cv::namedWindow("frame", cv::WINDOW_NORMAL);

    while (true) {
        cap >> contour_finder.frame;
        if (contour_finder.frame.empty()) {
            break;
        }

        contour_finder.color_segmentation();
        if (contour_finder.choose_contours()) {
            contour_finder.draw_circle();
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