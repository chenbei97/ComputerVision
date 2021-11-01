import cv2
img = cv2.imread("background2.jpg")  # 读取原始图像
templ = cv2.imread("template.png")  # 读取模板图像
width, height, c = templ.shape  # 获取模板图像的宽度、高度和通道数
results = cv2.matchTemplate(img, templ, cv2.TM_CCOEFF_NORMED)  # 按照标准相关系数匹配
for y in range(len(results)):  # 遍历结果数组的行
    for x in range(len(results[y])):  # 遍历结果数组的列
        if results[y][x] > 0.99:  # 如果相关系数大于0.99则认为匹配成功
            # 在最佳匹配结果位置绘制红色方框
            cv2.rectangle(img, (x, y), (x + width, y + height), (0, 0, 255), 2)
cv2.imshow("img", img)  # 显示匹配的结果
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体
