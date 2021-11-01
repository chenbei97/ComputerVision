import cv2
img = cv2.imread("car.jpg")  # 原始图像
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)  # 转为灰度图像
t1, dst1 = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY)  # 二值化阈值处理
t2, dst2 = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY_INV)  # 反二值化阈值处理
cv2.imshow("img", img)  # 显示图像
cv2.imshow("gray", gray)
cv2.imshow("dst1", dst1)
cv2.imshow("dst2", dst2)
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
