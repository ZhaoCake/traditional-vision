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

# 一份调用了OpenCV的CMakeLists.txt文件，支持多个目标文件，根据源文件自动生成同名目标文件

cmake_minimum_required(VERSION 3.0)
project(traditionalVision)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)

# 寻找OpenCV库
find_package(OpenCV REQUIRED)

# 添加头文件
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/include)

# 输出路径


# 源文件在src目录下
file(GLOB SRC_FILES "src/*.cpp" )

# 生成目标文件
foreach(SRC_FILE ${SRC_FILES})
    get_filename_component(TARGET_NAME ${SRC_FILE} NAME_WE)
    add_executable(${TARGET_NAME} ${SRC_FILE} "src/config/config.cpp" "src/contour/contour_finder.cpp")
    target_link_libraries(${TARGET_NAME} ${OpenCV_LIBS})

    # 设置输出路径
    set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endforeach()

# 生成目标文件(05)
add_executable(contour_inst "src/05_contour_inst.cpp" "src/config/config.cpp" "src/contour/contour_finder.cpp")
target_link_libraries(contour_inst ${OpenCV_LIBS})
# 设置输出路径
set_target_properties(contour_inst PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# 生成目标文件(06)
add_executable(backsub "src/06_backsub.cpp" "src/config/config.cpp" "src/contour/contour_finder.cpp")
target_link_libraries(backsub ${OpenCV_LIBS})
# 设置输出路径
set_target_properties(backsub PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# 生成目标文件(07)
add_executable(svm "src/07_svm.cpp" "src/config/config.cpp" "src/contour/contour_finder.cpp")
target_link_libraries(svm ${OpenCV_LIBS})
# 设置输出路径
set_target_properties(svm PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

