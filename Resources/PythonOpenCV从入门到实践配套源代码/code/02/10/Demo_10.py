import cv2

rgb_image = cv2.imread("D:/2.1.jpg")
# 图2.1从RGB色彩空间转换到RGBA色彩空间
rgba_image = cv2.cvtColor(rgb_image, cv2.COLOR_RGB2RGBA)
cv2.imshow("RGBA", rgb_image) # 显示RGBA图像
r, g, b, a = cv2.split(rgba_image) # 拆分RGBA图像中的通道
a[:, :] = 172 # 将RGBA图像的透明度调整为172（半透明）
rgba_172 = cv2.merge([r, g, b, a]) # 合并拆分后并将透明度调整为172的通道图像
a[:, :] = 0 # 将RGBA图像的透明度调整为0（透明）
rgba_0 = cv2.merge([r, g, b, a]) # 合并拆分后并将透明度调整为0的通道图像
cv2.imshow("A = 172", rgba_172) # 显示透明度为172的RGBA图像
cv2.imshow("A = 0", rgba_0) # 显示透明度为0的RGBA图像
cv2.waitKey()
cv2.destroyAllWindows()
