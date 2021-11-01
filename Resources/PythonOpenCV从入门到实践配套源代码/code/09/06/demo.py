import cv2
img = cv2.imread("flower.png")  # 读取原图
r1 = cv2.Canny(img, 10, 50);  # 使用不同的阈值进行边缘检测
r2 = cv2.Canny(img, 100, 200);
r3 = cv2.Canny(img, 400, 600);

cv2.imshow("img", img)  # 显示原图
cv2.imshow("r1", r1)  # 显示边缘检测结果
cv2.imshow("r2", r2)
cv2.imshow("r3", r3)
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
