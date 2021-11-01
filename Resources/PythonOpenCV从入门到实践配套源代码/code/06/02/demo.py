import cv2

img = cv2.imread("beach.jpg")  # 读取原始图像
sum1 = img + img  # 使用运算符相加
sum2 = cv2.add(img, img)  # 使用方法相加
cv2.imshow("img", img)  # 展示原图
cv2.imshow("sum1", sum1)  # 展示运算符相加结果
cv2.imshow("sum2", sum2)  # 展示方法相加结果
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
