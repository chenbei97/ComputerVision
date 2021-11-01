import cv2
import numpy as np
img = cv2.imread("sunset.jpg")  # 读取原图
k = np.ones((9, 9), np.uint8)  # 创建9*9的数组作为核
cv2.imshow("img", img)  # 显示原图
dst = cv2.dilate(img, k)  # 膨胀操作
cv2.imshow("dst", dst)  # 显示膨胀效果
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
