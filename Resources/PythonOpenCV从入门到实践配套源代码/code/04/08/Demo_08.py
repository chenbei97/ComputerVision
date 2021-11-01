import cv2

image = cv2.imread("4.27.png") # 读取4.27.png
image_Gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY) # 将4.27.png转换为灰度图像
t1, dst1 = cv2.threshold(image_Gray, 127, 255, cv2.THRESH_BINARY) # 二值化阈值处理
t2, dst2 = cv2.threshold(image_Gray, 127, 255, cv2.THRESH_BINARY_INV) # 反二值化阈值处理
t3, dst3 = cv2.threshold(image_Gray, 127, 255, cv2.THRESH_TOZERO) # 低于阈值零处理
t4, dst4 = cv2.threshold(image_Gray, 127, 255, cv2.THRESH_TOZERO_INV) # 超出阈值零处理
t5, dst5 = cv2.threshold(image_Gray, 127, 255, cv2.THRESH_TRUNC) # 截断处理
# 分别显示经过5种阈值类型处理后的图像
cv2.imshow("BINARY", dst1)
cv2.imshow("BINARY_INV", dst2)
cv2.imshow("TOZERO", dst3)
cv2.imshow("TOZERO_INV", dst4)
cv2.imshow("TRUNC", dst5)
cv2.waitKey() # 按下任何键盘按键后
cv2.destroyAllWindows() # 销毁所有窗口
