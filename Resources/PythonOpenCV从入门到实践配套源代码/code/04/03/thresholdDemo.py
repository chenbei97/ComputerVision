import cv2
img = cv2.imread("black.png", 0)  # 将图像读成灰度图像
t1, dst1 = cv2.threshold(img, 127, 255, cv2.THRESH_BINARY)  # 二值化阈值处理
t3, dst3 = cv2.threshold(img, 127, 150, cv2.THRESH_BINARY)  # 调低最大值效果
cv2.imshow('dst1', dst1)  # 展示最大值为255时的效果
cv2.imshow('dst3', dst3)  # 展示最大值为15时的效果
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
