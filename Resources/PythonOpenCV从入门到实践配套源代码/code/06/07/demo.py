import cv2

flower = cv2.imread("amygdalus triloba.png")  # 花原始图像
img = cv2.bitwise_not(flower)  # 取反运算
cv2.imshow("flower", flower)  # 展示花图像
cv2.imshow("img", img)  # 展示取反运算结果
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
