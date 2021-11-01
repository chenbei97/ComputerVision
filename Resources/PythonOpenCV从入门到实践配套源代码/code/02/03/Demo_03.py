import cv2

image = cv2.imread("D:/2.1.jpg")
cv2.imshow("2.1", image) # 显示图2.1
# 将图2.1从RGB色彩空间转换到GRAY色彩空间
gray_image = cv2.cvtColor(image, cv2.COLOR_RGB2GRAY)
cv2.imshow("GRAY", gray_image) # 显示灰度图像
cv2.waitKey()
cv2.destroyAllWindows()
