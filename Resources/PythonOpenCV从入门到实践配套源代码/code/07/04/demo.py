import cv2
img = cv2.imread("amygdalus triloba.jpg")  # 读取原图
dst1 = cv2.GaussianBlur(img, (15, 15), 0, 0)  # 使用大小为15*15的滤波核进行高斯滤波
# 双边滤波，选取范围直径为15，颜色差为120
dst2 = cv2.bilateralFilter(img, 15, 120, 100)
cv2.imshow("img", img)  # 显示原图
cv2.imshow("Gauss", dst1)  # 显示高斯滤波效果
cv2.imshow("bilateral", dst2)  # 显示双边滤波效果
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
