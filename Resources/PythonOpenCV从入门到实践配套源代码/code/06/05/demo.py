import cv2
import numpy as np

flower = cv2.imread("amygdalus triloba.png")  # 花原始图像
mask = np.zeros(flower.shape, np.uint8)  # 与花图像大小相等的掩模图像
mask[120:180, :, :] = 255  # 横着的白色区域
mask[:, 80:180, :] = 255  # 竖着的白色区域
img = cv2.bitwise_and(flower, mask)  # 与运算
cv2.imshow("flower", flower)  # 展示花图像
cv2.imshow("mask", mask)  # 展示掩模图像
cv2.imshow("img", img)  # 展示与运算结果
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
