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

# 使用resources/ball_svm.xml文件，检测视频

import cv2
import numpy as np
import sys

def main(video_path, model_path):
    # 读取SVM模型
    svm = cv2.ml.SVM_load(model_path)

    cap = cv2.VideoCapture(video_path)
    while True:
        ret, img = cap.read()
        if not ret:
            cap.set(cv2.CAP_PROP_POS_FRAMES, 0)
            continue

        # 提取HOG特征
        hog = cv2.HOGDescriptor((64, 64), (16, 16), (8, 8), (8, 8), 9)
        feature = hog.compute(img).flatten()

        # 预测
        result = svm.predict(np.array([feature], dtype=np.float32))

        if result[0][0] == 1:
            print('Ball detected!')
            cv2.putText(img, 'Ball detected!', (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)
        else:
            print('Ball not detected!')
            cv2.putText(img, 'Ball not detected!', (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)

        cv2.imshow('video', img)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cv2.destroyAllWindows()

if __name__ == '__main__':
    video_path = sys.argv[1]
    model_path = sys.argv[2]
    main(video_path, model_path)
