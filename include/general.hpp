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

#ifndef __GENERAL_HPP__
#define __GENERAL_HPP__

#include <opencv2/opencv.hpp>
#include <iostream>
#include "config.hpp"

#define CAMERA "../resources/OnlyBasketball.mp4"
#define IMAGE "../resources/kun.png"

#define CONFIG "../config/config.yaml"

// 通过宏配置参数
// #define KERNEL_SIZE 3  // 改为通过配置文件读取

Config config(CONFIG);

#endif

