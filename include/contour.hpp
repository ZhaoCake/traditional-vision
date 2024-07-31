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

#ifndef __CONTOUR_HPP__
#define __CONTOUR_HPP__

#include "general.hpp"
#include <vector>

/** @brief: 根据颜色分割，得到二值图像需要颜色分割和形态学操作
* @param: frame: 输入的三通道图像
* @param: mask: 处理后的二值图像
*/
void color_segmentation(cv::Mat &frame, cv::Mat &mask);

/** @brief: 查找轮廓，对于二值图像，我们可以通过轮廓查找函数来查找轮廓，并根据层级、形状等特征来筛选轮廓
* @param: mask: 输入的二值图像
* @param: contours: 输出的轮廓
*/
void choose_contours(cv::Mat &mask, std::vector<cv::Point> &contour);

/** @brief: 已经找到了轮廓，则我们可以计算轮廓的外接圆或外接矩形或其他信息来显示到图像上
 * @param: frame: 输入的三通道图像
 * @param: contour: 输入的轮廓
 */
void draw_circle(cv::Mat &frame, std::vector<cv::Point> &contour);


#endif