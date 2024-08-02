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

#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

#include <nlohmann/json.hpp>
#include <fstream>
#include <opencv2/opencv.hpp>

class Config {
public:
    Config(std::string path);
    ~Config() = default;

    void load();

    void save();

    void get_bound(cv::Scalar &lower_bound, cv::Scalar &upper_bound);

    void set_bound(const cv::Scalar &lower_bound, const cv::Scalar &upper_bound);

    void set_kernel_size(int kernel_size);

    int get_kernel_size();

private:
    cv::Scalar lower_bound;
    cv::Scalar upper_bound;

    int kernel_size;

    // 配置文件的路径
    std::string path;
};
#endif