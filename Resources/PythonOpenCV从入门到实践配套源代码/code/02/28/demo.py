import cv2
import numpy as np

width = 200  # 图像的宽
height = 100  # 图像的高
# 创建指定宽高、单通道、像素值都为0的图像
img = np.zeros((height, width), np.uint8)
cv2.imshow("img", img)  # 展示图像
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
