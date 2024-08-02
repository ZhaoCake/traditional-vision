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

def main(config_path, img_path):
    # 读取JSON文件
    with open(config_path, 'r') as f:
        config = json.load(f)
        # lower_bound和upper_bound是两个键
        lower_bound = [int(i) for i in config['lower_bound']]
        upper_bound = [int(i) for i in config['upper_bound']]


    # 创建一个窗口
    cv2.namedWindow('hsv')

    # 创建六个滑动条，分别是H, S, V的下界和上界
    cv2.createTrackbar('H_lower', 'hsv', lower_bound[0], 180, lambda x: None)
    cv2.createTrackbar('S_lower', 'hsv', lower_bound[1], 255, lambda x: None)
    cv2.createTrackbar('V_lower', 'hsv', lower_bound[2], 255, lambda x: None)
    cv2.createTrackbar('H_upper', 'hsv', upper_bound[0], 180, lambda x: None)
    cv2.createTrackbar('S_upper', 'hsv', upper_bound[1], 255, lambda x: None)
    cv2.createTrackbar('V_upper', 'hsv', upper_bound[2], 255, lambda x: None)

    # 读取一张图片
    img = cv2.imread(image_path)

    while True:
        # 将图片转换为HSV格式
        hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

        # 读取滑动条的值
        lower_bound = np.array([cv2.getTrackbarPos('H_lower', 'hsv'),
                                cv2.getTrackbarPos('S_lower', 'hsv'),
                                cv2.getTrackbarPos('V_lower', 'hsv')])
        upper_bound = np.array([cv2.getTrackbarPos('H_upper', 'hsv'),
                                cv2.getTrackbarPos('S_upper', 'hsv'),
                                cv2.getTrackbarPos('V_upper', 'hsv')])

        # 创建一个掩膜
        mask = cv2.inRange(hsv, lower_bound, upper_bound)

        # 将掩膜和原图进行按位与操作
        res = cv2.bitwise_and(img, img, mask=mask)

        # 显示图片
        cv2.imshow('hsv', res)

        # 按下ESC键退出
        if cv2.waitKey(1) == 27:
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
    image_path = sys.argv[2]
    main(config_path, image_path)
