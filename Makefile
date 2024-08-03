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

# 使用cmake也可以实现这些运行脚本、直接启动程序等功能，但是需要调用添加自定义目标函数，个人认为更加繁琐一些。

PROJECT_NAME = contour_inst
BUILD_DIR = build

CONFIG_FILE = "config/config.json"
IMAGE_FILE = "resources/kun.png"


# CMake
# 默认目标
all: cmake-build

# 创建构建目录并运行 CMake 配置
cmake-configure:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake ..

# 构建项目
cmake-build: cmake-configure
	@cmake --build $(BUILD_DIR)

# 运行项目
run: cmake-build
	@cd $(BUILD_DIR) && ./$(PROJECT_NAME)

gdb-configure:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=Debug ..

gdb-build: gdb-configure
	@cmake --build $(BUILD_DIR) 

gdb: gdb-build  # 还未验证
	@cd $(BUILD_DIR) && gdb ./$(PROJECT_NAME)

# 运行hsv阈值调试
hsv: 
	@python3 scripts/hsv.py $(CONFIG_FILE) $(IMAGE_FILE)

on_mouse:
	@python3 scripts/on_mouse.py $(IMAGE_FILE)

init_contour:
	@echo "init contour..."
	@mkdir -p resources/contour
	@rm resources/contour/*.jpg

# 清理构建目录
clean:
	@rm -rf $(BUILD_DIR)

.PHONY: all cmake-configure cmake-build run clean hsv