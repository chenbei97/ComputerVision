import cv2
img = cv2.imread("demo.png")  # 读取图像
dst1 = cv2.resize(img, (100, 100))  # 按照宽100像素、高100像素的大小进行缩放
dst2 = cv2.resize(img, (400, 400))  # 按照宽400像素、高400像素的大小进行缩放
cv2.imshow("img", img)  # 显示原图
cv2.imshow("dst1", dst1)  # 显示缩放图像
cv2.imshow("dst2", dst2)  
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
