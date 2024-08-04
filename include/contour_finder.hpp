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


#ifndef __CONTOUR_FINDER_HPP__
#define __CONTOUR_FINDER_HPP__

#include "general.hpp"

class Circle {
public:
    cv::Point2f center;
    float radius;
};

class ContourFinder {
public:
    ContourFinder();
    ~ContourFinder() = default;

    cv::Mat color_segmentation(); // cv::Mat &frame, cv::Mat &mask
    bool choose_contours(); // cv::Mat &mask, std::vector<cv::Point> &contour, bool &success  ：原本是void，传入一个bool引用；现在改为返回bool值
    cv::Rect2d get_bounding_box();
    void draw_circle();
    void set_color(cv::Scalar lower_bound, cv::Scalar upper_bound);

public:
    cv::Mat frame;  // 读取的视频帧，公有变量直接赋值

private:
    // 图像处理过程中的中间变量
    cv::Mat hsv, mask;
    // 结果圆的信息
    Circle circle;
    // 颜色阈值，应当通过调用set_color进行设置
    cv::Scalar lower_bound;
    cv::Scalar upper_bound;
    // 轮廓信息
    std::vector<std::vector<cv::Point>> contours;
    // 卷积核
    cv::Mat kernel;
    // 保存选择除的轮廓信息
    std::vector<cv::Point> contour;  
};

#endif