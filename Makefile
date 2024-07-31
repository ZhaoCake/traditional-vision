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

LOCAL_INCLUDE := -I./include
OPENCV_INCLUDE := -I/usr/include/opencv4
OPENCV_LIBS := -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio

# 每个源文件都有一个对应的可执行文件
TARGETS := $(SRCS:%.cpp=$(BUILD_DIR)/%.out)

all: $(TARGETS)
	@echo "Build finished"

$(BUILD_DIR)/%.out: %.cpp
	@mkdir -p $(dir $@)
	g++ -std=c++11 -g $(LOCAL_INCLUDE) $(OPENCV_INCLUDE) $< -o $@ $(OPENCV_LIBS)

run_contour:  # 每次都要进去build目录运行，太麻烦了
	@make all  # 最好是针对contour单独写个目标，不过这里我们基本不会改前面两个，或者改动成本很低，所以就这样了
	@cd build && ./src/03_contour.out
	@cd ..

gdb_contour:
	@make all
	@cd build && gdb ./src/04_contour.out
	@cd ..

sysinfo:  # 打印系统信息, makefile除了编译，还可以做很多事情，方便你的工作
	@echo "System Information:"
	@echo "OS: $(shell uname -s)"
	@echo "Kernel Version: $(shell uname -r)"
	@echo "Processor: $(shell uname -p)"
	@echo "Machine: $(shell uname -m)"
	@echo "System: $(shell uname -o)"
	@echo "Version: $(shell uname -v)"
	@echo "Release: $(shell uname -r)"
	@echo "Hostname: $(shell uname -n)"

	@fastfetch

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean run_contour sysinfo