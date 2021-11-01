import cv2
img = cv2.imread("black.png", 0)  # 将图像读成灰度图像
t1, dst1 = cv2.threshold(img, 127, 255, cv2.THRESH_BINARY)  # 二值化阈值处理
t7, dst7 = cv2.threshold(img, 127, 255, cv2.THRESH_TRUNC)  # 截断处理
cv2.imshow('dst1', dst1)  # 展示二值化效果
cv2.imshow('dst7', dst7)  # 展示截断效果
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
