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

#include "config.hpp"

Config::Config(std::string path) {
    path = path;
}

void Config::load() {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Error: cannot open file " << path << std::endl;
        return;
    }

    nlohmann::json j;

    file >> j;

    // 错误的：如果没有读取到配置文件，就会报错
    // lower_bound = cv::Scalar(j["lower_bound"][0], j["lower_bound"][1], j["lower_bound"][2]);
    // upper_bound = cv::Scalar(j["upper_bound"][0], j["upper_bound"][1], j["upper_bound"][2]);
    // kernel_size = j["kernel_size"];

    // 需要一个条件判断，如果没有读取到配置文件，就使用默认值
    if (j.find("lower_bound") != j.end()) {
        lower_bound = cv::Scalar(j["lower_bound"][0], j["lower_bound"][1], j["lower_bound"][2]);
    } else {
        lower_bound = cv::Scalar(20, 100, 100);
    }

    if (j.find("upper_bound") != j.end()) {
        upper_bound = cv::Scalar(j["upper_bound"][0], j["upper_bound"][1], j["upper_bound"][2]);
    } else {
        upper_bound = cv::Scalar(30, 255, 255);
    }

    if (j.find("kernel_size") != j.end()) {
        kernel_size = j["kernel_size"];
    } else {
        kernel_size = 3;
    }

    file.close();
}

void Config::save() {
    nlohmann::json j;

    j["lower_bound"] = {lower_bound[0], lower_bound[1], lower_bound[2]};
    j["upper_bound"] = {upper_bound[0], upper_bound[1], upper_bound[2]};
    j["kernel_size"] = kernel_size;

    std::ofstream file(path);
    file << j.dump(4);
    file.close();
}

void Config::get_bound(cv::Scalar &lower_bound, cv::Scalar &upper_bound) {
    lower_bound = this->lower_bound;
    upper_bound = this->upper_bound;
}

void Config::set_bound(const cv::Scalar &lower_bound, const cv::Scalar &upper_bound) {
    this->lower_bound = lower_bound;
    this->upper_bound = upper_bound;
}

void Config::set_kernel_size(int kernel_size) {
    this->kernel_size = kernel_size;
}

int Config::get_kernel_size() {
    return kernel_size;
}