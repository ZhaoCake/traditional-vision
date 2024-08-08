import cv2
from PIL import Image
import numpy as np

# 读取图像
image = cv2.imread('zhao.png')

# 将图像从BGR转换到灰度
gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# 应用阈值操作，
# 将灰度图像转换为二值图像
_, thresh_image = cv2.threshold(gray_image, 70, 255, cv2.THRESH_BINARY)

# 创建alpha通道，黑色部分为0（透明），白色部分为255（不透明）
alpha_channel = 255 - thresh_image

# 创建全白色的图像、
# 用于合并到alpha通道中
white_image = 255 * np.ones_like(gray_image)

# 将BGR图像和alpha通道合并成BGRA格式
bgra_image = cv2.merge((white_image, alpha_channel))

# 使用Pillow库保存图像，因为OpenCV不支持保存PNG透明图像
pil_image = Image.fromarray(bgra_image)
pil_image = pil_image.convert("RGBA")  # 确保图像是RGBA格式
pil_image.save('zhao.png', 'PNG')

