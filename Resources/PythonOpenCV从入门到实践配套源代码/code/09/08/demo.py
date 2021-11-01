import cv2
import numpy as np

img = cv2.imread("coin.jpg")  # 读取原图
o = img.copy()  # 复制原图
o = cv2.medianBlur(o, 5)  # 使用中值滤波进行降噪
gray = cv2.cvtColor(o, cv2.COLOR_BGR2GRAY)  # 从彩色图像变成单通道灰度图像
# 检测圆环，圆心最小间距为70，Canny最大阈值为100，投票数超过25。最小半径为10，最大半径为50
circles = cv2.HoughCircles(gray, cv2.HOUGH_GRADIENT, 1, 70, param1=100, param2=25, minRadius=10, maxRadius=50)
circles = np.uint(np.around(circles))  # 将数组元素四舍五入成整数
for c in circles[0]:  # 遍历圆环结果
    x, y, r = c  # 圆心横坐标、纵坐标和圆半径
    cv2.circle(img, (x, y), r, (0, 0, 255), 3)  # 绘制圆环
    cv2.circle(img, (x, y), 2, (0, 0, 255), 3)  # 绘制圆心
cv2.imshow("img", img)  # 显示绘制结果
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
