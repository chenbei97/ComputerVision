import cv2
import numpy as np
img = cv2.imread("demo.png")  # 读取图像
rows = len(img)  # 图像像素行数
cols = len(img[0])  # 图像像素列数
M = np.float32([[1, 0, 50],  # 横坐标向右移动50像素
                [0, 1, 100]])  # 纵坐标向下移动100像素
dst = cv2.warpAffine(img, M, (cols, rows))
cv2.imshow("img", img)  # 显示原图
cv2.imshow("dst", dst)  # 显示仿射变换效果
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
