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

#include "contour_finder.hpp"

#ifdef CONFIG  // 为了应对单独使用这个类而不通过CONFIG的情况，这里加上了这个宏
// 构造函数
ContourFinder::ContourFinder() {
    config.get_bound(ContourFinder::lower_bound, ContourFinder::upper_bound);  // 获取颜色阈值
    int size = config.get_kernel_size();  // 获取卷积核大小
    kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(size, size));  // 创建卷积核
}
#else 
ContourFinder::ContourFinder() {
    lower_bound = cv::Scalar(20, 100, 100);  // 设置颜色阈值
    upper_bound = cv::Scalar(30, 255, 255);
    kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));  // 创建卷积核
}
#endif


// 主要逻辑部分

cv::Mat ContourFinder::color_segmentation() {
    cv::cvtColor(ContourFinder::frame, ContourFinder::hsv, cv::COLOR_BGR2HSV);  // 转换为HSV色彩空间, 因为HSV色彩空间对光照相对不敏感
    cv::inRange(ContourFinder::hsv, ContourFinder::lower_bound, ContourFinder::upper_bound, ContourFinder::mask);  // 提取出特定颜色区域

    cv::morphologyEx(mask, mask, cv::MORPH_CLOSE, kernel);  // 闭操作：先膨胀后腐蚀——去除检测到的小区域的黑噪点
    cv::morphologyEx(mask, mask, cv::MORPH_OPEN, kernel);  // 开操作：先腐蚀后膨胀——去除不在黄色区域的白噪点

    return mask;
}

bool ContourFinder::choose_contours() {
    cv::findContours(ContourFinder::mask, ContourFinder::contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);  // [查找轮廓](https://docs.opencv.org/4.x/d3/dc0/group__imgproc__shape.html#gae4156f04053c44f886e387cff0ef6e08)

    double max_area = 0;
    int max_index = 0;
    for (int i = 0; i < ContourFinder::contours.size(); i++) {
        double area = cv::contourArea(ContourFinder::contours[i]);  // 计算轮廓的面积
        if (area > max_area && area > 300) {  // 保留面积大于500的轮廓
            max_area = area;
            max_index = i;
        }
    }

    if (max_area == 0) {
        return false;
    }

    ContourFinder::contour = ContourFinder::contours[max_index];
    cv::minEnclosingCircle(ContourFinder::contour, circle.center, circle.radius);  // 计算轮廓的最小外接圆
    return true;
}

void ContourFinder::draw_circle() { 
    // draw的时候就好好draw
    cv::circle(ContourFinder::frame, circle.center, circle.radius, cv::Scalar(0, 255, 0), 2);  // 画出最小外接圆
}

cv::Rect2d ContourFinder::get_bounding_box() {
    if (ContourFinder::contour.empty()) {
        return cv::Rect2d(0, 0, 0, 0);
    }
    return cv::boundingRect(ContourFinder::contour);  // 计算轮廓的外接矩形
}