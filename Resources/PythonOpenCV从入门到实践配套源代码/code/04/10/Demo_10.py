import cv2

image = cv2.imread("4.36.jpg") # 读取4.36.jpg
image_Gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY) # 将4.36.jpg转换为灰度图像
t1, dst1 = cv2.threshold(image_Gray, 127, 255, cv2.THRESH_BINARY) # 二值化阈值处理
# 实现Otsu方法的阈值处理
t2, dst2 = cv2.threshold(image_Gray, 0, 255, cv2.THRESH_BINARY  + cv2.THRESH_OTSU)
cv2.putText(dst2, "best threshold: " + str(t2), (0, 30),
         cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 0), 2) # 在图像上绘制最合适的阈值
cv2.imshow("BINARY", dst1) # 显示二值化阈值处理的图像
cv2.imshow("OTSU", dst2) # 显示实现Otsu方法的阈值处理
cv2.waitKey() # 按下任何键盘按键后
cv2.destroyAllWindows() # 销毁所有窗口