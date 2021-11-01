import cv2

rgb_image = cv2.imread("D:/2.1.jpg")
cv2.imshow("2.1", rgb_image) # 显示图2.1
# 图2.1从RGB色彩空间转换到HSV色彩空间
hsv_image = cv2.cvtColor(rgb_image, cv2.COLOR_RGB2HSV)
h, s, v = cv2.split(hsv_image) # 拆分HSV图像中的通道
cv2.imshow("H", h) # 显示HSV图像中的H通道图像
cv2.imshow("S", s) # 显示HSV图像中的S通道图像
cv2.imshow("V", v) # 显示HSV图像中的V通道图像
cv2.waitKey()
cv2.destroyAllWindows()
