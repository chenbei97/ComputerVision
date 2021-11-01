import cv2
img = cv2.imread("demo.png")  # 读取图像
rows = len(img)  # 图像像素行数
cols = len(img[0])  # 图像像素列数
center = (rows / 2, cols / 2)  # 图像的中心点
M = cv2.getRotationMatrix2D(center, 30, 0.8)  # 以图像为中心，逆时针旋转30度，缩放0.8倍
dst = cv2.warpAffine(img, M, (cols, rows))  # 按照M进行仿射
cv2.imshow("img", img)  # 显示原图
cv2.imshow("dst", dst)  # 显示仿射变换效果
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
