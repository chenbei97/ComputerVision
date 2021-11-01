import cv2
img = cv2.imread("shape2.png")  # 读取原图
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)  # 从彩色图像变成单通道灰度图像
# 将灰度图像进行二值化阈值处理
t, binary = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY)
# 获取二值化图像中的轮廓极轮廓层次数据
contours, hierarchy = cv2.findContours(binary, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)
x, y, w, h = cv2.boundingRect(contours[0])  # 获取第一个轮廓的最小矩形边框，记录坐标和宽高
cv2.rectangle(img, (x, y), (x + w, y + h), (0, 0, 255), 2)  # 绘制红色矩形
cv2.imshow("img", img)  # 显示绘制结果
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
