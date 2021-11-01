import cv2
img = cv2.imread("shape1.png")  # 读取原图
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)  # 彩色图像转为变成单通道灰度图像
t, binary = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY)  # 灰度图像转为二值图像
# 检测图像中出现的所有轮廓，记录轮廓的每一个点
contours, hierarchy = cv2.findContours(binary, cv2.RETR_LIST, cv2.CHAIN_APPROX_NONE)
# 绘制所有轮廓，宽度为5，颜色为红色
cv2.drawContours(img, contours, -1, (0, 0, 255), 5)
cv2.imshow("img", img)  # 显示绘制结果
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体