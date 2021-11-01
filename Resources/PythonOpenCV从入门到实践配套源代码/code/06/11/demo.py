import cv2

beach_img = cv2.imread("beach.jpg")  # 沙滩原始图像
cat_img = cv2.imread("cat.jpg")  # 小猫原始图像
cat = cat_img[75:400, 120:260, :]  # 截取75行至400行、120列至260列的像素值所组成的图像
cat = cv2.resize(cat, (70, 160))  # 将截取出的图像缩放成70*160大小
cv2.imshow("cat", cat_img)  # 展示小猫原始图像
cv2.imshow("cat2", cat)  # 展示截取并缩放的小猫图像
cv2.imshow("beach", beach_img)  # 展示沙滩原始图像
rows, colmns, channel = cat.shape  # 记录截取图像的行数和列数
# 将沙滩中一部分像素改成截取之后的图像
beach_img[100:100 + rows, 260:260 + colmns, :] = cat
cv2.imshow("beach2", beach_img)  # 展示修改之后的图像
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
