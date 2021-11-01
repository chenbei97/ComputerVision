import cv2
import numpy as np

img = cv2.imread("pen.jpg")  # 读取原图
o = img.copy()  # 复制原图
o = cv2.medianBlur(o, 5)  # 使用中值滤波进行降噪
gray = cv2.cvtColor(o, cv2.COLOR_BGR2GRAY)  # 从彩色图像变成单通道灰度图像
binary = cv2.Canny(o, 50, 150)  # 绘制边缘图像
# 检测直线，精度为1，全角度，阈值为15，线段最短100，最小间隔为18
lines = cv2.HoughLinesP(binary, 1, np.pi / 180, 15, minLineLength=100, maxLineGap=18)
for line in lines:  # 遍历所有直线
    x1, y1, x2, y2 = line[0]  # 读取直线两个端点的坐标
    cv2.line(img, (x1, y1), (x2, y2), (0, 0, 255), 2)  # 在原始图像上绘制直线
cv2.imshow("canny", binary)  # 显示二值化边缘图案
cv2.imshow("img", img)  # 显示绘制结果
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
