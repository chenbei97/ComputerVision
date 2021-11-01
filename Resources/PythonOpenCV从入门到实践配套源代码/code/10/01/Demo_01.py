import cv2
img = cv2.imread("background.jpg")  # 读取原始图像
templ = cv2.imread("template.png")  # 读取模板图像
width, height, c = templ.shape  # 获取模板图像的宽度、高度和通道数
results = cv2.matchTemplate(img, templ, cv2.TM_SQDIFF_NORMED)  # 按照标准平方差方式匹配
# 获取匹配结果中的最小值、最大值、最小值坐标和最大值坐标
minValue, maxValue, minLoc, maxLoc = cv2.minMaxLoc(results)
resultPoint1 = minLoc  # 将最小值坐标当做最佳匹配区域的左上角点坐标
# 计算出最佳匹配区域的右下角点坐标
resultPoint2 = (resultPoint1[0] + width, resultPoint1[1] + height)
# 在最佳匹配区域位置绘制红色方框，线宽为2像素
cv2.rectangle(img, resultPoint1, resultPoint2, (0, 0, 255), 2)
cv2.imshow("img", img)  # 显示匹配的结果
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
