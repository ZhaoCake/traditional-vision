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

# 正样本路径：resources/contour
# 负样本路径：resources/non_contour  人工创造负样本

# 创建64x64的负样本噪声图片
def create_negative_samples():
    for i in range(300):
        img = np.random.randint(0, 256, (256, 256, 3), dtype=np.uint8)
        cv2.imwrite(f'resources/non_contour/{i}.png', img)

def main():
    # 读取正样本: resources/contour中的全部文件，需要先读取文件列表，然后读取图片
    pos_samples = []
    for i in range(300):
        img = cv2.imread(f'resources/contour/roi{i}.jpg')
        img = cv2.resize(img, (256, 256))
        pos_samples.append(img)

    # 读取负样本：resources/non_contour中的全部文件
    create_negative_samples()
    neg_samples = []
    for i in range(300):
        img = cv2.imread(f'resources/non_contour/{i}.png')
        neg_samples.append(img)

    # 提取HOG特征, 64x64的窗口，16x16的block，8x8的cell，9个方向
    hog = cv2.HOGDescriptor((64, 64), (16, 16), (8, 8),
                            (8, 8), 9)
    pos_features = []
    for img in pos_samples:
        pos_features.append(hog.compute(img).flatten())
    pos_features = np.array(pos_features, dtype=np.float32)

    neg_features = []
    for img in neg_samples:
        neg_features.append(hog.compute(img).flatten())
    neg_features = np.array(neg_features, dtype=np.float32)

    # 创建标签
    pos_labels = np.ones((pos_features.shape[0], 1), dtype=np.int32)
    neg_labels = np.zeros((neg_features.shape[0], 1), dtype=np.int32)

    # 合并正负样本
    features = np.vstack((pos_features, neg_features))
    labels = np.vstack((pos_labels, neg_labels))

    # 训练SVM
    svm = cv2.ml.SVM_create()
    # 设置非线性SVM
    svm.setKernel(cv2.ml.SVM_LINEAR)
    svm.setType(cv2.ml.SVM_C_SVC)
    svm.setC(1)
    svm.train(features, cv2.ml.ROW_SAMPLE, labels)

    # 保存模型
    svm.save('resources/ball_svm.xml')

if __name__ == '__main__':
    main()
