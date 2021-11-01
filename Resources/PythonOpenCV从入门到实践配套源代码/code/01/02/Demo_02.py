import cv2

image = cv2.imread("1.1.jpg") # 读取1.1.jpg
cv2.imshow("flower", image) # 在名为flower的窗口中显示1.1.jpg
cv2.waitKey() # 窗口将一直显示图像，等价于cv2.waitKey(0)
cv2.destroyAllWindows() # 销毁所有窗口
