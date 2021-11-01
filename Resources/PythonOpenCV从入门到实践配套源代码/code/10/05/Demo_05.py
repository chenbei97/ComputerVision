import cv2

image = cv2.imread("image.png")  # 读取原始图像
templ = cv2.imread("templ.png")  # 读取模板图像
height, width, c = templ.shape  # 获取模板图像的高度、宽度和通道数
results = cv2.matchTemplate(image, templ, cv2.TM_CCOEFF_NORMED)  # 按照标准相关系数匹配
station_Num = 0  # 初始化快轨的站台个数为0
for y in range(len(results)):  # 遍历结果数组的行
    for x in range(len(results[y])):  # 遍历结果数组的列
        if results[y][x] > 0.99:  # 如果相关系数大于0.99则认为匹配成功
            # 在最佳匹配结果位置绘制蓝色矩形边框
            cv2.rectangle(image, (x, y), (x + width, y + height), (255, 0, 0), 2)
            station_Num += 1  # 快轨的站台个数加1
cv2.putText(image, "the numbers of stations: " + str(station_Num), (0, 30),
         cv2.FONT_HERSHEY_COMPLEX_SMALL, 1, (0, 0, 255), 1)  # 在原始图像绘制快轨站台的总数
cv2.imshow("result", image)  # 显示匹配的结果
cv2.waitKey()  # 按下任何键盘按键后
cv2.destroyAllWindows()  # 释放所有窗体