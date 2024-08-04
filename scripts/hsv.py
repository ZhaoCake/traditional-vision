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

# 体现OpenCV的控件的使用, 并且能够读取JSON文件中的数值作为trackbar的默认值

import cv2
import json
import sys
import numpy as np

def main(config_path, video_path):
    # 读取JSON文件
    with open(config_path, 'r') as f:
        config = json.load(f)
        # lower_bound和upper_bound是两个键
        lower_bound = [int(i) for i in config['lower_bound']]
        upper_bound = [int(i) for i in config['upper_bound']]


    # 创建一个窗口
    cv2.namedWindow('hsv', cv2.WINDOW_NORMAL)

    # 创建六个滑动条，分别是H, S, V的下界和上界
    cv2.createTrackbar('H_lower', 'hsv', lower_bound[0], 180, lambda x: None)
    cv2.createTrackbar('S_lower', 'hsv', lower_bound[1], 255, lambda x: None)
    cv2.createTrackbar('V_lower', 'hsv', lower_bound[2], 255, lambda x: None)
    cv2.createTrackbar('H_upper', 'hsv', upper_bound[0], 180, lambda x: None)
    cv2.createTrackbar('S_upper', 'hsv', upper_bound[1], 255, lambda x: None)
    cv2.createTrackbar('V_upper', 'hsv', upper_bound[2], 255, lambda x: None)

    cap = cv2.VideoCapture(video_path)

    while True:
        ret, img = cap.read()
        # 如果读取帧失败，则可能已经到达视频末尾
        if not ret:
            # 重新设置视频文件的读取位置到开始
            cap.set(cv2.CAP_PROP_POS_FRAMES, 0)
            continue

        hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

        lower_bound = np.array([cv2.getTrackbarPos('H_lower', 'hsv'),
                                cv2.getTrackbarPos('S_lower', 'hsv'),
                                cv2.getTrackbarPos('V_lower', 'hsv')])
        upper_bound = np.array([cv2.getTrackbarPos('H_upper', 'hsv'),
                                cv2.getTrackbarPos('S_upper', 'hsv'),
                                cv2.getTrackbarPos('V_upper', 'hsv')])

        mask = cv2.inRange(hsv, lower_bound, upper_bound)
        res = cv2.bitwise_and(img, img, mask=mask)

        cv2.imshow('hsv', res)

        # 设置视频徐循环播放
        if cv2.waitKey(33) == 27:
            break

    cv2.destroyAllWindows()

    # 保存新的数值到JSON文件
    config['lower_bound'] = lower_bound.tolist()
    config['upper_bound'] = upper_bound.tolist()

    with open(config_path, 'w') as f:
        json.dump(config, f, indent=4)

if __name__ == '__main__':
    # 读取命令行参数
    config_path = sys.argv[1]
    video_path = sys.argv[2]
    main(config_path, video_path)
