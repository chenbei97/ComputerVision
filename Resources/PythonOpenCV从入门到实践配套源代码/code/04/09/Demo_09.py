import cv2

image = cv2.imread("4.27.png") # 读取4.27.png
image_Gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY) # 将4.27.png转换为灰度图像
# 自适应阈值的计算方法为cv2.ADAPTIVE_THRESH_MEAN_C
athdMEAM = cv2.adaptiveThreshold\
    (image_Gray, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY, 5, 3)
# 自适应阈值的计算方法为cv2.ADAPTIVE_THRESH_GAUSSIAN_C
athdGAUS = cv2.adaptiveThreshold\
    (image_Gray, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C,cv2.THRESH_BINARY, 5, 3)
# 显示自适应阈值处理的结果
cv2.imshow("MEAN_C", athdMEAM)
cv2.imshow("GAUSSIAN_C", athdGAUS)
cv2.waitKey() # 按下任何键盘按键后
cv2.destroyAllWindows() # 销毁所有窗口

