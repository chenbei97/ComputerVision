import cv2
import numpy as np

width = 200  # 图像的宽
height = 100  # 图像的高
# 创建指定宽高、单通道、随机像素值的图像，随机值在0~256之间，数字为无符号8位格式
img = np.random.randint(256, size=(height, width), dtype=np.uint8)
cv2.imshow("img", img)  # 展示图像
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
