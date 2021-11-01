import cv2
img = cv2.imread("amygdalus triloba.jpg")  # 读取原图
dst1 = cv2.GaussianBlur(img, (5, 5), 0, 0)  # 使用大小为5*5的滤波核进行高斯滤波
dst2 = cv2.GaussianBlur(img, (9, 9), 0, 0)  # 使用大小为9*9的滤波核进行高斯滤波
dst3 = cv2.GaussianBlur(img, (15, 15), 0, 0)  # 使用大小为15*15的滤波核进行高斯滤波
cv2.imshow("img", img)  # 显示原图
cv2.imshow("5", dst1)  # 显示滤波效果
cv2.imshow("9", dst2)
cv2.imshow("15", dst3)
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
