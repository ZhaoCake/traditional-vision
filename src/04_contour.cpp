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

#include "contour.hpp"

void color_segmentation(cv::Mat &frame, cv::Mat &mask) {
    cv::Mat hsv;
    cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);  // 转换为HSV色彩空间, 因为HSV色彩空间对光照相对不敏感
    cv::inRange(hsv, cv::Scalar(0, 43, 46), cv::Scalar(50, 255, 255), mask);  // 提取出黄色区域

    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));  // 定义结构元素  3x3的卷积核  
    // 简单介绍一下图像的卷积：卷积核在图像上滑动，对应位置的像素值相乘再相加，得到的值替换原来的像素值 —— 所以大量的形态学操作都是以卷积为基础的
    
    cv::morphologyEx(mask, mask, cv::MORPH_CLOSE, kernel);  // 闭操作：先膨胀后腐蚀——去除检测到的小区域的黑噪点
    cv::morphologyEx(mask, mask, cv::MORPH_OPEN, kernel);  // 开操作：先腐蚀后膨胀——去除不在黄色区域的白噪点
}

void choose_contours(cv::Mat &mask, std::vector<cv::Point> &contour, bool &success) {
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);  // [查找轮廓](https://docs.opencv.org/4.x/d3/dc0/group__imgproc__shape.html#gae4156f04053c44f886e387cff0ef6e08)
    // cv::RETR_EXTERNAL: 只检测外轮廓(mode)
    // cv::CHAIN_APPROX_SIMPLE: 压缩水平、垂直和对角线方向的元素，只保留该方向的终点坐标(methods)
    // 这个函数还有一个重载，可以获取层级信息，这里我们目的比较简单，不需要

    // 计算轮廓的面积，保留面积最大的轮廓
    double max_area = 0;
    int max_index = 0;
    for (int i = 0; i < contours.size(); i++) {
        double area = cv::contourArea(contours[i]);  // 计算轮廓的面积
        if (area > max_area && area > 300) {  // 保留面积大于500的轮廓
            max_area = area;
            max_index = i;
        }
    }

    if (max_area == 0) {
        success = false;
        return;
    }

    contour = contours[max_index];
}

Circle draw_circle(cv::Mat &frame, std::vector<cv::Point> &contour) {
    cv::Point2f center;
    float radius;
    cv::minEnclosingCircle(contour, center, radius);  // 计算轮廓的最小外接圆
    cv::circle(frame, center, radius, cv::Scalar(0, 255, 0), 2);  // 画出最小外接圆
    // 打包center和radius
    Circle circle;
    circle.center = center;
    circle.radius = radius;
    return circle;
}

int main() {
    // 仅对图像进行处理
    cv::Mat frame = cv::imread(IMAGE);
    if (frame.empty()) {
        std::cerr << "Error: cannot load image!" << std::endl;
        return -1;
    }

    cv::Mat mask;
    color_segmentation(frame, mask);

    std::vector<cv::Point> contour;
    bool success = true;
    choose_contours(mask, contour, success);

    if (success) {
        Circle circle;
        circle = draw_circle(frame, contour);
        std::cout << "center: " << circle.center << ", radius: " << circle.radius << std::endl;
    }

    // cv::imshow("frame", frame);
    // cv::imshow("mask", mask);
    // cv::waitKey(0);
}