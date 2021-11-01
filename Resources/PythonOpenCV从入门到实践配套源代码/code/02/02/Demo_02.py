import cv2

image = cv2.imread("D:/2.1.jpg")
cv2.imshow("2.1", image) # 显示图2.1
for i in range(241, 292): # i表示横坐标，在区间[241, 291]内取值
    for j in range(168, 219): # j表示纵坐标，在区间[168, 218]内取值
        image[i, j] = [255, 255, 255] # 把区域内的所有像素都修改为白色
cv2.imshow("2.8", image) # 显示图2.8
cv2.waitKey()
cv2.destroyAllWindows() # 关闭所有的窗口时，销毁所有窗口
