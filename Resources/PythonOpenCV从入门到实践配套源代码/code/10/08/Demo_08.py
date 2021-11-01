import cv2

image = cv2.imread("image.png")  # 读取原始图像
templs = []  # 模板列表
templs.append(cv2.imread("car1.png"))  # 添加模板图像1
templs.append(cv2.imread("car2.png"))  # 添加模板图像2
templs.append(cv2.imread("car3.png"))  # 添加模板图像3
templs.append(cv2.imread("car4.png"))  # 添加模板图像3
for car in templs:  # 遍历所有模板图像
    # 按照标准相关系数匹配
    results = cv2.matchTemplate(image, car, cv2.TM_CCOEFF_NORMED)
    for i in range(len(results)):  # 遍历结果数组的行
        for j in range(len(results[i])):  # 遍历结果数组的列
            # print(results[i][j])
            if results[i][j] > 0.99:  # 如果相关系数大于0.99则认为匹配成功
                if 0 < j <= 140:
                    print("车位编号:", 1)
                elif j <= 330:
                    print("车位编号:", 2)
                elif j <= 500:
                    print("车位编号:", 3)
                else:
                    print("车位编号:", 4)
                break
