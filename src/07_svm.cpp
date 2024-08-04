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

#define SVM_MODEL "/home/cake/traditional-vision/resources/ball_svm.xml"

// 使用SVM进行目标检测，权重文件为resources/ball_svm.xml

int main () {
    cv::VideoCapture cap(CAMERA);
    if (!cap.isOpened()) {
        std::cerr << "Error: cannot open camera" << std::endl;
        return -1;
    }

    cv::Ptr<cv::ml::SVM> svm = cv::ml::SVM::load(SVM_MODEL);

    while (true) {
        cv::Mat frame;
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "Error: cannot read frame" << std::endl;
            break;
        }

        // 通过SVM进行目标检测
        ContourFinder contour_finder;
        contour_finder.frame = frame;
        cv::Mat mask = contour_finder.color_segmentation();

        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        for (int i = 0; i < contours.size(); i++) {
            cv::Rect rect = cv::boundingRect(contours[i]);
            cv::Mat roi = frame(rect);
            cv::resize(roi, roi, cv::Size(64, 64));
            cv::cvtColor(roi, roi, cv::COLOR_BGR2GRAY);
            cv::threshold(roi, roi, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
            cv::imshow("roi", roi);

            cv::Mat feature = roi.reshape(1, 1);
            feature.convertTo(feature, CV_32F);
            cv::Mat response;
            svm->predict(feature, response);
            if (response.at<float>(0, 0) == 1) {
                cv::rectangle(frame, rect, cv::Scalar(0, 255, 0), 2);
            }
        }

        cv::imshow("frame", frame);
        if (cv::waitKey(1) == 27) {
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}

