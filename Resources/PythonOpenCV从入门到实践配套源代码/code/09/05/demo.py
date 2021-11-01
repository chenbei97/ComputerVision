import cv2

img = cv2.imread("shape2.png")  # 读取原始图像
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)  # 转为灰度图像
ret, binary = cv2.threshold(gray, 127, 225, cv2.THRESH_BINARY)  # 二值化阈值处理
# 检测图像中出现的所有轮廓
contours, hierarchy = cv2.findContours(binary, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)
hull = cv2.convexHull(contours[0])  # 获取轮廓的凸包
cv2.polylines(img, [hull], True, (0, 0, 255), 2)  # 绘制凸包
cv2.imshow("img", img)  # 显示图像
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
