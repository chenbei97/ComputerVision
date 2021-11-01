import cv2
import numpy as np
img = cv2.imread("nigella.png")  # 读取原图
k = np.ones((5, 5), np.uint8)  # 创建5*5的数组作为核
cv2.imshow("img", img)  # 显示原图
dst = cv2.erode(img, k)  # 腐蚀操作
dst = cv2.dilate(dst, k)  # 膨胀操作
cv2.imshow("dst", dst)  # 显示开运算结果
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
