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

# 使用resources文件夹中的图片, 训练一个opencv的SVM分类器，并保存为cpp的OpenCV能够使用的模型
import cv2
import numpy as np
import json
import sys

def main():
    # 读取图片  # 还要再整一些负样本
    img = cv2.imread('resources/lena.jpg')
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    # 读取标签
    with open('resources/labels.json', 'r') as f:
        labels = json.load(f)

    # 读取特征
    with open('resources/features.json', 'r') as f:
        features = json.load(f)

    # 创建一个SVM分类器
    svm = cv2.ml.SVM_create()
    svm.setType(cv2.ml.SVM_C_SVC)
    svm.setKernel(cv2.ml.SVM_LINEAR)
    svm.setTermCriteria((cv2.TERM_CRITERIA_MAX_ITER, 100, 1e-6))

    # 训练分类器
    svm.train(np.array(features, dtype=np.float32), cv2.ml.ROW_SAMPLE, np.array(labels, dtype=np.int32))

    # 保存分类器
    svm.save('resources/svm.xml')

if __name__ == '__main__':
    main()