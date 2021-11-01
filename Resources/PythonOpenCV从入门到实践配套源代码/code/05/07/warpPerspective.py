import cv2
import numpy as np
img = cv2.imread("demo.png")  # 读取图像
rows = len(img)  # 图像像素行数
cols = len(img[0])  # 图像像素列数
p1 = np.zeros((4, 2), np.float32)  # 32位浮点型空列表，保存原图四个点
p1[0] = [0, 0]  # 左上角点坐标
p1[1] = [cols - 1, 0]  # 右上角点坐标
p1[2] = [0, rows - 1]  # 左下角点坐标
p1[3] = [cols - 1, rows - 1]  # 右下角点坐标
p2 = np.zeros((4, 2), np.float32)  # 32位浮点型空列表，保存透视图四个点
p2[0] = [90, 0]  # 左上角点坐标，向右移动90像素
p2[1] = [cols - 90, 0]  # 右上角点坐标，向左移动90像素
p2[2] = [0, rows - 1]  # 左下角点坐标，位置不变
p2[3] = [cols - 1, rows - 1]  # 右下角点坐标，位置不变
M = cv2.getPerspectiveTransform(p1, p2)  # 根据四个点的变化轨迹计算出M矩阵
dst = cv2.warpPerspective(img, M, (cols, rows))  # 按照M进行仿射
cv2.imshow('img', img)  # 显示原图
cv2.imshow('dst', dst)  # 显示仿射变换效果
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
