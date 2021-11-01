import cv2
sun = cv2.imread("sunset.jpg")  # 日落原始图像
beach = cv2.imread("beach.jpg")  # 沙滩原始图像
rows, colmns, channel = sun.shape  # 日落图像的行数、列数和通道数
beach = cv2.resize(beach, (colmns, rows))  # 沙滩图像缩放成日落图像大小
img = cv2.addWeighted(sun, 0.6, beach, 0.6, 0)  # 计算两幅图像加权和
cv2.imshow("sun", sun)  # 展示日落图像
cv2.imshow("beach", beach)  # 展示沙滩图像
cv2.imshow("addWeighted", img)  # 展示加权和图像
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
