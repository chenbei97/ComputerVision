import cv2
img = cv2.imread("black.png", 0)  # 将图像读成灰度图像
t5, dst5 = cv2.threshold(img, 127, 255, cv2.THRESH_TOZERO)  # 低于阈值零处理
cv2.imshow('img', img)  # 显示原图
cv2.imshow('dst5', dst5)  # 低于阈值零处理效果图
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
