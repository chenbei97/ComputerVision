import cv2
import numpy as np

flower = cv2.imread("amygdalus triloba.png")  # 花原始图像
m = np.zeros(flower.shape, np.uint8)  # 与花图像大小相等的0值图像
m[120:180, :, :] = 255  # 横着的白色区域
m[:, 80:180, :] = 255  # 竖着的白色区域
img = cv2.bitwise_xor(flower, m)  # 两章图像做异或运算
cv2.imshow("flower", flower)  # 展示花图像
cv2.imshow("mask", m)  # 展示零值图像
cv2.imshow("img", img)  # 展示异或运算结果
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
