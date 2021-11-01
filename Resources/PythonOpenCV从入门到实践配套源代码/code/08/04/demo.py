import cv2
import numpy as np
img = cv2.imread("tianye.png")  # 读取原图
k = np.ones((15, 15), np.uint8)  # 创建15*15的数组作为核
cv2.imshow("img", img)  # 显示原图
dst = cv2.dilate(img, k)  # 膨胀操作
dst = cv2.erode(dst, k)  # 腐蚀操作
cv2.imshow("dst2", dst)  # 显示闭运算结果
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
