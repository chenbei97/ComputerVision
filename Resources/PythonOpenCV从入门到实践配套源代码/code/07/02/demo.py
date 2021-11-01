import cv2
img = cv2.imread("amygdalus triloba.jpg")  # 读取原图
dst1 = cv2.medianBlur(img, 3)  # 使用宽度为3的滤波核进行中值滤波
dst2 = cv2.medianBlur(img, 5)  # 使用宽度为5的滤波核进行中值滤波
dst3 = cv2.medianBlur(img, 9)  # 使用宽度为9的滤波核进行中值滤波
cv2.imshow("img", img)  # 显示原图
cv2.imshow("3", dst1)  # 显示滤波效果
cv2.imshow("5", dst2)
cv2.imshow("9", dst3)
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
