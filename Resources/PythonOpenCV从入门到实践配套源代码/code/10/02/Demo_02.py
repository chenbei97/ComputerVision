import cv2

image = []  # 存储原始图像的列表
# 向image列表添加原始图像image_221.png
image.append(cv2.imread("image_221.png"))
# 向image列表添加原始图像image_222.png
image.append(cv2.imread("image_222.png"))
templ = cv2.imread("templ.png")  # 读取模板图像
index = -1  # 初始化车位编号列表的索引为-1
min = 1
for i in range(0, len(image)):  # 循环匹配image列表中的原始图像
    # 按照标准平方差方式匹配
    results = cv2.matchTemplate(image[i], templ, cv2.TM_SQDIFF_NORMED)
    # 获得最佳匹配结果的索引
    if min > any(results[0]):
        index = i
cv2.imshow("result", image[index])  # 显示最佳匹配结果
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
