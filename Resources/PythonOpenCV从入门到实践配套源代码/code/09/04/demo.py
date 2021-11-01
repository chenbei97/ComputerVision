import cv2
img = cv2.imread("shape2.png")  # 读取原图
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)  # 从彩色图像变成单通道灰度图像
# 将灰度图像进行二值化阈值处理
t, binary = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY)
# 获取二值化图像中的轮廓极轮廓层次数据
contours, hierarchy = cv2.findContours(binary, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)
center, radius = cv2.minEnclosingCircle(contours[0])  # 获取最小圆形边框的圆心点和半径
x = int(round(center[0]))  # 圆心点横坐标转为近似整数
y = int(round(center[1]))  # 圆心点纵坐标转为近似整数
cv2.circle(img, (x, y), int(radius), (0, 0, 255), 2)  # 绘制圆形
cv2.imshow("img", img)  # 显示绘制结果
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
