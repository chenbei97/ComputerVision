import cv2
img = cv2.imread("demo.png")  # 读取图像
dst3 = cv2.resize(img, None, fx=1 / 3, fy=1 / 2)  # 将宽缩小到原来的1/3、高缩小到原来的1/2
dst4 = cv2.resize(img, None, fx=2, fy=2)  # 将宽高扩大2倍
cv2.imshow("img", img)  # 显示原图
cv2.imshow("dst3", dst3)  # 显示缩放图像
cv2.imshow("dst4", dst4)  # 显示缩放图像
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
