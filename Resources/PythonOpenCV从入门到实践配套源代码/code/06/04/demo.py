import cv2
import numpy as np

img1 = np.zeros((150, 150, 3), np.uint8)  # 创建150*150的0值图像
img1[:, :, 0] = 255  # 蓝色通道賦予最大值
img2 = np.zeros((150, 150, 3), np.uint8)
img2[:, :, 2] = 255  # 红色通道賦予最大值

img = cv2.add(img1, img2)  # 蓝色 + 红色 = 洋红色
cv2.imshow("no mask", img)  # 展示相加的结果

m = np.zeros((150, 150, 1), np.uint8)  # 创建掩模
m[50:100, 50:100, :] = 255  # 掩模中央位置为纯白色
cv2.imshow("mask", m)  # 展示掩模

img = cv2.add(img1, img2, mask=m)  # 相加时使用掩模
cv2.imshow("use mask", img)  # 展示相加的结果

cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
