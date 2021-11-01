import cv2

rgb_image = cv2.imread("D:/2.1.jpg")
# 图2.1从RGB色彩空间转换到HSV色彩空间
hsv_image = cv2.cvtColor(rgb_image, cv2.COLOR_RGB2HSV)
h, s, v = cv2.split(hsv_image) # 拆分HSV图像中的通道
hsv = cv2.merge([h, s, v]) # 合并拆分后的通道图像
cv2.imshow("HSV", hsv) # 显示合并通道的HSV图像
cv2.waitKey()
cv2.destroyAllWindows()
