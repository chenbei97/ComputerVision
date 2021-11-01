import cv2
import time
import numpy as np

width, height = 200, 200  # 画面的宽和高
r = 20  # 圆半径
x = r + 20  # 圆心和坐标起始坐标
y = r + 100  # 圆形纵坐标起始坐标
x_offer = y_offer = 4  # 每一帧的移动速度

while cv2.waitKey(1) == -1:  # 按下任何按键之后
    if x > width - r or x < r:  # 如果圆的横坐标超出边界
        x_offer *= -1  # 横坐标速度取相反值
    if y > height - r or y < r:  # 如果圆的纵坐标超出边界
        y_offer *= -1  # 纵坐标速度取相反值
    x += x_offer  # 圆心按照横坐标速度移动
    y += y_offer  # 圆心按照纵坐标速度移动
    img = np.ones((width, height, 3), np.uint8) * 255  # 绘制白色背景面板
    cv2.circle(img, (x, y), r, (255, 0, 0), -1)  # 绘制圆形
    cv2.imshow("img", img)  # 显示图像
    time.sleep(1 / 60)  # 休眠1/60秒，也就是秒60帧

cv2.destroyAllWindows()  # 释放所有窗体
