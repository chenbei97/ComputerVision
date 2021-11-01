import cv2

rgb_image = cv2.imread("D:/2.1.jpg")
cv2.imshow("2.1", rgb_image) # 显示图2.1
b, g, r = cv2.split(rgb_image) # 拆分图2.1中的通道
cv2.imshow("B", b) # 显示图2.1中的B通道图像
cv2.imshow("G", g) # 显示图2.1中的G通道图像
cv2.imshow("R", r) # 显示图2.1中的R通道图像
cv2.waitKey()
cv2.destroyAllWindows()
