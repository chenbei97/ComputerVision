import cv2
img = cv2.imread("demo.png")  # 读取图像
dst1 = cv2.flip(img, 0)  # 沿X轴翻转
dst2 = cv2.flip(img, 1)  # 沿Y轴翻转
dst3 = cv2.flip(img, -1)  # 同时沿X轴、Y轴翻转
cv2.imshow("img", img)  # 显示原图
cv2.imshow("dst1", dst1)  # 显示翻转之后的图像
cv2.imshow("dst2", dst2)
cv2.imshow("dst3", dst3)
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
