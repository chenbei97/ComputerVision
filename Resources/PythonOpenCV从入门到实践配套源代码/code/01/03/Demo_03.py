import cv2

image = cv2.imread("1.1.jpg") # 读取1.1.jpg
# 把1.1.jpg保存为E盘根目录下的、Pictures文件夹中的1.jpg
cv2.imwrite("E:/Pictures/1.jpg", image)
