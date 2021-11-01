import cv2
import numpy as np

width = 200  # 图像的宽
height = 100  # 图像的高
# 创建指定宽高、3通道、像素值都为0的图像
img = np.zeros((height, width, 3), np.uint8)
blue = img.copy()  # 复制图像
blue[:, :, 0] = 255  # 1通道所有像素都为255
green = img.copy()
green[:, :, 1] = 255  # 2通道所有像素都为255
red = img.copy()
red[:, :, 2] = 255  # 3通道所有像素都为255
cv2.imshow("blue", blue)  # 展示图像
cv2.imshow("green", green)
cv2.imshow("red", red)
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
