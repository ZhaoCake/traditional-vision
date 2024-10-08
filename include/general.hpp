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

extern Config config;

#define CAMERA config.get_camera()
#define IMAGE config.get_image()

#endif
