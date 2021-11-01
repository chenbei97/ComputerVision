import cv2
import numpy as np

img = cv2.imread("stone.jpg")  # 读取原始图像

img_h = np.hstack((img, img))  # 水平拼接两个图像
img_v = np.vstack((img, img))  # 垂直拼接两个图像

cv2.imshow("img_h", img_h)  # 展示拼接之后的效果
cv2.imshow("img_v", img_v)
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
