# Copyright (c) 2024 ZhaoCake
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

SRC_DIRS := ./src
BUILD_DIR := ./build

# 找到我们要编译的所有C和C++文件
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

LOCAL_INCLUDE := -I./include
OPENCV_INCLUDE := -I/usr/include/opencv4
OPENCV_LIBS := -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio

all:
	mkdir -p $(BUILD_DIR)
	make $(BUILD_DIR)/camera_setting
	make $(BUILD_DIR)/basic_color_proc
	@echo "Build all complete"

$(BUILD_DIR)/camera_setting: ./src/01_camera_setting.cpp
	@echo "Building camera_setting"
	g++ -o $(BUILD_DIR)/camera_setting ./src/01_camera_setting.cpp $(LOCAL_INCLUDE) $(OPENCV_INCLUDE) $(OPENCV_LIBS) -std=c++11
	@echo "Build complete"

$(BUILD_DIR)/basic_color_proc: ./src/02_basic_color_proc.cpp
	@echo "Building basic_color_proc"
	g++ -o $(BUILD_DIR)/basic_color_proc ./src/02_basic_color_proc.cpp $(OPENCV_INCLUDE) $(LOCAL_INCLUDE) $(OPENCV_LIBS) -std=c++11
	@echo "Build complete"

clean:
	rm -rf camera_setting basic_color_proc

.PHONY: all clean