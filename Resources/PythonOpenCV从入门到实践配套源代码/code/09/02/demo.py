import cv2
img = cv2.imread("flower.png")  # 读取原图
cv2.imshow("img", img)  # 显示原图
img = cv2.medianBlur(img, 5)  # 使用中值滤波去除噪点
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)  # 原图从彩图变成单通道灰度图像
t, binary = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY)  # 灰度图像转化为二值图像
cv2.imshow("binary", binary)  # 显示二值化图像
# 获取二值化图像中的轮廓极轮廓层次数据
contours, hierarchy = cv2.findContours(binary, cv2.RETR_LIST, cv2.CHAIN_APPROX_NONE)
cv2.drawContours(img, contours, -1, (0, 0, 255), 2)  # 在原图中绘制轮廓
cv2.imshow("contours", img)  # 显示绘有轮廓的图像
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
