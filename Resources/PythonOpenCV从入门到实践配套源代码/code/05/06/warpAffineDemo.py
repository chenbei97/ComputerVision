import cv2
import numpy as np
img = cv2.imread("demo.png")  # 读取图像
rows = len(img)  # 图像像素行数
cols = len(img[0])  # 图像像素列数
p1 = np.zeros((3, 2), np.float32)  # 32位浮点型空列表，原图三个点
p1[0] = [0, 0]  # 左上角点坐标
p1[1] = [cols - 1, 0]  # 右上角点坐标
p1[2] = [0, rows - 1]  # 左下角点坐标
p2 = np.zeros((3, 2), np.float32)  # 32位浮点型空列表，倾斜图三个点
p2[0] = [50, 0]  # 左上角点坐标，向右挪50像素
p2[1] = [cols - 1, 0]  # 右上角点坐标，位置不变
p2[2] = [0, rows - 1]  # 左下角点坐标，位置不变
M = cv2.getAffineTransform(p1, p2)  # 根据三个点的变化轨迹计算出M矩阵
dst = cv2.warpAffine(img, M, (cols, rows))  # 按照M进行仿射
cv2.imshow('img', img)  # 显示原图
cv2.imshow('dst', dst)  # 显示仿射变换效果
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
