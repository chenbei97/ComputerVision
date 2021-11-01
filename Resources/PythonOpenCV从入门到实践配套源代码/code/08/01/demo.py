import cv2
import numpy as np
img = cv2.imread("cactus.jpg")  # 读取原图
k = np.ones((3, 3), np.uint8)  # 创建3*3的数组作为核
cv2.imshow("img", img)  # 显示原图
dst = cv2.erode(img, k)  # 腐蚀操作
cv2.imshow("dst", dst)  # 显示腐蚀效果
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
